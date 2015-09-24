#include "Castle.h"
#include "Board.h"
#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "Referenceable.h"
#include "Reference.h"
#include "TestCastle.h"

#include <iostream>
#include <vector>
using namespace std;

TestCastle::TestCastle(){}

bool TestCastle::testCastle(ostream & os){
	bool success = true;
	Board board;
	Reference<Location>** squares = board.getAllSquares();
	Reference<Location> loc = squares[WHITE_MAIN_ROW][0];
	IPiece* whiteCastle = squares[WHITE_MAIN_ROW][0]->getPiece();
	
	printSubheader("MOVES",os);
	vector<Reference<Location> > moves = whiteCastle->getMoves(squares,loc);
	TESTM(moves.size()==0,"Expected: 0\n Actual: " << moves.size() << "\n");
	
	squares[WHITE_PAWN_ROW][0]->setPiece(NULL);
	moves = whiteCastle->getMoves(squares,loc);
	TESTM(moves.size()==6,"Expected: 6\n Actual: " << moves.size() << "\n");
	
	squares[3][0]->setPiece(whiteCastle);
	moves = whiteCastle->getMoves(squares,squares[3][0]);
	TESTM(moves.size()==12,"Expected: 12\n Actual: " << moves.size() << "\n");
	
	moves = whiteCastle->getMoves(squares,squares[4][4]);
	TESTM(moves.size()==11,"Expected: 11\n Actual: " << moves.size() << "\n");
	
	return success;
}
