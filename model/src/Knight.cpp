#include "Knight.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>
#include <iostream>
using namespace std;
	
Knight::Knight(int col){
	color = col;
	if(col == WHITE)
		type = W_KNIGHT;
	else
		type = B_KNIGHT;
}

Knight::~Knight(){}

std::vector<Reference<Location> > Knight::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	
	vector<Reference<Location> > moves;
	
	int moveLong[3] = {-2,2};
	int moveShort[3] = {-1,1};
	
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
			if(moveOkay(squares,row2,col2))
				moves.insert(moves.end(),squares[row2][col2]);
		}
	}
	//col is 2 different
	for(int i = 0; i <2; i++){
		for(int j = 0; j < 2; j++){
			row2 = moveShort[i] + row;
			col2 = moveLong[j] + col;
			if(moveOkay(squares,row2,col2))
				moves.insert(moves.end(),squares[row2][col2]);
		}
	}
	return moves;
}

