#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>

class Cards {

    public:
      // Dynamic structure must have a constructor
      // that initializes the top item as null
      Cards();

      // Adds a new card with the given id as the topmost element
      void add(int id);

      // Prints the content of the data structure with ordinal numbers
      // to the output stream given as a parameter starting from the first element
      void print_from_top_to_bottom(std::ostream& s);

      // Removes the topmost card and returns it as reference parameter number.
      // Returns false, if the data structure is empty, otherwise returns true.
      bool remove(int& id);

      // Moves the last element of the data structure as the first one.
      bool bottom_to_top();

      // Moves the first element of the data structure as the last one.
      bool top_to_bottom();

      // Prints the content of the data structure with ordinal numbers
      // to the output stream given as a parameter starting from the last element.
      void print_from_bottom_to_top(std::ostream& s);

      // Dynamic data structure must have a destructor
      // that can be called to deallocate memory,
      // when the data structure is not needed any more.
      ~Cards();

    private:
      struct Card_data {
        int data;
        Card_data* next;
      };

      Card_data* top_;

      // You can use the function below in the implementation of
      // method print_from_bottom_to_top.
      int recursive_print(Card_data* top, std::ostream& s);
};

#endif // CARDS_HH
