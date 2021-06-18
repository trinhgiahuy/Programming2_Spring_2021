#include "cards.hh"

using namespace std;
Cards::Cards() :top_(nullptr) {
}

Cards::~Cards() {
	while (top_ != nullptr) {
		Card_data* item_to_be_released = top_;
		top_ = top_->next;
		delete item_to_be_released;
	}
}

void Cards::add(int id) {
	Card_data* new_item = new Card_data{ id, nullptr };

	if (top_ == nullptr) {
		top_ = new_item;
	}
	else {
		new_item->next = top_;
		top_ = new_item;
	}

}

void Cards::print_from_top_to_bottom(std::ostream& s) {
	Card_data* item_to_be_printed = top_;
	int running_number = 1;

	while (item_to_be_printed != nullptr) {
		s << running_number << ": " << item_to_be_printed->data << endl;
		++running_number;
		item_to_be_printed = item_to_be_printed->next;
	}
}

bool Cards::remove(int& id) {
	if (top_ == nullptr) return false;
	Card_data* item_to_be_removed = top_;

	id = item_to_be_removed->data;


	top_ = top_->next;


	delete item_to_be_removed;

	return true;
}

// Moves the last element of the data structure as the first one.
bool Cards::bottom_to_top() {
	Card_data* item_to_be_printed = top_;
	Card_data* prev = new Card_data{ {}, nullptr };
	if (top_ == nullptr or top_->next == nullptr) return false;
	else {
		while (item_to_be_printed->next != nullptr) {
			prev = item_to_be_printed;
			item_to_be_printed = item_to_be_printed->next;
		}
		item_to_be_printed->next = top_;
		top_ = item_to_be_printed;
		prev->next = nullptr;
	}
	return true;
}

// Moves the first element of the data structure as the last one.
bool Cards::top_to_bottom() {
	Card_data* item_to_be_printed = top_;
	if (top_ == nullptr) return false;
	while (item_to_be_printed->next != nullptr) {

		item_to_be_printed = item_to_be_printed->next;
	}
	item_to_be_printed->next = top_;
	Card_data* bottom_ = top_;
	top_ = top_->next;
	bottom_->next = nullptr;
	return true;
}

// Prints the content of the data structure with ordinal numbers
// to the output stream given as a parameter starting from the last element.
void Cards::print_from_bottom_to_top(std::ostream& s) {
	static Card_data* item_to_be_printed = top_;
	static int count = 1;
	if (item_to_be_printed->next == nullptr) {
		count = 1;
		s << count << ": " << item_to_be_printed->data << endl;
		return;
	}
	Card_data* current_card = item_to_be_printed;
	item_to_be_printed = item_to_be_printed->next;
	print_from_bottom_to_top(s);

	s << ++count << ": " << current_card->data << endl;

}
// TODO: Implement the methods here
