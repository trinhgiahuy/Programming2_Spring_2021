#include "queue.hh"
#include <iostream>

using namespace std;
// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle): first_(nullptr), last_(nullptr), cycle_(cycle) {
}

Queue::~Queue() {
    while (first_ != nullptr) {
        Vehicle* car_release = first_;
        first_ = first_->next;

        delete car_release;
    }
}

void Queue::enqueue(string reg) {
    Vehicle* car_add = new Vehicle{reg, nullptr};

    if ( is_green_ ) {
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
    } else {
        if(first_ == nullptr) {
            first_ = car_add;
            last_ = car_add;
        } else {
            last_->next = car_add;
            last_ = car_add;
        }
    }
}

void Queue::dequeue() {
    if (first_->reg_num == last_->reg_num) {
        first_ = nullptr;
        last_ = nullptr;
    } else {
        first_ = first_->next;
    }
}

void Queue::switch_light() {
    string car_name = "";
    is_green_ = !(is_green_);

    if ( first_ == nullptr ) {
        print();
    } else {
        if ( is_green_ ) {
            for(unsigned int i = 0; i <cycle_; i++) {
                if ( first_ == nullptr) {
                    break;
                }
                car_name += first_->reg_num + " ";
                dequeue();
            }
        }
        cout << "GREEN: Vehicle(s) " << car_name << "can go on" << endl;

        is_green_ = !(is_green_);
    }
}

void Queue::reset_cycle(unsigned int cycle) {
    cycle_ = cycle;
}

void Queue::print() {
    Vehicle* car_count = first_;
    string car_name = "";

    if (first_ == nullptr) {
        if ( is_green_ ) {
            cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        } else {
            cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
    } else {
        while ( (car_count != nullptr) ) {
            car_name += car_count->reg_num + " ";
            car_count = car_count->next;
        }

        if ( !(is_green_)){
            cout << "RED: Vehicle(s) " << car_name << "waiting in traffic lights" << endl;
        }
    }
}
