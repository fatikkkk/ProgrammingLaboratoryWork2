#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int minValueArr, maxValueArr;
steady_clock::time_point startTime;
steady_clock::time_point endTime;

void displayArray(int arr[], int sizeArr) {
	for (int i = 0; i < sizeArr; i++)
		cout << arr[i] << " ";

	cout << "\n\n";
}

void fillArray(int arr[], int sizeArr) {
	const int minRand = -99, maxRand = 99;
	for (int i = 0; i < sizeArr; i++)
		arr[i] = rand() % (maxRand - minRand + 1) + minRand;
	
}

void bruteForceSort() {
	const int sizeArray = 100;
	int arrayNum[sizeArray];
	fillArray(arrayNum, sizeArray);
	displayArray(arrayNum, sizeArray);

	startTime = steady_clock::now();
	bool isSwapped;
	for (int i = 0; i <= sizeArray; i++)
		for (int j = 0; j <= sizeArray; j++)
			if (arrayNum[j] < arrayNum[i])
			{
				int temp = arrayNum[j];
				arrayNum[j] = arrayNum[i];
				arrayNum[i] = temp;
			}
	endTime = steady_clock::now();

	displayArray(arrayNum, sizeArray);
	cout << "Time spent Brute Force Sorting: " 
		<< duration_cast<nanoseconds>(endTime - startTime).count() 
		<< " nanoseconds.\n\n";

}

void quickSort(int arr[], int left, int right) {
	if (left > right) 
		return;

	int supportElem = arr[left + right] / 2;
	int leftArr = left, rightArr = right;

	while (leftArr <= rightArr)
	{
		while (arr[leftArr] < supportElem)
			leftArr++;

		while (arr[rightArr] > supportElem)
			rightArr--;

		if (leftArr <= rightArr)
		{
			int temp = arr[leftArr];
			arr[leftArr] = arr[rightArr];
			arr[rightArr] = temp;
			leftArr++;
			rightArr--;
		}
	}

	quickSort(arr, left, rightArr);
	quickSort(arr, leftArr, right);
}

int main()
{   
    bool isLive = true;
	while (isLive)
	{
		int userSelectNum;
		cout << "Please, Select a number to choose actions with array: \n";
		cout << "\t 1 - Brute Force Sorting\n";
		cout << "\t 2 - Quick Sorting\n";
		cout << "\t 3 - Merge Sorting\n";
		cout << "\t 4 - Search Min and Max value\n";
		cout << "\t 5 - Display Average Min and Max\n";
		cout << "\t 5 - Display Count Less Value\n";
		cout << "\t 5 - Binary Search\n";
		cout << "\t 5 - Swap value\n";
		cout << "Number: ";
		cin >> userSelectNum;

		switch (userSelectNum)
		{
		case 1:
			bruteForceSort();
			break;

		case 2:
			const int sizeArray = 100;
			int arrayNum[sizeArray];
			fillArray(arrayNum, sizeArray);
			displayArray(arrayNum, sizeArray);
			quickSort(arrayNum, 0, sizeArray - 1);

			displayArray(arrayNum, sizeArray);
			cout << "case 2";
		default:
			break;
		}
	}
    cout << "Hello World!\n";
}
