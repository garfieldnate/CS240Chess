#ifndef I_PIECE_H
#define I_PIECE_H

#include <vector>
#include <iostream>

#include "Location.h"
#include "ChessGuiDefines.h"
#include "Referenceable.h"
#include "Reference.h"

class Location;

//!This class will form the base for King, Queen, Knight, Bishop, Castle and Pawn. All of them
//!must have their own constructors and destructors, a getMoves function, and a test function.
class IPiece{
	
	public:
	
		//IPiece(){};
	
		virtual ~IPiece(){};
		
		//pass in pointer to entire board; important for pawn, which must see other pieces.
		virtual std::vector<Reference<Location> > getMoves(Reference<Location>** squares,
			Reference<Location> loc)=0;
		
		//!@return type of piece, i.e. W_PAWN, B_KING, etc.
		ImageName getType();
		
		//!@return color of piece as defined in ChessConstants.h
		int getColor();
		
	protected:
		//1 for black, 0 for white
		int color;
		
		ImageName type;
		
		//!@param squares 2d array of locations
		//!@param row of move location
		//!@param column of move location
		//!@return true the location is not occupied by a piece of the same color
		virtual bool moveOkay(Reference<Location>** squares, int row, int col);
		
		//!@param squares 3d array of locations representing the board
		//!@param moves a structure to store possible moves in
		//!@param row the row of the piece
		//!@param col the column of the piece
		//!adds possible diagonal moves to vector of moves
		void getDiagonalMoves(Reference<Location>** squares, std::vector<Reference<Location> > *
			moves, int row, int col);
	
		//!@param squares 3d array of locations representing the board
		//!@param moves a structure to store possible moves in
		//!@param row the row of the piece
		//!@param col the column of the piece
		//!adds possible vertical and horizontal moves of the piece
		void getCrossMoves(Reference<Location>** squares, std::vector<Reference<Location> > *
			moves, int row, int col);
	
	private:
	
		//!@param squares 3d array of locations representing the board
		//!@param moves a structure to store possible moves in
		//!@param row the row of the piece
		//!@param col the column of the piece
		//!adds possible vertical moves to vector of moves
		void getVerticalMoves(Reference<Location>** squares, std::vector<Reference<Location> > *
			moves, int row, int col);
		
		//!@param squares 3d array of locations representing the board
		//!@param moves a structure to store possible moves in
		//!@param row the row of the piece
		//!@param col the column of the piece
		//!adds possible horizontal moves to vector of moves
		void getHorizontalMoves(Reference<Location>** squares, std::vector<Reference<Location> >
			* moves, int row, int col);
	
		//!returns left to right diagonal moves (bottom to top)
		void getLRdiagonalMoves(Reference<Location>** squares, std::vector<Reference<Location> >
			* moves, int row, int col);
		
		//!returns right to left diagonal moves (bottom to top)
		void getRLdiagonalMoves(Reference<Location>** squares, std::vector<Reference<Location> >
			* moves, int row, int col);
};
#endif

