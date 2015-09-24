#ifndef CASTLE_H
#define CASTLE_H

#include "IPiece.h"
#include "ChessGuiDefines.h"
#include "Location.h"
#include "Referenceable.h"
#include "Reference.h"

#include <vector>

class Castle : public IPiece {
	
	public:
	
		//!needed for inheritance
		Castle();
		Castle(int color);
		
		~Castle();
		
		virtual std::vector<Reference<Location> > getMoves(Reference<Location>** squares,
		Reference<Location> loc);
		
		ImageName getType();
		
		int getColor();
		
	private:
		

};
#endif

