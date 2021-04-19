#include "careperiod.hh"
#include "person.hh"
#include <iostream>
#include <algorithm>
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
    //Deallocating the staff responsible
    for(auto iter : staff_respon_vct_){
        delete iter;
    }
}

void CarePeriod::assign_staff_respon(Person* staff)
{
    if(!is_closed_){
        staff_respon_vct_.push_back(staff);
    }
}

std::vector<Person*> CarePeriod::return_staff_respon_vct()
{
    return staff_respon_vct_;
}

void CarePeriod::set_end_date(Date &end)
{
    end.set(end.get_day(),end.get_month(),end.get_year());
}

Date CarePeriod::get_start_date()
{
    return start_;
}

Date CarePeriod::get_end_date()
{
    return end_;
}

void CarePeriod::print_staff_respon()
{
    if( staff_respon_vct_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    std::sort(staff_respon_vct_.begin(),staff_respon_vct_.end());
    for( auto iter : staff_respon_vct_)
    {
        iter->print_id();
        std::cout<<" ";
    }
    std::cout<<std::endl;
}

void CarePeriod::close_care_period(Date& closed_date)
{
    end_ = closed_date;
    is_closed_ = true;
}

bool CarePeriod::is_closed_ret()
{
    return is_closed_;
}

Person* CarePeriod::get_patient()
{
    return patient_;
}
