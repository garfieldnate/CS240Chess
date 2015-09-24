#include "King.h"
#include "Board.h"
#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "Referenceable.h"
#include "Reference.h"
#include "TestKing.h"

#include <iostream>
#include <vector>
using namespace std;

TestKing::TestKing(){}
bool TestKing::testKing(ostream & os){
	bool success = true;
	Board board;
	Reference<Location>** squares = board.getAllSquares();
	Reference<Location> loc = squares[WHITE_MAIN_ROW][4];
	IPiece* whiteKing = loc->getPiece();
	printSubheader("MOVES",os);
	vector<Reference<Location> > moves = whiteKing->getMoves(squares,loc);
	TESTM(moves.size()==0,"Expected: 0\n Actual: " << moves.size() << "\n");
	
	moves = whiteKing->getMoves(squares,squares[3][4]);
	
	TESTM(moves.size()==8,"Expected: 8\n Actual: " << moves.size() << "\n");
	
	//for(int i = 0; i < moves.size(); i++)
		//cout << moves.at(i)->getRow() << ", " << moves.at(i)->getCol() << endl;
	return success;
}


