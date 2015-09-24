#include "Bishop.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>
#include <iostream>
using namespace std;
	
Bishop::Bishop(int col){
	color = col;
	if(col == WHITE)
		type = W_BISHOP;
	else
		type = B_BISHOP;
}

Bishop::~Bishop(){}

vector<Reference<Location> > Bishop::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	vector<Reference<Location> > moves;
	getDiagonalMoves(squares, &moves, loc->getRow(), loc->getCol());
	return moves;
}
