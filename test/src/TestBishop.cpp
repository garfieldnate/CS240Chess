#include "Bishop.h"
#include "Board.h"
#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "Referenceable.h"
#include "Reference.h"
#include "TestBishop.h"

#include <iostream>
#include <vector>
using namespace std;

TestBishop::TestBishop(){}
bool TestBishop::testBishop(ostream & os){
	bool success = true;
	Board board;
	Reference<Location>** squares = board.getAllSquares();
	Reference<Location> loc = squares[WHITE_MAIN_ROW][2];
	IPiece* whiteBishop = loc->getPiece();
	printSubheader("MOVES",os);
	
	vector<Reference<Location> > moves = whiteBishop->getMoves(squares,loc);
	TESTM(moves.size()==0,"Expected: 0\n Actual: " << moves.size() << "\n");
	
	moves = whiteBishop->getMoves(squares,squares[2][2]);
	TESTM(moves.size()==6,"Expected: 6\n Actual: " << moves.size() << "\n");
	
	//for(int i = 0; i < moves.size(); i++)
		//cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol() << endl;
	
	moves = whiteBishop->getMoves(squares,squares[3][3]);
	TESTM(moves.size()==8,"Expected: 8\n Actual: " << moves.size() << "\n");
	
	//for(int i = 0; i < moves.size(); i++)
		//cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol() << endl;
	return success;
}


