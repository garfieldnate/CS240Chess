#include "Pawn.h"
#include "Board.h"
#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "Referenceable.h"
#include "Reference.h"
#include "TestPawn.h"

#include <iostream>
#include <vector>
using namespace std;

TestPawn::TestPawn(){}
bool TestPawn::testPawn(ostream & os){
	bool success = true;
	Board board;
	Reference<Location>** squares = board.getAllSquares();
	Reference<Location> loc = squares[WHITE_PAWN_ROW][1];
	IPiece* whitePawn = loc->getPiece();
	printSubheader("MOVES",os);
	vector<Reference<Location> > moves = whitePawn->getMoves(squares,loc);
	TESTM(moves.size()==2,"Expected: 2\n Actual: " << moves.size() << "\n");
	
	((Pawn*)whitePawn)->incrementMoved();
	moves = whitePawn->getMoves(squares,squares[WHITE_PAWN_ROW][1]);
	TESTM(moves.size()==1,"Expected: 1\n Actual: " << moves.size() << "\n");
	((Pawn*)whitePawn)->decrementMoved();
	
	Pawn* blackPawn = new Pawn(BLACK);
	squares[WHITE_PAWN_ROW+2][1]->setPiece(blackPawn);
	moves = whitePawn->getMoves(squares,loc);
	TESTM(moves.size()==1,"Expected: 1\n Actual: " << moves.size() << "\n");
	
	squares[WHITE_PAWN_ROW+1][1]->setPiece(blackPawn);
	moves = whitePawn->getMoves(squares,loc);
	TESTM(moves.size()==0,"Expected: 0\n Actual: " << moves.size() << "\n");
	
	squares[WHITE_PAWN_ROW+1][2]->setPiece(blackPawn);
	moves = whitePawn->getMoves(squares,loc);
	TESTM(moves.size()==1,"Expected: 1\n Actual: " << moves.size() << "\n");
	
	squares[WHITE_PAWN_ROW+1][0]->setPiece(blackPawn);
	moves = whitePawn->getMoves(squares,loc);
	TESTM(moves.size()==2,"Expected: 2\n Actual: " << moves.size() << "\n");
	
	delete blackPawn;
	return success;
}


