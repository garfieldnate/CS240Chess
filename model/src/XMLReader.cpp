#include "XMLReader.h"
#include "Move.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "StringUtil.h"
#include "HTMLTokenizer.h"
#include "CS240Exception.h"
//#include 

using namespace std;

//read xml file and make moves out of it
vector<Move * > * XMLReader::getHistory(string fileName, Board* board){
	
	//read in file
	ifstream file(fileName.c_str());
	string str((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	cout << str << endl;
	
	StringUtil::ToLower(str);
	StringUtil::Trim(str);
	
	HTMLTokenizer t(str);
	
	while(t.HasNextToken()){
		if(t.GetNextToken().GetValue() == "history")
			return parse(&t, board);
	}
	
	throw new IllegalStateException("didn't find history!");
}

vector<Move * > * XMLReader::parse(HTMLTokenizer * t, Board* board){
	vector<Move*> * history = new vector<Move*>();
	bool inMove = false;
	int pieceInMoveCount = 0;
	
	//temp variables for token type and value
	HTMLTokenType tokenType;
	std::string tokenValue;
	Reference<Location> locs[2];
	
	while(t->HasNextToken()){
		//get all values
		HTMLToken token = t->GetNextToken();
		tokenType = token.GetType();
		tokenValue = token.GetValue();
		StringUtil::ToLower(tokenValue);
		StringUtil::Trim(tokenValue);
		
		if(tokenType == TAG_START && tokenValue == "move"){
			pieceInMoveCount = 0;
			inMove = true;
		}
		
		if(tokenType == TAG_END && tokenValue == "move"){
			//pieceInMoveCount = 0;
			inMove = false;
			if(pieceInMoveCount < 2)
				throw new IllegalStateException("Not enough pieces in move element!");
			history->insert(history->end(),new Move(locs[0],locs[1]));
		}
		
		if(tokenValue == "piece"){
			if(!inMove)
				throw new IllegalStateException("Piece outside of a move!");
			//only want the first two pieces
			if(pieceInMoveCount > 1)
				break;
			string row = token.GetAttribute("row");
			StringUtil::Trim(row);
			string col = token.GetAttribute("column");
			StringUtil::Trim(col);
			int r = atoi(row.c_str());
			int c = atoi(col.c_str());
			locs[pieceInMoveCount] = board->getSquare(r,c);
			pieceInMoveCount++;
		}
	}
	return history;
}
