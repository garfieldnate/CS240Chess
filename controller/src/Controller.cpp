#include "Controller.h"
#include <iostream>
#include "ChessView.h"
#include "History.h"
#include "Move.h"
#include "Location.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include "assert.h"

using namespace std;

Controller::Controller(char * playerType1, char * playerType2):view(NULL),
		game(NULL),turn(WHITE),currentFileName(""){
			
	selectedLocs = new vector<Reference<Location> >();
	if(strcmp(playerType1, "h") == 0)
		playerTypes[0] = HUMAN;
	else
		playerTypes[0] = COMPUTER;
		
	if(strcmp(playerType2, "h") == 0)
		playerTypes[1] = HUMAN;
	else
		playerTypes[1] = COMPUTER;
	cout << "Controller: Hi there!" << endl;
}

Controller::~Controller(){
	if(game != NULL)
		delete game;
	delete selectedLocs;
}

void Controller::on_CellSelected(int row, int col, int button){
	//ignore the player during the computer's turn
	if(playerTypes[turn] == COMPUTER){
		cout << "playerTypes[" << turn << "] is " << playerTypes[turn] << endl;
		return;
	}
	
	//if the space is highlighted, do the move; otherwise check for moves
	vector<Reference<Location> >::iterator contained = find(selectedLocs->begin(),
		selectedLocs->end(),game->getSquares()[row][col]);
	//location is highlighted
	if(contained != selectedLocs->end()){
		cout << "gonna move!~" << endl;
		//move piece
		//grab piece to capture if there is one
		Move * move;
		if(game->existsPieceAt(row, col))
			move = new Move(selectedLoc, game->locAt(row,col), game->pieceAt(row,col));
		else
			move = new Move(selectedLoc, game->locAt(row,col));
		game->execute(move);
		
		//clear saved selections
		selectedLocs->clear();
		selectedLoc = NULL;
		unhighlightAll();
		refreshBoard();
		changeTurn();
	}
	//location was not highlighted; check for moves
	else if(game->existsPieceAt(row, col) && game->pieceAt(row, col)->getColor() == turn){
		
		//unhighlight everything first
		unhighlightAll();
		
		//save the piece that was selected by the player
		selectedLoc = game->getSquares()[row][col];
		
		vector<Reference<Location> > moves = game->getMoves(row,col);
		
		//then highlight moves and save them in selectedLocs
		cout << "controller: gettin moves" << endl;
		for(int i = 0; i < moves.size(); i++){
			cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol() << endl;
			view->HighlightSquare(moves.at(i)->getRow(),moves.at(i)->getCol(),BLUE_SQUARE);
			selectedLocs->insert(selectedLocs->end(),moves.at(i));
		}
		
	}
}

void Controller::on_DragStart(int row,int col){
	cout << "Dragging" << endl;
}

bool Controller::on_DragEnd(int row,int col){}

//!clear history, reset board
void Controller::on_NewGame(){
	cout << "on_New Game!" << endl;
	//new game
	if(game != NULL)
		delete game;
	game = new Game();
	
	//reset the board on the GUI
	refreshBoard();
	unhighlightAll();
	view->SetBottomLabel("white's turn");
	turn = WHITE;
}

void Controller::unhighlightAll(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			view->UnHighlightSquare(i,j);
		}
	}
	selectedLocs->clear();
	selectedLoc = NULL;
}

void Controller::refreshBoard(){
	Reference<Location>** squares = game->getSquares();
	assert(squares != NULL);
	
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			//clear spaces without pieces
			if(squares[i][j]->getPiece() == NULL)
				view->ClearPiece(i,j);
			//update view with correct piece image
			else{
				cout << "painting piece " << i << "," << j << endl;
				view->PlacePiece(i, j, squares[i][j]->getPiece()->getType());
			}
		}
	}
}

//!if not saved yet, choose file
//!write xml to selected file
void Controller::on_SaveGame(){
	if(currentFileName == "")
		on_SaveGameAs();
	else
		game->writeXML(currentFileName);
}

//!choose file
//!write xml to selected file
void Controller::on_SaveGameAs(){
	currentFileName = view->SelectSaveFile();
	game->writeXML(currentFileName);
}

//!choose file
//!read xml file, executing all moves
void Controller::on_LoadGame(){
	if(game != NULL)
		delete game;
		
	string fileName = view->SelectLoadFile();
	//if(string == string
	game = new Game(fileName);
	refreshBoard();
	cout << "finished refreshing" << endl;
	unhighlightAll();
	cout << "finished unhighlighting" << endl;
	turn = (game->getHistorySize() +1) % 2;
	changeTurn();
	
}

//!pop last move from history
//!move back
//!if captured, uncapture
void Controller::on_UndoMove(){
	//switch turns and refresh only if a turn was undone
	if(!game->undo())
		return;
	refreshBoard();
	unhighlightAll();
	changeTurn();
	//cout << "should have unhilited" << endl;
}

//!optional: ask to save if not saved
void Controller::on_QuitGame(){}

//!If it is the computer's turn, generate a move randomly
void Controller::on_TimerEvent(){
	if(playerTypes[turn] != COMPUTER)
		return;
	//cout << "computer moving" << endl;
	Move * move = game->getComputerMove(turn);
	assert(move != NULL);
	//if(move == NULL)
		//cout << "NOOOO!" << endl;
	//cout << "got here1" << endl;
	game->execute(move);
	//cout << "got here2" << endl;
	refreshBoard();
	//cout << "got here3" << endl;
	changeTurn();
	//cout << "got here4" << endl;
}

void Controller::SetView(IChessView* chessView){
	view = chessView;
}

void Controller::changeTurn(){
	//if 1 then zero, if zero then 1
	turn = (turn + 1) % 2;
	cout << "Controller: changed turn to " << turn << endl;
	string text = (turn == WHITE ? WHITE_TEXT : BLACK_TEXT);
	view->SetBottomLabel(text + "'s turn");
	
	if(game->isCheck(turn)){
		//check for checkmate
		if(game->noMoves(turn))
			view->SetBottomLabel(text + ": you are in checkmate!");
		else
			view->SetBottomLabel(text + ": you are in check!");
	}
	else{
		if(game->noMoves(turn))
			view->SetBottomLabel(text + ": you are in stalemate");
		cout << "not check!" << endl;
	}
}

//Use case
	//New game
		//1. click
		//2. newgame in model
		//3. display board
	//Save game
		//1. click
		//2. file select
		//3. tell model to save
	//Load game
		//1. click
		//2. file select
		//3. tell model to load
		//4. display board
	//Move
		//click square
			//first click on a piece:
				//get moves from model
				//tell view to highlight squares
				//set SELECTED flag
		//click square
			//second time it's clicked:
				//move piece (model)
				//move piece (view)
				//clear flag
