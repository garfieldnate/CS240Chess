#ifndef GAME_H
#define GAME_H

#include <set>

#include "IPiece.h"
#include "King.h"
#include "Board.h"
#include "History.h"
#include "Referenceable.h"
#include "Reference.h"
#include "Move.h"
#include "XML.h"
#include <vector>
#include <string>

//!This class acts as a facade between the controller and the entire model layer.
class Game{
	
	public:
	
		Game();
		
		//!@param name of file to load
		Game(std::string fileName);
		
		~Game();
		
		//!@return piece at location given by row and column
		IPiece* pieceAt(int row, int col);
		
		//!@return true if there is a piece at the location
		bool existsPieceAt(int row, int col);
		
		//!
		std::vector<Reference<Location> > getMoves(int row, int col);

		//!@return 2d array of Location pointers
		Reference<Location>** getSquares();
		
		//!@return true if king of this color is in check
		bool isCheck(int color);
		
		//!@return true if checkmate is achieved
		bool noMoves(int color);
		
		//!@return true if stalemate is achieved
		bool isStaleMate();
		
		//!@return location at given row and column
		Reference<Location> locAt(int row, int col);
		
		//!@param move to execute
		//!executes move and adds it to the history
		void execute(Move * move);
		
		//!@param move to undo
		//!@return true if a move was undone
		//!undoes the move and removes it from the history
		bool undo();
		
		//!@return terrible move for a piece of this color
		Move * getComputerMove(int color);
		
		void writeXML(std::string fileName);
		
		void WriteHistoryXML(XML* xml);
		
		int getHistorySize();
	private:
		
		//!@return move by piece at loc
		Move * getComputerMove(int row, int col, int color);
		
		//!@return move from start to end
		Move * getComputerMove(Reference<Location> start, Reference<Location> end);
		
		//!get rid of moves that place the moving piece's player in check
		void filter(std::vector<Reference<Location> > * locs, int row,int col);
		Board * board;
		std::vector<Move * > * history;
		
		void executeLoaded(Move * move);
};
#endif

