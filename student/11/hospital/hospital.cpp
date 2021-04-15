#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
    // Deallocating staff
    for( std::map<std::string, Person*>::iterator
         iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        delete iter->second;
    }

    // Remember to deallocate patients also
    for (std::map<std::string, Person*>::iterator
         iter = current_patients_.begin();
         iter != current_patients_.end();
         ++iter){
        delete iter->second;
    }
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    if (current_patients_.find(patient_id) != current_patients_.end()){
        std::cout<< ALREADY_EXISTS<< patient_id << std::endl;
        return;
    }
    Person* new_patient = new Person(patient_id);
    CarePeriod* new_period = new CarePeriod(utils::today,new_patient);


    current_patients_.insert({patient_id,new_patient});
    all_patient_care_period_.at(patient_id).push_back(new_period);


    std::cout<< PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    if (current_patients_.find(patient_id) == current_patients_.end()){
        std::cout<<CANT_FIND<<patient_id<<std::endl;
        return;
    }

    //std::map<std::string, Person*>::const_iterator patient_iter = current_patients_.find(patient_id);
    //Remove the patient from hospital
    current_patients_.erase(patient_id);

    std::vector<CarePeriod*> temp_patient_care_period = all_staff_care_period_.at(patient_id);
    for(auto iter : temp_patient_care_period){
        if(iter->already_close()){
            iter++;
        }else{
            iter->close_care_period(utils::today);
        }
    }
    std::cout<< PATIENT_LEFT<< std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    //Handle error of cannot find staff/patient
    if(staff_.find(staff_id) == staff_.end()){
        std::cout<<CANT_FIND<<staff_id<<std::endl;
        return;
    }

    if(current_patients_.find(patient_id) == current_patients_.end()){
        std::cout<<CANT_FIND<<patient_id<<std::endl;
        return;
    }


    Person* new_patient = new Person(patient_id);
    Person* new_staff = new Person(staff_id);

    //Create a care period for patient and assign staff
    CarePeriod* new_period = new CarePeriod(utils::today,new_patient);
    new_period->assign_staff_respon(new_staff);


    //Assign a new care period to patient ?


    //Still need to check that current care period available ?
    //all_patient_care_period_.at(patient_id).push_back(new_period);
    all_staff_care_period_.at(staff_id).push_back(new_period);

}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    std::string patient_id = params.at(0);
    std::map<std::string, Person*>::const_iterator
            patient_iter = current_patients_.find(patient_id);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    std::vector<CarePeriod*> temp_patient_care_period =
             all_patient_care_period_.at(patient_id);

    for(auto iter : temp_patient_care_period)
    {
        std::cout<<"* Care period: ";
        iter->get_start_date().print();
        std::cout<<"-";
        iter->get_end_date().print();
        std::cout<<std::endl;

        std::cout<<"  - Staff: ";
        iter->print_staff_respon();

        /*
        std::vector<Person*> temp_care_staff_vct = iter->return_staff_respon_vct();
        for (auto it : temp_care_staff_vct){
            if(temp_care_staff_vct.size() == 0){
                std::cout<<"None "<<std::endl;
                break;
            }else{
                it->print_id();
                std::cout<<" ";
            }
        }
        */

        std::cout<<std::endl;
    }

    std::cout<<"* Medicines:"<<std::endl;
    patient_iter->second->print_medicines(" - ");
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::vector<CarePeriod*> temp_staff_care_period = all_staff_care_period_.at(staff_id);

    if(staff_.find(staff_id) == staff_.end()){
        std::cout << ALREADY_EXISTS << staff_id << std::endl;
        return;
    }

    for(auto iter : temp_staff_care_period)
    {
        iter->get_start_date().print();
        std::cout<<"-";
        iter->get_end_date().print();
        std::cout<<std::endl;

        std::cout<<"* Patient: ";
        iter->get_patient()->print_id();
        std::cout<<std::endl;
    }
}

void Hospital::print_all_medicines(Params)
{
    std::map<std::string,std::vector<Person*>> all_medicines_map;
    for (auto iter : current_patients_){
        std::vector<std::string> temp_medicine_list;
        temp_medicine_list = iter.second->get_medicines();

        for(auto it : temp_medicine_list){
            if(all_medicines_map.find(it) != all_medicines_map.end()){
                //Case: Medicine already exist
                all_medicines_map.at(it).push_back(iter.second);
            }else{
                //Case: New medicine name
                std::vector<Person*> temp_patient_vct;
                temp_patient_vct.push_back(iter.second);
                all_medicines_map.insert({it,temp_patient_vct});
            }
        }
    }

    //Print all medicines information
    for (std::map<std::string,std::vector<Person*>>::iterator it_2 = all_medicines_map.begin();
         it_2 != all_medicines_map.end();
         it_2 ++){
        std::cout<<it_2->first<<" prescribed for"<<std::endl;
        for(auto it_3 : it_2->second){
            std::cout<<"* ";
            it_3->print_id();
            std::cout<<std::endl;
        }
    }
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map<std::string, Person*>::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::print_all_patients(Params)
{

}

void Hospital::print_current_patients(Params)
{

}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}
