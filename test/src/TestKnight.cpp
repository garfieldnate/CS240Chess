#include "Knight.h"
#include "Board.h"
#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "Referenceable.h"
#include "Reference.h"
#include "TestKnight.h"

#include <iostream>
#include <vector>
using namespace std;

TestKnight::TestKnight(){}

bool TestKnight::testKnight(ostream & os){
	bool success = true;
	Board board;
	Reference<Location>** squares = board.getAllSquares();
	Reference<Location> loc = squares[WHITE_MAIN_ROW][1];
	IPiece* whiteKnight = squares[WHITE_MAIN_ROW][1]->getPiece();
	
	printSubheader("MOVES",os);
	vector<Reference<Location> > moves = whiteKnight->getMoves(squares,loc);
	TESTM(moves.size()==2,"Expected: 2\n Actual: " << moves.size() << "\n");
	
	squares[3][4]->setPiece(whiteKnight);
	moves = whiteKnight->getMoves(squares,squares[3][4]);
	TESTM(moves.size()==6,"Expected: 6\n Actual: " << moves.size() << "\n");
	
	squares[4][4]->setPiece(whiteKnight);
	moves = whiteKnight->getMoves(squares,squares[4][4]);
	TESTM(moves.size()==8,"Expected: 8\n Actual: " << moves.size() << "\n");
	
	//for(int i = 0; i < moves.size(); i++)
		//cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol() << endl;
	
	return success;
}
