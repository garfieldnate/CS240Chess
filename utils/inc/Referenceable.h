
#ifndef REFERENCEABLE_H
#define REFERENCEABLE_H
#include <iostream>

class Referenceable {
private:
  int refCount;

public:
  Referenceable() {
	//std::cout << "created referenceable" << std::endl;
    refCount = 0;
  }

  int AddRef() {
	//std::cout << "incrementing ref count to " << refCount+1 << std::endl;
    return ++refCount;
  }

  int ReleaseRef() {
	  //std::cout << "decrementing ref count to " << refCount-1 << std::endl;
    return --refCount;
  }
};


#endif
