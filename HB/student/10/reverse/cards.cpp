#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards() : top_(nullptr) {
}


void Cards::add(int id) {
	std::shared_ptr<Card_data> new_card
		= std::make_shared<Card_data>(Card_data{ id, top_ });
	top_ = new_card;
}

void Cards::print(std::ostream& s) {
	std::shared_ptr<Card_data> to_be_printed = top_;
	int nr = 1;

	while (to_be_printed != 0) {
		s << nr << ": " << to_be_printed->data << std::endl;
		to_be_printed = to_be_printed->next;
		++nr;
	}
}

bool Cards::remove(int& id) {
	if (top_ == nullptr) return false;
	std::shared_ptr<Card_data> item_to_be_removed = top_;

	id = item_to_be_removed->data;

	if (top_->next != nullptr)	top_ = top_->next;
	else return false;


	//delete item_to_be_removed;

	return true;
}

void Cards::reverse() {
	if (top_ == nullptr) return;
	if (top_->next == nullptr)	return;
	std::shared_ptr<Card_data> end_trace = top_->next;

	//static Card_data* item_to_be_printed = top_;
	//prev->next = nullptr;
	while (end_trace->next != nullptr) {

		end_trace = end_trace->next;
	}
	std::shared_ptr<Card_data> end = end_trace;
	std::shared_ptr<Card_data> current = top_->next;
	std::shared_ptr<Card_data> prev = top_;
	while (current->next != nullptr) {
		std::shared_ptr<Card_data> temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	end->next = prev;
	top_->next = nullptr;
	top_ = end;

}
// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file reverse.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in reverse.cpp
