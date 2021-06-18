#ifndef GIRAFFE_HH
#define GIRAFFE_HH

#include <iostream>
#include <string>
#include "mammal.hh"

class Giraffe: public Mammal
{
public:
	Giraffe();


    void make_noise(std::ostream& output) const;

private:
 
};

#endif // GIRAFFE_HH
