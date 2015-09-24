#include "XML.h"
#include "StringUtil.h"
#include "CS240Exception.h"
#include <string>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;
	//! @param stream to write XML data to
		//! @param stream to write errors to
	XML::XML(ostream* out, ostream* err = &cerr):outStream(out),errStream(err),tabNum(0){
		openedTags = new vector<string>();
	}
	
	//! The destructor will print an error if the opened tags stack is not empty
	XML::~XML(){
		assert(openedTags != NULL);
		if(openedTags->size()!=0){
			*errStream << "Warning! Not all tags closed:";
			while(openedTags->size() != 0){
				*errStream << " [" << openedTags->back() << "]";
				openedTags->pop_back();
			}
			*errStream << endl;
		}
		delete openedTags;
	}

	//! @param name of opening tag to write. XML entities will be escaped.
	//! @throws InvalidArgumentException if the string contains whitespace
	void XML::openTag(const string str){
		assert(openedTags != NULL);
		//there is certainly much more whitespace that could be checked for, but just these for now
		if(str.find(' ') != string::npos || str.find('\t') != string::npos)
			throw InvalidArgumentException("XML tag name should not contain whitespace");
		
		//convert to XML before saving or printing
		string escaped = StringUtil::EncodeToXmlCopy(str);
		for(int i = 0; i < tabNum; i++)
			*outStream << "\t";
			
		
		*outStream << "<" << escaped << ">" << endl;
		tabNum++;
		
		openedTags->push_back(escaped);
	}
	
	//!@param name of opening tag to write
	//!@param vector of attribute/value pairs
	void XML::openTag(const std::string str, vector<string> * atts, bool endSelf){
		if(atts->size()%2 != 0)
			throw InvalidArgumentException();
		string escaped = StringUtil::EncodeToXmlCopy(str);
		for(int i = 0; i < tabNum; i++)
			*outStream << "\t";
			
		*outStream << "<" << escaped;
			
		//print attributes
		for(int i = 0; i < atts->size(); i += 2)
			*outStream << " " << atts->at(i) << "=\"" << atts->at(i+1) << "\"";
			
		if(endSelf)
			*outStream << "/";
		else{
			tabNum++;
			openedTags->push_back(escaped);
		}
		*outStream << ">" << endl;
		
	}
	
	
	//! closes the last opened tag
	//! @throws exception if there is no tag on the stack to close
	void XML::closeTag(){
		assert(openedTags != NULL);
		
		tabNum--;
		for(int i = 0; i < tabNum; i++)
			*outStream << "\t";
		*outStream << "</" << openedTags->back() << ">" << endl;
		openedTags->pop_back();
	}
	
	//! @param text to write. XML entities will be escaped, and tabs and a newline will be added.
	void XML::writeText(const string str){
		//convert to xml and print
		string escaped = StringUtil::EncodeToXmlCopy(str);
		for(int i = 0; i < tabNum; i++)
			*outStream << "\t";
		*outStream << escaped << endl;
	}
	
	
