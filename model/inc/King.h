#ifndef KING_H
#define KING_H

#include "IPiece.h"
#include "ChessGuiDefines.h"

#include <vector>

class King : public IPiece {
	
	public:
	
		King(int color);
		
		~King();
		
		std::vector<Reference<Location> > getMoves(Reference<Location>** squares,
			Reference<Location> loc);

		//!@return true if this king is in check
		//!@param squares the entire board
		//!@param loc the location of the king
		bool check(Reference<Location> ** squares, Reference<Location> loc);
		
		//!@return true if a knight puts the king in check
		bool checkKnight(Reference<Location> ** squares, Reference<Location> loc);
		
		//!@return true if a pawn puts the king in check
		bool checkPawn(Reference<Location> ** squares, Reference<Location> loc);
		
		//!@return true if a king puts the king in check
		bool checkKing(Reference<Location> ** squares, Reference<Location> loc);
		
		//!@return true if a queen or bishop put the king in check
		bool checkQB(Reference<Location> ** squares, Reference<Location> loc);
		
		
		//!@return true if a queen or castle put the king in check
		bool checkQC(Reference<Location> ** squares, Reference<Location> loc);
	private:
		//!@return true if the location contains piece type of piece
		bool contains(Reference<Location> loc, ImageName piece);
		
		bool checkQBLR(Reference<Location> ** squares, Reference<Location> loc);
		bool checkQBRL(Reference<Location> ** squares, Reference<Location> loc);
		
		bool checkQCH(Reference<Location> ** squares, Reference<Location> loc);
		bool checkQCV(Reference<Location> ** squares, Reference<Location> loc);
	
};
#endif

