#include "tests.h"
#include "ChessConstants.h"
#include "UnitTest.h"
#include "TestLoad.h"
#include "Game.h"
#include <iostream>
#include <string>
using namespace std;

TestLoad::TestLoad(){}

bool TestLoad::testLoad(ostream & os, string dataDir){
	bool success = true;
	
	Game * game = new Game(dataDir + "fewmoves.xml");
	
	//just checking memory errors; don't test anything else!
	delete game;
	return success;
}
