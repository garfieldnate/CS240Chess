#include "Game.h"
#include "King.h"
#include "Referenceable.h"
#include "Reference.h"
#include "Move.h"
#include "Pawn.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "CS240Exception.h"
#include "XML.h"
#include "XMLReader.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "assert.h"
using namespace std;

Game::Game(){
	cout << "Creating new Game" << endl;
	board = new Board();
	history = new vector<Move * >();
}

Game::Game(string fileName){
	board = new Board();
	history = XMLReader::getHistory(fileName,board);
	cout << "size is: " << history->size() <<  endl;
	//then execute entire history
	for(int i = 0; i < history->size(); i++){
		executeLoaded(history->at(i));
	}
		
	cout << "finished loading" << endl;
}
		
Game::~Game(){
	delete board;
	delete history;
}

//!@return piece at location given by row and column
IPiece* Game::pieceAt(int row, int col){
	return board->pieceAt(row, col);
}

bool Game::existsPieceAt(int row, int col){
	return board->existsPieceAt(row, col);
}

//!
vector<Reference<Location> > Game::getMoves(int row, int col){
	vector<Reference<Location> > moves = board->getMoves(row,col);
	//get rid of moves that put player in check
	filter(&moves,row,col);
	return moves;
}

//execute each move (and undo it); if it puts the king in check, remove it from the list of moves
void Game::filter(vector<Reference<Location> > * locs, int row,int col){
	int color = pieceAt(row,col)->getColor();
	King * king = board->getKing(color);
	Move * move;
	for(int i = 0; i < locs->size(); i++){
		if(locs->at(i)->getPiece() != NULL)
			move = new Move(getSquares()[row][col],locs->at(i),locs->at(i)->getPiece());
		else
			move = new Move(getSquares()[row][col],locs->at(i),locs->at(i)->getPiece());
		execute(move);
		if(isCheck(color)){
			locs->erase(locs->begin()+i);
			i--;
			for(int i = 0; i < locs->size(); i++)
				cout << locs->at(i)->getRow() << ", " << locs->at(i)->getCol()  << endl;
		}
		undo();
		delete move;
	}
}

//!@return true if king is in check
bool Game::isCheck(int color){
	King * king = board->getKing(color);
	ImageName in = king->getType();
	Reference<Location> loc = board->getLoc(king->getType());
	return king->check(getSquares(),loc);
			
	return false;
}

//!@return true if checkmate is achieved
bool Game::noMoves(int color){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(existsPieceAt(i,j) &&
				pieceAt(i,j)->getColor() == color
				&& getMoves(i,j).size() != 0)
					return false;
		}
	}
	return true;
}

//!@return true if stalemate is achieved
bool Game::isStaleMate(){
	
}

Reference<Location>** Game::getSquares(){
	return board->getAllSquares();
}

Reference<Location> Game::locAt(int row, int col){
	return board->getSquare(row,col);
}

void Game::executeLoaded(Move * move){
	assert(move != NULL);
	//cout ecuting move from " << move->getStart()->getRow() << "," 
		//<< move->getStart()->getCol() <<
		//" to " << move->getEnd()->getRow() << "," << move->getEnd()->getCol() << endl;
	
	//don't store move again
	
	//save captured, if there was one
	if(move->getEnd()->getPiece() != NULL)
		move->setCaptured(move->getEnd()->getPiece());
	
	//move piece; automatically removes captured piece
	IPiece* mover = move->getStart()->getPiece();
	move->getEnd()->setPiece(mover);
	move->getStart()->setPiece(NULL);
	
	//pawns need to remember that they moved
	if(mover->getType() == W_PAWN || mover->getType() == B_PAWN)
		((Pawn*)mover)->incrementMoved();
}

void Game::execute(Move * move){
	assert(move != NULL);
	cout << "executing move from " << move->getStart()->getRow() << "," 
		<< move->getStart()->getCol() <<
		" to " << move->getEnd()->getRow() << "," << move->getEnd()->getCol() << endl;
	//save move
	history->insert(history->end(),move);
	
	//move piece; automatically removes captured piece
	IPiece* mover = move->getStart()->getPiece();
	move->getEnd()->setPiece(mover);
	move->getStart()->setPiece(NULL);
	
	//pawns need to remember that they moved
	if(mover->getType() == W_PAWN || mover->getType() == B_PAWN)
		((Pawn*)mover)->incrementMoved();
}

bool Game::undo(){
	if(history->size() == 0)
		return false;
	cout << "Game: undoing" << endl;
	//retrieve move from history
	Move * move = history->back();
	history->pop_back();
	
	//move back piece, uncapture if applicable
	move->getStart()->setPiece(move->getEnd()->getPiece());
	move->getEnd()->setPiece(move->getCaptured());
	
	//pawns need to forget that they moved
	IPiece* mover = move->getStart()->getPiece();
	if(mover->getType() == W_PAWN || mover->getType() == B_PAWN)
		((Pawn*)mover)->decrementMoved();
	return true;
}

//returns a crappy random move
Move * Game::getComputerMove(int color){
	Reference<Location> ** squares = getSquares();
	Move * move = NULL;
	//loop through the board for a random piece of this color;
	//if the piece has moves
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			move = getComputerMove(i, j, color);
			if(move != NULL)
				return move;
		}
	}
	throw new IllegalStateException("No legal moves for the computer");
	//return move;
}

Move * Game::getComputerMove(int row, int col, int color){
	Reference<Location> ** squares = getSquares();
	vector<Reference<Location> > moves;
	if(existsPieceAt(row,col) 
		&& pieceAt(row,col)->getColor() == color){
		moves = getMoves(row,col);
		//no move possible; return NULL
		if(moves.size() == 0){
			return NULL;
		}
		return getComputerMove(squares[row][col],moves.at(0));
	}
	return NULL;
}

Move * Game::getComputerMove(Reference<Location> start, Reference<Location> end){
	cout << "gettingMoves 3" << endl;
	Move * move;
	Reference<Location> ** squares = getSquares();
	
	if(existsPieceAt(end->getRow(), end->getCol()))
		move = new Move(start, end, pieceAt(end->getRow(),end->getCol()));
	else
		move = new Move(start, end);
	cout << "returning move from " << start->getRow() << "," << start->getCol() <<
		" to " << end->getRow() << "," << end->getCol() << endl;
	return move;
	//execute(move);
}

void Game::writeXML(string fileName){
	ofstream out(fileName.c_str());
	if(!out)
		throw FileException("Couldn't open file for writing XML: " + fileName);
	XML xml(&out, &cerr);
	xml.openTag("chessgame");
		board->WriteXML(&xml);
		WriteHistoryXML(&xml);
	xml.closeTag();
}

void Game::WriteHistoryXML(XML* xml){
	xml->openTag("history");
		vector<Move*>::iterator it;
		vector<string> atts;
		for (int i = 0; i < history->size(); i++){
			xml->openTag("move");
				Board::WriteLocXML(xml,history->at(i)->getStart());
				Board::WriteLocXML(xml,history->at(i)->getEnd());
			xml->closeTag();
		}
	xml->closeTag();
}

int Game::getHistorySize(){
	return history->size();
}
