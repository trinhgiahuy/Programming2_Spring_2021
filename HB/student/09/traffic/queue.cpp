#include "queue.hh"
#include <iostream>

//using namespace std;
// Implement the member functions of Queue here
Queue::Queue(unsigned int cycle) : cycle_(cycle) {
}

Queue::~Queue() {
	while (first_ != nullptr) {
		Vehicle* item_to_be_released = first_;
		first_ = first_->next;
		delete item_to_be_released;
	}
}

void Queue::enqueue(string reg) {
	Vehicle* new_item = new Vehicle{ reg, nullptr };
	if (is_green_) {
		cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;
		return;
	}
	if (first_ == nullptr) {
		first_ = new_item;
		last_ = new_item;
	}
	else {
		last_->next = new_item;
		last_ = new_item;
	}
}

void Queue::switch_light() {
	is_green_ = !is_green_;
	if (is_green_) cout << "GREEN: ";
	else cout << "RED: ";
	if (first_ == nullptr) {
		cout << "No vehicles waiting in traffic lights" << endl;
		return;
	}
	unsigned int i = 1;
	cout << "Vehicle(s) ";
	while ((i <= cycle_) and first_ != nullptr) {
		Vehicle* item_to_be_removed = first_;

		cout << item_to_be_removed->reg_num << " ";

		if (first_ == last_) {
			first_ = nullptr;
			last_ = nullptr;
		}
		else {
			first_ = first_->next;
		}

		delete item_to_be_removed;
		i++;
	}
	cout << "can go on" << endl;
	is_green_ = !is_green_;
}

void Queue::reset_cycle(unsigned int cycle) {
	cycle_ = cycle;
}

void Queue::print() {
	if (is_green_) cout << "GREEN: ";
	else cout << "RED: ";
	if (first_ == nullptr) {
		cout << "No vehicles waiting in traffic lights" << endl;
		return;
	}
	Vehicle* item_to_be_printed = first_;
	cout << "Vehicle(s) ";
	while (item_to_be_printed != nullptr) {
		cout <<  item_to_be_printed->reg_num << " ";
		item_to_be_printed = item_to_be_printed->next;
	}
	cout << "waiting in traffic lights" << endl;
}