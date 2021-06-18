#ifndef COCKATOO_HH
#define COCKATOO_HH

#include <iostream>
#include <string>
#include "bird.hh"

class Cockatoo: public Bird
{
public:
	Cockatoo();


    void sing(std::ostream& output) const;

private:
 
};

#endif // COCKATOO_HH
