//REVERSE STRING
char* recursiveWordInString(char*initialString) {
	static char arr[100] = { 0 }; //hold the initial string
	static int pos[15] = { 0 }; //hold the position of each word in the array arr[100]
	pos[0] = 0;
	static int  i = 0; // position of each char
	static int j = 1; // position of each word before reversing 

//Load initial string into the array and mark word positions.
	if (*initialString != '\0') {
		if (*initialString == ' ') {
			pos[j] = i + 1;
			j++;
		}
		arr[i] = *initialString;
		i++;
		initialString++;
		return recursiveWordInString(initialString);
	}
	arr[i] = '\0';

//Reverse words into a new char array
	char* str = new char[i + 1]; // j = 5 , i = 22 , 23 elements
	j -= 1;
	for (int k = 0; k < i + 1; k++) {
		if (arr[pos[j]] == ' ' || arr[pos[j]] == '\0') {
			str[k] = ' ';
			j -= 1;
			continue;
		}
		str[k] = arr[pos[j]];
		(pos[j])++;
	}
	str[i] = '\0';
	return str;
}
