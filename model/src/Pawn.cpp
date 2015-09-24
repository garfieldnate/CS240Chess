#include "Pawn.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"
#include "Board.h"

#include <vector>
#include <iostream>

using namespace std;
	
Pawn::Pawn(int col):moved(false){
	color = col;
	//cout << "Color is " << color << endl;
	if(color == WHITE)
		type = W_PAWN;
	else
		type = B_PAWN;
}

Pawn::~Pawn(){}

void Pawn::incrementMoved(){
	moved++;
}

void Pawn::decrementMoved(){
	moved--;
}

//pawn has the most complex moves;
//if first move, can go forward two; otherwise only one
//can only move forward into empty space
//can also move one diagonal forward to take a piece
vector<Reference<Location> > Pawn::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	//cout << "getting Pawn's moves" << endl;
	int currentRow = loc->getRow();
	int currentCol = loc->getCol();
	int rowTemp;
	vector<Reference<Location> > moves;
	
	//can move forward
	//1 forward
	rowTemp = currentRow+((color == WHITE ? WHITE_DIRECTION : BLACK_DIRECTION));
	if(moveOkay(squares, rowTemp, currentCol)){
		moves.insert(moves.end(),squares[rowTemp][currentCol]);
		//can also move two ahead if it's the first time
			if(moved == 0){
				//2 forward
				rowTemp = currentRow+(2*(color == WHITE ? WHITE_DIRECTION : BLACK_DIRECTION));
				if(moveOkay(squares, rowTemp, currentCol))
					moves.insert(moves.end(),squares[rowTemp][currentCol]);
				//remove 1 space in rowTemp to make diagonal checks correct
				rowTemp = rowTemp+(-1*(color == WHITE ? WHITE_DIRECTION : BLACK_DIRECTION));
					
				//cout << "1number of moves is now " << moves.size() << endl;
		}
	}
	
	//cout << "2number of moves is now " << moves.size() << endl;
	//can move diagonally forward to take a piece
	if(moveOkayDiag(squares, rowTemp, currentCol-1))
		moves.insert(moves.end(),squares[rowTemp][currentCol-1]);
	//cout << "3number of moves is now " << moves.size() << endl;
	if(moveOkayDiag(squares, rowTemp, currentCol+1))
		moves.insert(moves.end(),squares[rowTemp][currentCol+1]);
	//cout << "4number of moves is now " << moves.size() << endl;
		
	return moves;
}

bool Pawn::moveOkay(Reference<Location>** squares, int row, int col){
	if(!Board::inBounds(row, col)){
		cout << row << "," << col << " is out of bounds" << endl;
		return false;
	}
	if(squares[row][col]->getPiece() == NULL)
		return true;
	return false;
}

bool Pawn::moveOkayDiag(Reference<Location>** squares, int row, int col){
	//check bounds
	if(!Board::inBounds(row, col))
		return false;
	IPiece* piece = squares[row][col]->getPiece();
	if(piece != NULL){
		return piece->getColor()!=color;
	}
	return false;
}

