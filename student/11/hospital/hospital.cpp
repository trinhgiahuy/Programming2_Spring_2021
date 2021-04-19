#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include<bits/stdc++.h>
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

bool Hospital::exist_care_period_of_patient(std::vector<CarePeriod *> care_period_vct,
                                            std::string patient)
{
    if(care_period_vct.empty())
    {
        return false;
    }

    for(auto iter : care_period_vct)
    {
        if(iter->get_patient()->get_id() == patient)
        {
            return  true;
        }
    }

    return false;
}

CarePeriod* Hospital::return_care_period_of_patient(std::vector<CarePeriod *> care_period_vct,
                                                    std::string patient_id)
{
    for(auto care_per_it : care_period_vct)
    {
        if(care_per_it->get_patient()->get_id() == patient_id)
        {
            return care_per_it;
        }
    }
    return nullptr;
}


void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if(staff_.find(specialist_id) != staff_.end())
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }

    Person* new_specialist = new Person(specialist_id);
    staff_.insert({specialist_id, new_specialist});


    //Create a empty care period for staff
    std::vector<CarePeriod*> temp_care_period_vct;
    all_staff_care_period_.insert({specialist_id,temp_care_period_vct});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);
    if(!current_patients_.empty())
    {
        //Handle patient already exist as current patient
        if (current_patients_.find(patient_id) != current_patients_.end())
        {
            std::cout<< ALREADY_EXISTS<< patient_id << std::endl;
            return;
        }
    }

    Person* new_patient = new Person(patient_id);
    CarePeriod* new_period = new CarePeriod(utils::today,new_patient);
    current_patients_.insert({patient_id,new_patient});

    if(!all_patient_care_period_.empty())
    {
        std::map<std::string,std::vector<CarePeriod*>>::iterator iter = all_patient_care_period_.find(patient_id);
        if(iter == all_patient_care_period_.end())
        {
            //Case patient has not been hospital before
            std::vector<CarePeriod*> temp_care_period_vct;
            temp_care_period_vct.push_back(new_period);
            all_patient_care_period_.insert({patient_id,temp_care_period_vct});

        }
        else
        {
            //Case a patient has been to hospital before
            iter->second.push_back(new_period);
        }
    }
    else
    {
        //Case first patient added
        std::vector<CarePeriod*> temp_care_period_vct;
        temp_care_period_vct.push_back(new_period);
        all_patient_care_period_.insert({patient_id,temp_care_period_vct});
    }

    std::cout<< PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);
    if (current_patients_.find(patient_id) == current_patients_.end())
    {
        std::cout<<CANT_FIND<<patient_id<<std::endl;
        return;
    }

    //Remove the patient from hospital
    current_patients_.erase(patient_id);

    //Check and close care period of patient
    std::vector<CarePeriod*> temp_patient_care_period = all_patient_care_period_.at(patient_id);
    for(auto care_per_iter : temp_patient_care_period)
    {
        if(care_per_iter->is_closed_ret())
        {
            care_per_iter++;
        }
        else
        {
            //Check and close care period of that patient for staff
            std::vector<Person*> tmp_staff_respon_vct = care_per_iter->return_staff_respon_vct();

            //Checking these staffs have patient care period.
            for(auto staff_iter : tmp_staff_respon_vct)
            {
                std::vector<CarePeriod*> patient_care_per_vct;
                patient_care_per_vct = all_staff_care_period_.at(staff_iter->get_id());
                CarePeriod* patient_care_per = return_care_period_of_patient(patient_care_per_vct,patient_id);
                patient_care_per->close_care_period(utils::today);
            }
            care_per_iter->close_care_period(utils::today);
        }
    }

    std::cout<< PATIENT_LEFT<< std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::string patient_id = params.at(1);

    //Handle error of cannot find staff/patient
    if (!staff_.empty()){
        if(staff_.find(staff_id) == staff_.end()){
            std::cout<<CANT_FIND<<staff_id<<std::endl;
            return;
        }
    }else{
        //Empty staff data.
        std::cout<<CANT_FIND<<staff_id<<std::endl;
        return;
    }

    if(!current_patients_.empty()){
        if(current_patients_.find(patient_id) == current_patients_.end()){
            std::cout<<CANT_FIND<<patient_id<<std::endl;
            return;
        }
    }else{
        //Empty patient data.
        std::cout<<CANT_FIND<<patient_id<<std::endl;
        return;
    }

    Person* new_patient = new Person(patient_id);
    Person* new_staff = new Person(staff_id);
    CarePeriod* new_period = new CarePeriod(utils::today,new_patient);

    //All_patient_care must have at least or recorded previous patient
    if(!all_patient_care_period_.empty())
    {

        for (auto iter : all_patient_care_period_.at(patient_id))
        {

            //Patient has a current
            if(!iter->is_closed_ret())
            {
                iter->assign_staff_respon(new_staff);
            }
            else
            {
                //The previous care period close.
                //Create a care period for patient and assign staff
                all_patient_care_period_.at(patient_id).push_back(new_period);
            }
        }
    }

    std::vector<CarePeriod*> temp_staff_care_period_vct= all_staff_care_period_.at(staff_id);

    if(!temp_staff_care_period_vct.empty())
    {

        bool care_period_exist = exist_care_period_of_patient(temp_staff_care_period_vct,new_patient->get_id());
        if(!care_period_exist)
        {
            all_staff_care_period_.at(staff_id).push_back(new_period);
        }
        else
        {
            for(auto care_period_iter : temp_staff_care_period_vct)
            {
                //Case staff have already patient's care period but it is closed already
                if( (care_period_exist && care_period_iter->is_closed_ret()) )
                {
                    all_staff_care_period_.at(staff_id).push_back(new_period);
                }
            }
        }
    }
    else
    {
        //Add first patient care period of staff
        all_staff_care_period_.at(staff_id).push_back(new_period);
    }

    std::cout<<STAFF_ASSIGNED<<patient_id<<std::endl;
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
    Person* person_ptr = current_patients_.at(patient);

    //Add medicine to all_medicine_map
    if(all_medicines_map.find(medicine) != all_medicines_map.end())
    {

        //The medicine name already exist in the list
        std::vector<Person*> temp_person_vct = all_medicines_map.at(medicine);
        std::vector<Person*>::iterator it = std::find(temp_person_vct.begin(),temp_person_vct.end(),person_ptr);

        if(it == temp_person_vct.end())
        {
            //Case that person has not been assign that medicine
            all_medicines_map.at(medicine).push_back(person_ptr);
        }
    }
    else
    {
        std::vector<Person*> temp_person_vct;
        temp_person_vct.push_back(person_ptr);
        all_medicines_map.insert({medicine,temp_person_vct});
    }

    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map<std::string, Person*>::iterator
            patient_iter = current_patients_.find(patient);
    if(patient_iter == current_patients_.end())
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
    std::map<std::string, std::vector<CarePeriod*>>::iterator
            patient_iter = all_patient_care_period_.find(patient_id);

    if( patient_iter == all_patient_care_period_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    std::vector<CarePeriod*> temp_patient_care_period =
            all_patient_care_period_.at(patient_id);

    std::sort(temp_patient_care_period.begin(),temp_patient_care_period.end());
    for(auto iter : temp_patient_care_period)
    {
        std::cout<<"* Care period: ";
        iter->get_start_date().print();
        std::cout<<" - ";
        if(iter->is_closed_ret())
        {
            iter->get_end_date().print();
        }
        std::cout<<std::endl;

        std::cout<<"  - Staff: ";
        iter->print_staff_respon();
    }

    std::cout<<"* Medicines:";
    temp_patient_care_period.at(0)->get_patient()->print_medicines(" - ");
}

void Hospital::print_care_periods_per_staff(Params params)
{
    std::string staff_id = params.at(0);
    std::map<std::string,std::vector<CarePeriod*>>::iterator iter =
            all_staff_care_period_.find(staff_id);

    if(iter == all_staff_care_period_.end())
    {
        std::cout<<CANT_FIND<<staff_id<<std::endl;
        return;
    }

    std::vector<CarePeriod*> temp_staff_care_period = all_staff_care_period_.at(staff_id);

    if(staff_.find(staff_id) == staff_.end())
    {
        std::cout << ALREADY_EXISTS << staff_id << std::endl;
        return;
    }

    if(temp_staff_care_period.empty())
    {
        std::cout<<"None"<<std::endl;
        return;
    }


    for(auto iter : temp_staff_care_period)
    {
        iter->get_start_date().print();
        std::cout<<" - ";
        if(iter->is_closed_ret())
        {
            iter->get_end_date().print();
        }

        std::cout<<std::endl;
        std::cout<<"* Patient: ";
        iter->get_patient()->print_id();
        std::cout<<std::endl;
    }
}


bool Hospital::check_medicine_removed_of_patient(Person* patient_temp_,
                                                 std::string medicine)
{
    return patient_temp_->check_medicine_removed(medicine);
}


void Hospital::print_all_medicines(Params)
{

    if(all_medicines_map.empty())
    {
        std::cout<<"None"<<std::endl;
        return;
    }

    //Print all medicines information
    for (std::map<std::string,std::vector<Person*>>::iterator medicine_it_ = all_medicines_map.begin();
         medicine_it_ != all_medicines_map.end();
         medicine_it_ ++)
    {

        if(!medicine_it_->second.empty())
        {
            std::vector<Person*> patient_temp_vct = medicine_it_->second;
            unsigned int med_removed_num =0;
            for(unsigned int i = 0 ; i < patient_temp_vct.size();i++)
            {
                bool med_removed_ = check_medicine_removed_of_patient(patient_temp_vct.at(i),medicine_it_->first);
                if(med_removed_)
                {
                    med_removed_num ++;
                }
            }

            if(med_removed_num != patient_temp_vct.size())
            {
                std::cout<<medicine_it_->first<<" prescribed for"<<std::endl;
                std::vector<std::string> sorted_patient_vct;

                for(auto patient_it_ : patient_temp_vct)
                {
                    //Check if that medicine is not removed yet
                    if(!(patient_it_->check_medicine_removed(medicine_it_->first)))
                    {
                        sorted_patient_vct.push_back(patient_it_->get_id());
                    }
                }

                std::sort(sorted_patient_vct.begin(),sorted_patient_vct.end());
                for(auto iter_ : sorted_patient_vct)
                {
                    std::cout<<"* ";
                    all_patient_care_period_.at(iter_).at(0)->get_patient()->print_id();
                    std::cout<<std::endl;
                }
            }
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

bool Hospital::check_medicines_recorded(CarePeriod *temp_patient_care_period){

    std::vector<std::string> temp_med_vct = temp_patient_care_period->get_patient()->get_medicines();
    if(temp_med_vct.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Hospital::print_all_patients(Params)
{
    if(all_patient_care_period_.empty())
    {
        std::cout<<"None"<<std::endl;
        return;
    }

    for (auto patient_iter : all_patient_care_period_)
    {

        std::cout<<patient_iter.first<<std::endl;
        std::vector<CarePeriod*> temp_patient_care_period =
                all_patient_care_period_.at(patient_iter.first);

        for(auto iter : temp_patient_care_period)
        {
            std::cout<<"* Care period: ";
            iter->get_start_date().print();
            std::cout<<" - ";
            if(iter->is_closed_ret()){
                iter->get_end_date().print();
            }
            std::cout<<std::endl;

            std::cout<<"  - Staff: ";
            iter->print_staff_respon();
        }

        std::cout<<"* Medicines:";
        //Check all careperiod to find the medicines of patient
        unsigned int empty_med_num = 0;
        unsigned int index = 0;

        // The algorithm to find te index of newest updated care period of patient that
        // having the medicine
        for(unsigned int i = 0 ; i < temp_patient_care_period.size(); i++)
        {
            bool med_record = check_medicines_recorded(temp_patient_care_period.at(i));
            if(med_record)
            {
                if(index < empty_med_num)
                {
                    index = empty_med_num;
                    empty_med_num = i;
                }
            }
            else
            {
                empty_med_num++;
            }
        }

        //At least 1 careperiod has medicine
        if ( !(empty_med_num == temp_patient_care_period.size())){
            temp_patient_care_period.at(index)->get_patient()->print_medicines(" - ");
        }else{
            temp_patient_care_period.at(0)->get_patient()->print_medicines(" - ");
        }
    }

}

void Hospital::print_current_patients(Params)
{
    if(current_patients_.empty())
    {
        std::cout<<"None"<<std::endl;
        return;
    }

    //At least 1 patient current in hospital
    for (auto patient_iter : current_patients_)
    {

        std::vector<CarePeriod*> temp_patient_care_period =
                all_patient_care_period_.at(patient_iter.first);

        for(auto iter : temp_patient_care_period)
        {
            std::cout<<"* Care period: ";
            iter->get_start_date().print();
            std::cout<<"-";
            if(iter->is_closed_ret()){
                iter->get_end_date().print();
            }
            std::cout<<std::endl;

            std::cout<<"  - Staff: ";
            iter->print_staff_respon();

            std::cout<<"* Medicines:";
            iter->get_patient()->print_medicines(" - ");

        }
    }

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
