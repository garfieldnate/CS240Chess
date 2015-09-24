#include "Board.h"
#include "Castle.h"
#include "Knight.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Pawn.h"
#include "ChessConstants.h"
#include "ChessGuiDefines.h"
#include "Referenceable.h"
#include "Reference.h"
#include "XML.h"

#include <iostream>
#include <sstream>
#include "assert.h"

using namespace std;

const string Board::pieceNames[] = {"","","","","pawn","pawn","rook","rook","knight","knight",
	"bishop","bishop","king","king","queen","queen"};
const string Board::colorNames[] = {"white","black"};

bool Board::inBounds(int row, int col){
	//cout << "got here -2" << endl;
	//cout << "checking that " << row << " and " << col << " are smaller than " << BOARD_SIZE << endl;
	//cout << "creating board" << endl;
	return row < BOARD_SIZE && row > -1 && col < BOARD_SIZE && col > -1;
}

Board::Board():allocCount(0){
	//cout << "Creating new Board" << endl;
	//allocate an 8x8 array of location pointers
	locations = new Reference<Location>*[BOARD_SIZE];
	for(int i = 0; i < BOARD_SIZE; i++){
		locations[i] = new Reference<Location>[BOARD_SIZE];
		allocCount++;
		for(int j = 0; j < BOARD_SIZE; j++){
			//cout << "creating a location reference" << endl;
			locations[i][j] = new Location(i,j);
			allocCount++;
		}
	}
	makePieces();
	//pieceNames = new string[16];
	//{"","","","","pawn","pawn","rook","rook","knight","knight",
			//"bishop","bishop","king","king","queen","queen"};
}
	
void Board::makePieces(){
	//cout << "making pieces!" << endl;
	//create pieces array
	pieces = new IPiece * [ NUM_OF_PIECES ];
	kings = new IPiece * [2];
	
	//create pieces and place them in the correct location
	int temp = 0;
	//white pieces
	pieces[temp++] = new Castle(WHITE);
	locations[WHITE_MAIN_ROW][CASTLE_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Knight(WHITE);
	locations[WHITE_MAIN_ROW][KNIGHT_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Bishop(WHITE);
	locations[WHITE_MAIN_ROW][BISHOP_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Queen(WHITE);
	locations[WHITE_MAIN_ROW][QUEEN_LOC]->setPiece(pieces[temp-1]);
	
	pieces[temp++] = new King(WHITE);
	kings[WHITE] = pieces[temp-1];
	//cout << pieces[temp]->getType();
	//cout << kings[WHITE]->getType();
	
	locations[WHITE_MAIN_ROW][KING_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Bishop(WHITE);
	locations[WHITE_MAIN_ROW][BISHOP_2_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Knight(WHITE);
	locations[WHITE_MAIN_ROW][KNIGHT_2_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Castle(WHITE);
	locations[WHITE_MAIN_ROW][CASTLE_2_LOC]->setPiece(pieces[temp-1]);
	
	//white pawns
	for(int i = 0; i < BOARD_SIZE; i++){
		pieces[temp++] = new Pawn(WHITE);
		locations[WHITE_PAWN_ROW][i]->setPiece(pieces[temp-1]);
	}
	
	//black pieces
	pieces[temp++] = new Castle(BLACK);
	locations[BLACK_MAIN_ROW][CASTLE_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Knight(BLACK);
	locations[BLACK_MAIN_ROW][KNIGHT_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Bishop(BLACK);
	locations[BLACK_MAIN_ROW][BISHOP_1_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Queen(BLACK);
	locations[BLACK_MAIN_ROW][QUEEN_LOC]->setPiece(pieces[temp-1]);
	
	pieces[temp++] = new King(BLACK);
	kings[BLACK] = pieces[temp-1];
	
	locations[BLACK_MAIN_ROW][KING_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Bishop(BLACK);
	locations[BLACK_MAIN_ROW][BISHOP_2_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Knight(BLACK);
	locations[BLACK_MAIN_ROW][KNIGHT_2_LOC]->setPiece(pieces[temp-1]);
	pieces[temp++] = new Castle(BLACK);
	locations[BLACK_MAIN_ROW][CASTLE_2_LOC]->setPiece(pieces[temp-1]);
	
	//black pawns
	for(int i = 0; i < BOARD_SIZE; i++){
		pieces[temp++] = new Pawn(BLACK);
		locations[BLACK_PAWN_ROW][i]->setPiece(pieces[temp-1]);
	}
	//cout << "Placed " << temp << " pieces; should have placed " << NUM_OF_PIECES << endl;
	assert(temp == 32);
}
	
Board::~Board(){
	//loop through board and delete all location pointers
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			//don't need to explicitly delete with References
			//delete locations[i][j];
			//allocCount--;
		}
		delete [] locations[i];
		allocCount--;
	}
	//cout << "allocCount is " << allocCount << endl;
	delete [] locations;
	
	for(int i = 0; i < NUM_OF_PIECES; i++)
		delete pieces[i];
	
	delete [] kings;
	
	delete [] pieces;
	
	//delete  pieceNames;
}
	
bool Board::existsPieceAt(int row, int col){
	return locations[row][col]->getPiece() != NULL;
}

IPiece* Board::pieceAt(int row, int col){
	return locations[row][col]->getPiece();
}

Location* Board::getSquare(int row, int col){
	return locations[row][col];
}

Reference<Location>** Board::getAllSquares(){
	return locations;
}

vector<Reference<Location> > Board::getMoves(int row, int col){
	vector<Reference<Location> > moves;
	if(!existsPieceAt(row,col))
		return moves;
	moves = locations[row][col]->getPiece()->getMoves(locations, locations[row][col]);
	cout << "Board: getting moves" << endl;
	for(int i = 0; i < moves.size(); i++)
		cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol()  << endl;
	return moves;
}

King * Board::getKing(int color){
	cout << "grabbing king of color " << color << endl;
	return (King*) kings[color];
}

Reference<Location> Board::getLoc(ImageName type){
	cout << "board: finding" << endl;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(locations[i][j]->getPiece() != NULL &&
				locations[i][j]->getPiece()->getType() == type)
				return locations[i][j];
		}
	}
	return NULL;
}

void Board::WriteXML(XML* xml){
	xml->openTag("board");
	vector<string> atts;
	stringstream num;
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(locations[i][j]->getPiece() != NULL){
				WritePieceXML(xml,locations[i][j]);
			}
		}
	}
	xml->closeTag();
}

//mine doesn't use piece information
void Board::WriteLocXML(XML* xml, Reference<Location> loc){
	vector<string> atts;
	stringstream num;
	
	atts.insert(atts.end(),"row");
	num << loc->getRow();
	atts.insert(atts.end(),num.str());
	
	num.str("");
	
	num << loc->getCol();
	atts.insert(atts.end(),"column");
	atts.insert(atts.end(),num.str());
	
	num.str("");
	
	xml->openTag(string("piece"),&atts,true);
}

void Board::WritePieceXML(XML* xml, Reference<Location> loc){
	vector<string> atts;
	stringstream num;
	
	atts.insert(atts.end(),"type");
	atts.insert(atts.end(),pieceNames[loc->getPiece()->getType()]);
	
	atts.insert(atts.end(),"color");
	atts.insert(atts.end(),colorNames[loc->getPiece()->getColor()]);
	
	atts.insert(atts.end(),"row");
	num << loc->getRow();
	atts.insert(atts.end(),num.str());
	
	num.str("");
	
	num << loc->getCol();
	atts.insert(atts.end(),"column");
	atts.insert(atts.end(),num.str());
	
	num.str("");
	
	xml->openTag(string("piece"),&atts,true);
	
}
