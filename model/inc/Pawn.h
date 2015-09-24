#ifndef PAWN_H
#define PAWN_H

#include "IPiece.h"
#include "ChessGuiDefines.h"
#include "Location.h"
#include "Referenceable.h"
#include "Reference.h"

#include <iostream>
#include <vector>

class Pawn : public IPiece {
	
	public:
	
		Pawn(int color);
		
		~Pawn();
		
		std::vector<Reference<Location> > getMoves(Reference<Location>** squares, 
			Reference<Location> loc);
		
		//!increment number of times pawn has moved
		void incrementMoved();

		//!decrement number of times pawn has moved
		void decrementMoved();
	
	private:
		//number of times the pawn has moved
		int moved;
		
		//!@return it's occupied by a piece; this is for pawn's forward move
		bool moveOkay(Reference<Location>** squares, int row, int col);
		
		//!@return true if the pawn can move diagonally here
		//!it's occupied by an enemy piece
		bool moveOkayDiag(Reference<Location>** squares, int row, int col);
};
#endif

