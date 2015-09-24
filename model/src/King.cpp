#include "King.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Board.h"

#include <vector>
#include <iostream>
using namespace std;
	
King::King(int col){
	color = col;
	if(col == WHITE)
		type = W_KING;
	else
		type = B_KING;
}

King::~King(){}

std::vector<Reference<Location> > King::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	vector<Reference<Location> > moves;
	int row = loc->getRow();
	int col = loc->getCol();
	//cout << "king: starting from " << row << ", " << col << endl;
	
	//grab eight moves from around the king; row and column difference range between -1 and 1
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			//can't move to current spot
			if(i == 0 && j == 0){
				//cout << "king: continuing" << endl;
				continue;
			}
			//cout << "considering " << row+i << ", " << col+j << endl;
			if(moveOkay(squares, row+i, col+j)){
				//cout << "adding " << row+i << ", " << col+j << endl;
				moves.insert(moves.end(),squares[row+i][col+j]);
			}
		}	
	}
	//cout << "King: returning these: " << endl;
	for(int i = 0; i < moves.size(); i++)
		cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol()  << endl;
	return moves;
}

bool King::check(Reference<Location> ** squares, Reference<Location> loc){
	//cout << "king: checking" << endl;
	if(checkKnight(squares, loc))
		return true;
	cout << "got here!1" << endl;
	if(checkPawn(squares, loc))
		return true;
	cout << "got here!2" << endl;
	if(checkKing(squares, loc))
		return true;
	cout << "got here!3" << endl;
	if(checkQB(squares, loc))
		return true;
	cout << "got here!4" << endl;
	if(checkQC(squares, loc))
		return true;
	cout << "got here!5" << endl;
	return false;
}

bool King::contains(Reference<Location> loc, ImageName type){
	//cout << "check loc" << endl;
	if(loc->getPiece() == NULL)
		return false;
	return loc->getPiece()->getType() == type;
}

//!@return true if a knight puts the king in check
bool King::checkKnight(Reference<Location> ** squares, Reference<Location> loc){
	int moveLong[3] = {-2,2};
	int moveShort[3] = {-1,1};
	
	ImageName searchType = (color == WHITE ? B_KNIGHT : W_KNIGHT);
	
	int row = loc->getRow();
	int col = loc->getCol();
	//cout << "starting from " << row << ", " << col << endl;
	
	int row2;
	int col2;
	
	//row is 2 different
	for(int i = 0; i <2; i++){
		for(int j = 0; j < 2; j++){
			row2 = moveLong[i] + row;
			col2 = moveShort[j] + col;
			if(Board::inBounds(row2,col2) && contains(squares[row2][col2],searchType))
				return true;
			//cout << "nothin' yet!" << endl;
		}
	}
	
	//col is 2 different
	for(int i = 0; i <2; i++){
		for(int j = 0; j < 2; j++){
			row2 = moveShort[i] + row;
			col2 = moveLong[j] + col;
			if(Board::inBounds(row2,col2) && contains(squares[row2][col2],searchType))
				return true;
		}
	}
	//cout << "knight check: returning false" << endl;
	return false;
}

//!@return true if a pawn puts the king in check
bool King::checkPawn(Reference<Location> ** squares, Reference<Location> loc){
	int direction = color == BLACK ? BLACK_DIRECTION : WHITE_DIRECTION;
	int currentRow = loc->getRow();
	int currentCol = loc->getCol();
	
	ImageName searchType = (color == WHITE ? B_PAWN : W_PAWN);
	
	//check two in front for unmoved pawns
	int rowTemp = currentRow + 1*direction;
	if(Board::inBounds(rowTemp,currentCol+1) &&
		contains(squares[rowTemp][currentCol+1], searchType))
		return true;
	if(Board::inBounds(rowTemp,currentCol-1) &&
		contains(squares[rowTemp][currentCol-1], searchType))
		return true;
	//else
		//cout << "no pawn threat from " << rowTemp << "," << currentCol << endl; 
	//check diags in front
	return false;
}

//!@return true if a king puts the king in check
bool King::checkKing(Reference<Location> ** squares, Reference<Location> loc){
	int currentRow = loc->getRow();
	int currentCol = loc->getCol();
	
	ImageName searchType = (color == WHITE ? B_KING : W_KING);
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			//can't move to current spot
			if(i == 0 && j == 0){
				//don't check self
				continue;
			}
			//cout << "considering " << row+i << ", " << col+j << endl;
			if(Board::inBounds(currentRow+i,currentCol+j) &&
				contains(squares[currentRow+i][currentCol+j], searchType))
				return true;
			}
		}
	return false;
}

//!@return true if a queen or bishop put the king in check
bool King::checkQB(Reference<Location> ** squares, Reference<Location> loc){
	
	if(checkQBLR(squares, loc))
		return true;
		
	cout << "got here 6!" << endl;
	if(checkQBRL(squares, loc))
		return true;
	cout << "got here 7!" << endl;
	return false;
}

bool King::checkQBLR(Reference<Location> ** squares, Reference<Location> loc){
	
	int row = loc->getRow();
	int col = loc->getCol();
	ImageName searchType1 = (color == WHITE ? B_BISHOP : W_BISHOP);
	ImageName searchType2 = (color == WHITE ? B_QUEEN : W_QUEEN);
	//upper left
	for(int i = row + 1, j = col - 1; i < BOARD_SIZE && j > -1; i++,j--){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][j], searchType1) ||
				contains(squares[i][j], searchType2) )
				return true;
			cout << "in ul path: " << squares[i][j]->getPiece()->getType() << endl;
			break;
		}
	}
	//lower right
	for(int i = row - 1, j = col + 1; i > -1 && j < BOARD_SIZE; i--,j++){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][j], searchType1) ||
				contains(squares[i][j], searchType2) )
				return true;
			cout << "in lr path: " << squares[i][j]->getPiece()->getType() << endl;
			break;
		}
	}
	return false;
}
bool King::checkQBRL(Reference<Location> ** squares, Reference<Location> loc){
	
	int row = loc->getRow();
	int col = loc->getCol();
	ImageName searchType1 = (color == WHITE ? B_BISHOP : W_BISHOP);
	ImageName searchType2 = (color == WHITE ? B_QUEEN : W_QUEEN);
	//upper right
	for(int i = row + 1, j = col + 1; i < BOARD_SIZE && j < BOARD_SIZE; i++,j++){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][j], searchType1) ||
				contains(squares[i][j], searchType2) )
				return true;
			cout << "in ur path: " << squares[i][j]->getPiece()->getType() << endl;
			break;
		}
	}
	
	//lower left
	for(int i = row - 1, j = col - 1; i > -1 && j > -1; i--,j--){
		if(squares[i][j]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][j], searchType1) ||
				contains(squares[i][j], searchType2) )
				return true;
			cout << "in ll path: " << squares[i][j]->getPiece()->getType() << endl;
			break;
		}
	}
	return false;
}


//!@return true if a queen or castle put the king in check
bool King::checkQC(Reference<Location> ** squares, Reference<Location> loc){
	if(checkQCH(squares, loc))
		return true;
	cout << "got here 8!" << endl;
	if(checkQCV(squares, loc))
		return true;
	cout << "got here 9!" << endl;
	return false;
}

bool King::checkQCH(Reference<Location> ** squares, Reference<Location> loc){
	int row = loc->getRow();
	int col = loc->getCol();
	ImageName searchType1 = (color == WHITE ? B_ROOK : W_ROOK);
	ImageName searchType2 = (color == WHITE ? B_QUEEN : W_QUEEN);
	
	//get moves right
	//start at one row right; add location one row right until a piece is encountered
	for(int i = col + 1; i < BOARD_SIZE; i++){
		if(squares[row][i]->getPiece() != NULL){
			//can move to a square with an enemy piece, but no past it
			if(contains(squares[row][i], searchType1) ||
				contains(squares[row][i], searchType2) ){
					cout << "check by " << squares[row][i]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
				return true;
			}
			cout << "checkQC3 blocked by " << squares[row][i]->getPiece()->getType()
				<< "at " << row << "," << i << endl;
			break;
		//cout << "Right: " << moves->size() << endl;
		}
	}
	
	//get moves left
	//start at one row left; add location one row left until a piece is encountered
	for(int i = col -1; i > -1; i--){
		if(squares[row][i]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[row][i], searchType1) ||
				contains(squares[row][i], searchType2) ){
					cout << "check by " << squares[row][i]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
				return true;
			}
			cout << "checkQC4 blocked by " << squares[row][i]->getPiece()->getType()
				<< "at " << row << "," << i << endl;
			break;
		//cout << "Left: " << moves->size() << endl;
		}
	}
	return false;
}

bool King::checkQCV(Reference<Location> ** squares, Reference<Location> loc){
	int row = loc->getRow();
	int col = loc->getCol();
	ImageName searchType1 = (color == WHITE ? B_ROOK : W_ROOK);
	ImageName searchType2 = (color == WHITE ? B_QUEEN : W_QUEEN);
	//get moves up
	for(int i = row + 1; i < BOARD_SIZE; i++){
		//if(!Board::inBounds
		if(squares[i][col]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][col], searchType1) ||
				contains(squares[i][col], searchType2) ){
					cout << "check by " << squares[i][col]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
				return true;
			}
			cout << "checkQC1 blocked by " << squares[i][col]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
			break;
		}
		//cout << "Left2: " << moves->size() << endl;
	}
	cout << "got here 10" << endl;
	//get moves down
	//start at one row down; add location one row down until a piece is encountered
	for(int i = row - 1; i > -1; i--){
		if(squares[i][col]->getPiece() != NULL){
			//can move to a square with an enemy piece, but not past it
			if(contains(squares[i][col], searchType1) ||
				contains(squares[i][col], searchType2) ){
					cout << "check by " << squares[i][col]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
				return true;
			}
			cout << "checkQC2 blocked by " << squares[i][col]->getPiece()->getType() <<
				"at " << i << "," << col << endl;
			break;
		}
	}
	return false;
}

