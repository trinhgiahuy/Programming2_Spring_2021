#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int value;
	int index = -1;

	int arr[30] = { 5, 11, 12, 9, 7,
					3, 15, 20, 19, 1,
					18, 8, 17, 13, 6,
					16, 14, 2, 10, 4 };
	int sizeA = 30;

	printf("Enter value: ");
	scanf("%d", &value);

	for (int i = 0; i < sizeA; i++)
	{
		if (value == arr[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
		printf("=> Found %d at index %d.\n", value, index);
	else
		printf("=> %d is not found in array.\n", value);

	while (true);
	return 0;
}

=========================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(NULL));

	int arr[20] = { 0 };
	int sizeA = 20;

	for (int i = 0; i < sizeA; i++)
		arr[i] = rand();

	for (int i = 0; i < sizeA; i++)
		printf("%d ", arr[i]);

	while (true);
	return 0;
}
=================================
#include <stdio.h>

int main()
{
	int A[20] = { 	5, 11, 12, 9, 7,
					3, 15, 20, 19, 1,
					18, 8, 17, 13, 6,
					16, 14, 2, 10, 4 };
	int sizeA = 20;
	
	int B[10] = { 	30, 21, 24, 23, 27,
					22, 25, 28, 26, 29 };
	int sizeB = 10;

	int C[30] = { 0 };
	int sizeC = sizeA + sizeB;

	for (int i = 0; i < sizeA; i++)
		C[i] = A[i];

	for (int i = 0; i < sizeB; i++)
		C[i + sizeA] = B[i];

	for (int i = 0; i < sizeC; i++)
		printf("%d ", C[i]);

	while (true);
	return 0;
}
====================================
#include <stdio.h>

int main()
{
	int A[20] = { 	5, 11, 12, 9, 7,
					3, 15, 20, 19, 1,
					18, 8, 17, 13, 6,
					16, 14, 2, 10, 4 };
	int sizeA = 20;
	
	int B[30] = { 	30, 21, 24, 23, 27,
					22, 25, 28, 26, 29 };
	int sizeB = 10;

	for (int i = sizeB - 1; i >= 0; i--)
		B[i + sizeA] = B[i];

	for (int i = 0; i < sizeA; i++)
		B[i] = A[i];

	sizeB += sizeA;

	for (int i = 0; i < sizeB; i++)
		printf("%d ", B[i]);

	while (true);
	return 0;
}
========================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int A[9] = { 5, 1, 2, 9, 7, 3, 5, 2, 8 };
	int sizeA = 9;

	int B[6] = { 90, 91, 91, 93, 94, 95 };
	int sizeB = 6;

	int C[15] = { 0 };
	int sizeC = sizeA + sizeB;

	int index = -1;

	printf("Enter index: ");
	scanf("%d", &index);

	int C[25];

	for (int i = 0; i < index; i++)
		C[i] = A[i];

	for (int i = 0; i < sizeB; i++)
		C[i + index] = B[i];

	for (int i = index; i < sizeA; i++)
		C[i + sizeB] = A[i];

	while (true);
	return 0;
}
====================================
#include <stdio.h>

int main()
{
	int A[20] = { 5, 11, 12, 9, 7, 3, 15, 20, 19, 1, 18, 8, 17, 13, 6, 16, 14, 2, 10, 4 };
	int sizeA = 20;

	int B[5] = { 7, 3, 13, 18, 4 };
	int sizeB = 5;

	bool isArrayExist = true;

	for (int i = 0; i < sizeB; i++)
	{
		for (int j = 0; j < sizeA; j++)
		{
			if (B[i] == A[j])
				break;

			if (j == (sizeA - 1))
				isArrayExist = false;

		}
	}

	if (isArrayExist == true)
		printf("=> YES");
	else
		printf("=> NO");

	while (true);
	return 0;
}
=========================================
#include <stdio.h>

int main()
{
	int A[20] = { 5, 11, 12, 9, 7, 3, 15, 20, 19, 1, 18, 8, 17, 13, 6, 16, 14, 2, 10, 4 };
	int sizeA = 20;

	int B[5] = { 7, 3, 15, 20, 19 };
	int sizeB = 5;

	bool isArrayExist = false;

	for (int i = 0, j = 0; i < sizeA; i++)
	{
		if (B[j] == A[i])
		{
			if (j < sizeB)
				j += 1;

			if (j == sizeB - 1)
            {
				isArrayExist = true;
				break;
			}
		}
		else
		{
			j = 0;
		}
	}

	if (isArrayExist == true)
		printf("=> YES");
	else
		printf("=> NO");

	while (true);
	return 0;
}