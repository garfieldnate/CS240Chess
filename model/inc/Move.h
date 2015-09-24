#ifndef MOVE_H
#define MOVE_H
#include "Reference.h"
#include "Referenceable.h"
#include "Location.h"
#include "IPiece.h"

//! This class saves all of the important information about a move: the start and end locations
//! and any captured piece
class Move{
	
	public:
	
	//!use this for moves where pieces were not captured
	Move(Reference<Location> start, Reference<Location> end);
	
	//!use this for moves where pieces were captured
	Move(Reference<Location> start, Reference<Location> end, IPiece* captured);
	
	Reference<Location> getStart();
	
	Reference<Location> getEnd();
	
	//!@return piece that was captured during the move
	IPiece* getCaptured();
	
	void setCaptured(IPiece* piece);
	
	~Move();
		
	private:
		Reference<Location> start;
		Reference<Location> end;
		IPiece * captured;
};
#endif

