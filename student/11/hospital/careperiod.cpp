#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::CarePeriod(const Date &start, Person* patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::assign_staff_respon(Person* staff)
{
    staff_respon_ = staff;
}

Person* CarePeriod::return_staff_respon(){
    return staff_respon_;
}

