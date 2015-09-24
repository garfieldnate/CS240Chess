#include "Castle.h"
#include "IPiece.h"
#include "Location.h"
#include "ChessGuiDefines.h"
#include "ChessConstants.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>
using namespace std;
	
	Castle::Castle(){}
	
Castle::Castle(int col){
	color = col;
	if(col == WHITE)
		type = W_ROOK;
	else
		type = B_ROOK;
}

Castle::~Castle(){}

vector<Reference<Location> > Castle::getMoves(Reference<Location>** squares,
	Reference<Location> loc){
	int row = loc->getRow();
	int col = loc->getCol();
	
	vector<Reference<Location> > moves;
	getCrossMoves(squares, &moves, row, col);
	
	return moves;
}
