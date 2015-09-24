#include "IPiece.h"
#include "Location.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"
#include "Board.h"
#include <vector>

using namespace std;

//!This file includes the methods which are common to all pieces


ImageName IPiece::getType(){
	//cout << "returning type!: " << type << endl;
	return type;
}

int IPiece::getColor(){
	return color;
}

//!@return true if the space is not occupied by a piece of the same color and is not out of bounds
bool IPiece::moveOkay(Reference<Location>** squares, int row, int col){
	if(!Board::inBounds(row, col))
		return false;
	IPiece* piece = squares[row][col]->getPiece();
	if(piece != NULL)
		return piece->getColor() != color;
	//cout << "empty space okay to move into" << endl;
	return true;
}

void IPiece::getCrossMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){
	getHorizontalMoves(squares, moves, row, col);
	getVerticalMoves(squares, moves, row, col);
	//cout << "crossmoves: " << moves->size() << endl;
}

void IPiece::getHorizontalMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){
	
	//get moves right
	//start at one row right; add location one row right until a piece is encountered
	for(int i = col + 1; i < BOARD_SIZE; i++){
		if(squares[row][i]->getPiece() != NULL){
			//can move to a square with an enemy piece, but no past it
			if(moveOkay(squares, row, i)){
				moves->insert(moves->end(),squares[row][i]);
			}
			break;
		}else
			moves->insert(moves->end(),squares[row][i]);
		//cout << "Right: " << moves->size() << endl;
	}
	
	//get moves left
	//start at one row left; add location one row left until a piece is encountered
	for(int i = col -1; i > -1; i--){
		if(squares[row][i]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, row, i)){
				moves->insert(moves->end(),squares[row][i]);
				//cout << "Left: " << moves->size() << endl;
			}
			break;
		}else
			moves->insert(moves->end(),squares[row][i]);
		//cout << "Left: " << moves->size() << endl;
	}
	//cout << "horizontal: " << moves->size() << endl;
	return;
}

void IPiece::getVerticalMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){

	//get moves up
	//start at one row up; add location one row up until a piece is encountered
	for(int i = row + 1; i < BOARD_SIZE; i++){
		//if(!Board::inBounds
		if(squares[i][col]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, col)){
				moves->insert(moves->end(),squares[i][col]);
				//cout << "Left1: " << moves->size() << endl;
			}
			break;
		}else{
			//cout << "adding move to no-piece loc at " << i << ", " << col << endl;
			moves->insert(moves->end(),squares[i][col]);
		}
		//cout << "Left2: " << moves->size() << endl;
	}
	
	//get moves down
	//start at one row down; add location one row down until a piece is encountered
	for(int i = row - 1; i > -1; i--){
		if(squares[i][col]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, col)){
				moves->insert(moves->end(),squares[i][col]);
			}
			break;
		}else
			moves->insert(moves->end(),squares[i][col]);
	}
	//cout << "vertical: " << moves->size() << endl;
	return;
}


void IPiece::getDiagonalMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){
	getLRdiagonalMoves(squares, moves, row, col);
	getRLdiagonalMoves(squares, moves, row, col);
	//cout << "diag: size is " << moves->size() << endl;
}

//bottom to top, left to right diagonal
void IPiece::getLRdiagonalMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){
	//upper right
	for(int i = row + 1, j = col + 1; i < BOARD_SIZE && j < BOARD_SIZE; i++,j++){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, j)){
				moves->insert(moves->end(),squares[i][j]);
			}
			break;
		}else
			moves->insert(moves->end(),squares[i][j]);
	}
	//for(int i = 0; i < moves->size(); i++)
		//cout << moves->at(i)->getRow() << ", " << moves->at(i)->getCol() << endl;
	//cout << "moves is " << moves->size() << endl;
	//lower left
		for(int i = row - 1, j = col - 1; i > -1 && j > -1; i--,j--){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, j)){
				moves->insert(moves->end(),squares[i][j]);
			}
			break;
		}else
			moves->insert(moves->end(),squares[i][j]);
	}
	//for(int i = 0; i < moves->size(); i++)
		//cout << moves->at(i)->getRow() << ", " << moves->at(i)->getCol() << endl;
}

void IPiece::getRLdiagonalMoves(Reference<Location>** squares, vector< Reference<Location> > *
	moves, int row, int col){
	//upper left
	for(int i = row + 1, j = col - 1; i < BOARD_SIZE && j > -1; i++,j--){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, j)){
				moves->insert(moves->end(),squares[i][j]);
			}
			break;
		}else
			moves->insert(moves->end(),squares[i][j]);
	}
	//lower right
	for(int i = row - 1, j = col + 1; i > -1 && j < BOARD_SIZE; i--,j++){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(moveOkay(squares, i, j)){
				moves->insert(moves->end(),squares[i][j]);
				//cout << "adding " << i << ", " << j<< endl;
			}
			break;
		}else
			moves->insert(moves->end(),squares[i][j]);
	}
	//for(int i = 0; i < moves->size(); i++)
		//cout << moves->at(i)->getRow() << ", " << moves->at(i)->getCol() << endl;
}

