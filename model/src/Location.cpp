#include "Location.h"
#include <iostream>

using namespace std;
//Location::Location(){
	//row = -1;
	//col = -1;
//}

Location::Location(int r, int c):row(r),col(c),piece(NULL){
	//cout << "Creating new location (" << row << "," << col << ")" << endl;
}

Location::~Location(){}

//void setRow(int r){
	//row = r;
//}

//void setCol(int c){
	//col = c;
//}

int Location::getRow(){
	return row;
}

int Location::getCol(){
	return col;
}

IPiece * Location::getPiece(){
	//cout << "Accessing piece, which is of type ";
	//if(piece == NULL)
		//cout << "NULL" << endl;
	//else
		//cout << piece->getType() << endl;
	//cout << "getting piece" << endl;
	return piece;
}

void Location::setPiece(IPiece* p){
	piece = p;
		//cout << "set piece type " << piece->getType() << " at " << row << ", " << col << endl;
}

////!@return true if the location has been selected as a potential move spot
//void Location::getSelected(){

//}
