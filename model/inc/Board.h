#ifndef BOARD_H
#define BOARD_H

#include "Location.h"
#include "Referenceable.h"
#include "Reference.h"
#include "King.h"
#include "ChessGuiDefines.h"
#include "XML.h"

#include <vector>
#include <string>

//!The board is responsible for keeping track of locations and pieces.
class Board{
	
	public:
	
		Board();
		
		//!create pieces and place them in their initial positions
		void makePieces();
		
		~Board();
		
		//!@return true if a piece is located at a particular location
		bool existsPieceAt(int row, int col);
		
		//!@return pointer to piece at particular location
		IPiece* pieceAt(int row, int col);
		
		//!@return location object for a particular row and column
		Location* getSquare(int row, int col);
		
		//!@return 2d array of pointers to locations on the board
		Reference<Location>** getAllSquares();
		
		//!@return true if the row and column are within the bounds of the board
		static bool inBounds(int row, int col);
		
		//!@return vector of moves that can be made from the given location
		std::vector<Reference<Location> > getMoves(int row, int col);
		
		//!@return king of specific color
		King* getKing(int color);
	
		//!@return location of piece
		Reference<Location> getLoc(ImageName type);
		
		void WriteXML(XML* xml);
		
		static void WritePieceXML(XML* xml, Reference<Location> loc);
		
		static void WriteLocXML(XML* xml, Reference<Location> loc);
	private:
		//2D array of location pointers
		Reference<Location>** locations;
		//array of piece pointers; allows for memory managing them
		IPiece** pieces;
		IPiece** kings;
		int allocCount;
		static const std::string  pieceNames[];
		static const std::string  colorNames[];// = {"white","black"};
		
};
#endif

