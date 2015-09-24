#ifndef QUEEN_H
#define QUEEN_H

#include "IPiece.h"
#include "ChessGuiDefines.h"
#include "Bishop.h"
#include "Castle.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>

class Queen : public IPiece{
	
	public:
	
	Queen(int color);
	
	~Queen();
	
	std::vector<Reference<Location> > getMoves(Reference<Location>** squares, 
		Reference<Location> loc);
	
	ImageName getType();
	
	int getColor();
	
	private:
	
};
#endif

