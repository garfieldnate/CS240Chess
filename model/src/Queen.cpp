#include "Queen.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>
using namespace std;
	
Queen::Queen(int col){
	color = col;
	if(col == WHITE)
		type = W_QUEEN;
	else
		type = B_QUEEN;
}

Queen::~Queen(){}

vector<Reference<Location> > Queen::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	vector<Reference<Location> > moves;
	getDiagonalMoves(squares, &moves, loc->getRow(), loc->getCol());
	getCrossMoves(squares, &moves, loc->getRow(), loc->getCol());
	return moves;
}
