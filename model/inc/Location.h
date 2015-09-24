#ifndef LOCATION_H
#define LOCATION_H
#include "Referenceable.h"

#include "IPiece.h"

class IPiece;


class Location : public Referenceable{
	
	public:
	
	
	Location();
	
	Location(int r, int c);
	
	~Location();
	
	//!@param int to set row to
	void setRow(int r);
	
	//!@param int to set column to
	void setCol(int c);
	
	//!@return the row number of the location, ranging 0-7
	int getRow();
	
	//!@return the row number of the location, ranging 0-7
	int getCol();
	
	//!@return pointer to the piece at this location 
	IPiece * getPiece();
	
	//!@param pointer to piece to put on this location
	void setPiece(IPiece* piece);
	
	//compare?
	
	const bool operator < (const Location & other) const;
	
	private:
		int row;
		int col;
		
		//piece at this location on the board
		IPiece * piece;
	
};

#endif

