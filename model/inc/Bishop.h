#ifndef BISHOP_H
#define BISHOP_H

#include "IPiece.h"
#include "ChessGuiDefines.h"

#include <vector>

class Bishop : public IPiece {
	
	public:
	
		//!needed for inheritance
		Bishop();
		Bishop(int color);
		
		~Bishop();
		
		virtual std::vector<Reference<Location> > getMoves(Reference<Location>** squares,
			Reference<Location> loc);
		
		ImageName getType();
		
		int getColor();
	
	private:
};
#endif

