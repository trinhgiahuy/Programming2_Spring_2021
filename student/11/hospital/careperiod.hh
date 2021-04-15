/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * Note: Students need to implement almost all of this class by themselves.
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>

class CarePeriod
{
public:
    // Constructor, start date given as a string (ddmmyyyy).
    CarePeriod(const std::string& start, Person* patient);

    // Constructor, start date given as a Date object.
    CarePeriod(const Date& start, Person* patient);

    // Destructor.
    ~CarePeriod();

    // More public methods

    //Method for assign staff to this care period
    void assign_staff_respon(Person* staff);

    //Method returning staff responsible for this care period
    std::vector<Person*> return_staff_respon_vct();

    void set_end_date(Date& end);

    Date get_start_date();
    Date get_end_date();
    Person* get_patient();

    void print_staff_respon();

    //Check that if care period is already closed
    bool already_close();
    void close_care_period(Date& closed_date);




private:
    Person* patient_;
    Date start_;
    Date end_ ;

    // More attributes and methods
    bool is_closed_ = false;

    //A staff person who is responsible for this care period
    std::vector<Person*> staff_respon_vct_;

};

#endif // CAREPERIOD_HH
