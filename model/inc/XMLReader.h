#ifndef XMLREADER_H
#define XMLREADER_H
#include "Move.h"
#include "Board.h"
#include "HTMLTokenizer.h"
#include <vector>
#include <string>

class XMLReader{
	public:
		static std::vector<Move * > * getHistory(std::string fileName, Board* board);
		static vector<Move * > * parse(HTMLTokenizer * t, Board* board);
	private:
	
};

#endif
