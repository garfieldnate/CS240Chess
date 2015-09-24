#include <iostream>
#include "tests.h"
#include "TestPawn.h"
#include "TestCastle.h"
#include "TestKnight.h"
#include "TestQueen.h"
#include "TestBishop.h"
#include "TestKing.h"
#include "TestLoad.h"

#include "CS240Exception.h"
#include "UnitTest.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]){
	if(argc == 0){
		cerr << "USAGE: test.exe <directory name>" << endl;
		return -1;
	}
 
	cerr << "Hello! input was " << argv[1] << endl;

	string dataDir("/users/guest/n/nglenn/Desktop/chess/");
	cout << "datadir is " << dataDir << endl;
	dataDir.append("test/data/");
	cout << "data stored in " << dataDir << endl;
	

	//printHeader("PAWN",cout);
	//TestPawn testPawn;
	bool success;
	//success = testPawn.testPawn(cout);
	//printEnder("PAWN",success,cout);
	
	//printHeader("KNIGHT",cout);
	//TestKnight testKnight;
	//success = testKnight.testKnight(cout);
	//printEnder("KNIGHT",success,cout);
	
	//printHeader("CASTLE",cout);
	//TestCastle testCastle;
	//success = testCastle.testCastle(cout);
	//printEnder("CASTLE",success,cout);
	
	//printHeader("BISHOP",cout);
	//TestBishop testBishop;
	//success = testBishop.testBishop(cout);
	//printEnder("BISHOP",success,cout);
	
	//printHeader("QUEEN",cout);
	//TestQueen testQueen;
	//success = testQueen.testQueen(cout);
	//printEnder("QUEEN",success,cout);
	
	//printHeader("KING",cout);
	//TestKing testKing;
	//success = testKing.testKing(cout);
	//printEnder("KING",success,cout);
	
	printHeader("LOAD",cout);
	TestLoad testLoad;
	success = testLoad.testLoad(cout,dataDir);
	printEnder("LOAD",success,cout);
	
	//try{
	      //printHeader("HTML PARSER",cout);
	      //TestHTMLparser testHTMLparser(fileProtocol,dataDir);
	      //success = testHTMLparser.testHTMLparser(cout);
	      //printEnder("HTML PARSER",success,cout);
	//}catch(InvalidURLException e){
		//cout << e.GetMessage() << endl;
	//}catch(FileException e){
		//cout << e.GetMessage() << endl;
	//}
	
	cout << "Should have run X tests." << endl;
	cout << "Total TESTS RUN:    " << testCounter << endl;
	cout << "Total TESTS FAILED: " << failedCount << endl;
}

void printHeader(std::string str, std::ostream & os){
	os << "******************************" << std::endl;
	os << "|||||TESTING " + str + "|||||" << std::endl;
	os << "------------------------------" << std::endl;
}

void printSubheader(std::string str, std::ostream & os){
	os << "-----" << str << "-----" << std::endl;
}

void printEnder(std::string testName, bool success, std::ostream & os){
	os << testName + ": " << (success == true ? "PASS" : "FAIL") << endl <<
		"______________________________" << endl;
}

