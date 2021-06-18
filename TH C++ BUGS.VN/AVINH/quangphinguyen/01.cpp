#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

int maxOfArray(vector<int> &vect)
{
	int max = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		if (max < vect[i])
			max = vect[i];
	}
	return max;
}

int almostLargestOfArray(vector<int> &vect)
{
	int max = 0;
	int temp_max = 0;
	
	for (int i = 0; i < vect.size(); i++)
	{
		if (max < vect[i])
		{
			temp_max = max;
			max = vect[i];
		}
	}
	
	max = 0;
	
	return temp_max;
}

bool tripletExist(vector<int> vect, int max)
{
	unordered_map<int, int> map;

	for (int i = 0; i < vect.size(); i++)
		map[vect[i]] = i;

	for (int i = 0; i < vect.size() - 1; i++)
	{
		for (int j = i + 1; j < vect.size(); j++)
		{
			int val = max - (vect[i] + vect[j]);

			if (map.find(val) != map.end())
			{
				if (map[val] != i && map[val] != j)
					return true;
			}
		}
	}
	return false;
}

int main(int argc, int** argv)
{
	vector<int> vect = { 2, 3, 5, 7, 12 };
	int WhatWeNeedToFind = maxOfArray(vect);
	
	while (tripletExist(vect, WhatWeNeedToFind) != true)
	{
		WhatWeNeedToFind = almostLargestOfArray(vect);
	}

	cout << WhatWeNeedToFind << endl;

	system("pause");
	return 0;
}
#include <iostream>
#include <unordered_set>
using namespace std; 
/*-------------------------------*/
