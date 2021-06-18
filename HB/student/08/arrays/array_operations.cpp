#include "array_operations.hh"

int greatest_v1(int* itemptr, int size) {
	int max = 0;
	for (int* element = itemptr; element < itemptr + size; element++) {
		if (*element > max) {
			max = *element;
		}
	}
	return max;
}

int greatest_v2(int* itemptr, int* endptr) {
	int max = 0;
	for (int* element = itemptr; element < endptr; element++) {
		if (*element > max) {
			max = *element;
		}
	}
	return max;
}

void copy(int* itemptr, int* endptr, int* targetptr) {
	for (int* element = itemptr; element < endptr; element++) {
		*targetptr = *element;
		targetptr++;
	}
}

void reverse(int* leftptr, int* rightptr) {
	int* reverse_element = rightptr - 1;
	for (int* element = leftptr; element < rightptr; element++) {
		if (reverse_element > element) {
			int a = *element;
			int b = *reverse_element;
			*element = b;
			*reverse_element = a;
			
		}
		reverse_element--;
	}
}