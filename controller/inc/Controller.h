#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "IChessController.h"
#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "History.h"
#include "King.h"
#include "IPiece.h"
#include "Referenceable.h"
#include "Reference.h"
#include "Location.h"

#include <vector>

class Controller : public IChessController{
	public:
	
		Controller(char * playerType1, char * playerType2);
		
		~Controller();
		
		void on_CellSelected(int row, int col, int button);
		
		void on_DragStart(int row,int col);
		
		bool on_DragEnd(int row,int col);
		
		//!clears history and resets board
		void on_NewGame();
		
		//!same as "save as" if never saved before;
		//!otherwise simply saves in same location as last time
		void on_SaveGame();
		
		//!save game in chosen file as XML
		void on_SaveGameAs();
		
		//!load a previously saved game XML file
		void on_LoadGame();
		
		//!pop last move from history and reverse it;
		//!uncapture any captured pieces
		void on_UndoMove();
		
		void on_QuitGame();
		
		void on_TimerEvent();
		
		//!set the view object for the controller;
		//!allows the controller to move objects and highlight the board
		void SetView(IChessView* chessView);
	
	private:
		//!unhighlights everything on the board
		void unhighlightAll();
		
		//!redraws the entire board
		void refreshBoard();
		
		//!changes the turn between players
		void changeTurn();
		
		IChessView * view;
		Game * game;
		
		//save the list of locations that are currently highlighted as potential moves
		std::vector<Reference<Location> > * selectedLocs;
		//save the location that the player might move a piece from
		Location * selectedLoc;
		
		//HUMAND or COMPUTER
		int playerTypes[2];
		//WHITE always goes first
		int turn;
		
		//save the location that the game was last loaded in
		std::string currentFileName;
};


#endif

