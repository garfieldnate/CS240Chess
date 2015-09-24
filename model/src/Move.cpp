#include "Move.h"
#include "Reference.h"
#include "Referenceable.h"
#include "Location.h"
#include "IPiece.h"


	//!use this for moves where pieces were not captured
	Move::Move(Reference<Location> s, Reference<Location> e):captured(NULL){
		start = s;
		end = e;
	}
	
	//!use this for moves where pieces were captured
	Move::Move(Reference<Location> s, Reference<Location> e, IPiece* c){
		start = s;
		end = e;
		captured = c;
	}
	
	Move::~Move(){}

	Reference<Location> Move::getStart(){
		return start;
	}
	
	Reference<Location> Move::getEnd(){
		return end;
	}
	
	//!@return piece that was captured during the move
	IPiece* Move::getCaptured(){
		return captured;
	}
	
	//!@return piece that was captured during the move
	void Move::setCaptured(IPiece* piece){
		captured = piece;
	}

