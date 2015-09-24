#ifndef KNIGHT_H
#define KNIGHT_H

#include "IPiece.h"
#include "ChessGuiDefines.h"

#include <vector>
class Knight : public IPiece {
	
	public:
		
		Knight(int color);
		
		~Knight();
		
		std::vector<Reference<Location> > getMoves(Reference<Location>** squares,
			Reference<Location> loc);
		
	private:
	
};
#endif

