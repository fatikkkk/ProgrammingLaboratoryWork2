#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

const int sizeArray = 100;
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
	int arrayNum[sizeArray];
	fillArray(arrayNum, sizeArray);
	displayArray(arrayNum, sizeArray);

	startTime = steady_clock::now();
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
		<< " nanoseconds.\n";

}

void quickSort(int arr[], int left, int right) {
	if (left > right) 
		return;

	int supportElem = arr[(left + right) / 2];
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

void searchMinMax(int arr[], int sizeArr, bool isSort) {
	startTime = steady_clock::now();
	if (isSort)
	{
		minValueArr = arr[0];
		maxValueArr = arr[sizeArr - 1];
	}
	else {
		minValueArr = arr[0], maxValueArr = arr[0];
		for (int i = 0; i < sizeArr; i++)
		{
			if (arr[i] <= minValueArr)
				minValueArr = arr[i];

			if (arr[i] >= maxValueArr)
				maxValueArr = arr[i];
		}
	}
	endTime = steady_clock::now();
}

void averageMinMax(int arr[], int sizeArr, bool isSort) {
	int avgValue = 0;
	int countAvg = 0;

	searchMinMax(arr, sizeArr, isSort);
	avgValue = (minValueArr + maxValueArr) / 2;
	cout << "Average Value in Array: " << avgValue << "\n";

	cout << "Index element array equal to the average value: ";
	startTime = steady_clock::now();
	for (int i = 0; i < sizeArr; i++)
	{
		if (arr[i] == avgValue)
		{
			cout << i << " ";
			countAvg++;
		}
	}
	endTime = steady_clock::now();
	cout << "\n";
	countAvg == 0 ? cout << "Index not found, Count 0\n" : cout << "Count index equal to the average value: " << countAvg << "\n";
	cout << "Time spent search count average value in array: " << duration_cast<nanoseconds>(endTime - startTime).count() << " nanoseconds.\n";
}
int main()
{   
    bool isLive = true;
	while (isLive)
	{
		int arrayNum[sizeArray];
		fillArray(arrayNum, sizeArray);
		int userSelectNum;

		int chooseUser;
		bool isSort;

		cout << "Please, Select a number to choose actions with array: \n";
		cout << "\t 1 - Brute Force Sorting\n";
		cout << "\t 2 - Quick Sorting\n";
		cout << "\t 3 - Merge Sorting\n";
		cout << "\t 4 - Search Min and Max value\n";
		cout << "\t 5 - Display Average Min and Max\n";
		cout << "\t 6 - Display Count Less Value\n";
		cout << "\t 7 - Binary Search\n";
		cout << "\t 8 - Swap value\n";
		cout << "Number: ";
		cin >> userSelectNum;
		cout << "\n";

		switch (userSelectNum)
		{
		case 1:
			cout << "================================== Brute Force Sort =================================\n";
			bruteForceSort();
			cout << "=====================================================================================\n\n";
			break;

		case 2:
			cout << "===================================== Quick Sort ====================================\n";
			displayArray(arrayNum, sizeArray);

			startTime = steady_clock::now();
			quickSort(arrayNum, 0, sizeArray - 1);
			endTime = steady_clock::now();

			displayArray(arrayNum, sizeArray);
			cout << "Time spent Quick Sorting: "
				<< duration_cast<nanoseconds>(endTime - startTime).count()
				<< " nanoseconds.\n\n";
			cout << "=====================================================================================\n\n";
			break;

		case 3:
			cout << "===================================== Merge Sort ====================================\n";
			cout << "=====================================================================================\n\n";
			break;

		case 4:
			cout << "============================= Search Min and Max value ==============================\n";
			cout << "Do you want Search Min and Max in?\n";
			cout << "\t1 - UnSorted Array\n";
			cout << "\t2 - Sorted Array\n";
			cout << "Number: ";
			cin >> chooseUser;
			switch (chooseUser)
			{
			case 1:
				isSort = false;
				searchMinMax(arrayNum, sizeArray, isSort);
				break;

			case 2:
				quickSort(arrayNum, 0, sizeArray - 1);
				isSort = true;
				searchMinMax(arrayNum, sizeArray, isSort);
				break;
			default:
				break;
			}
			cout << "Min value in array: " << minValueArr << "\n";
			cout << "Max value in array: " << maxValueArr << "\n";
			cout << "Time spent search min and max value in not sorting array: " << duration_cast<nanoseconds>(endTime - startTime).count() << " nanoseconds.\n";
			cout << "=====================================================================================\n\n";
			break;

		case 5:
			cout << "=========================== Average Min and Max value ===============================\n";
			cout << "Do you want Average search Min and Max in?\n";
			cout << "\t1 - UnSorted Array\n";
			cout << "\t2 - Sorted Array\n";
			cout << "Number: ";
			cin >> chooseUser;
			switch (chooseUser)
			{
			case 1:
				isSort = false;
				displayArray(arrayNum, sizeArray);
				averageMinMax(arrayNum, sizeArray, isSort);
				break;

			case 2:
				quickSort(arrayNum, 0, sizeArray - 1);
				isSort = true;
				displayArray(arrayNum, sizeArray);
				averageMinMax(arrayNum, sizeArray, isSort);
				break;
			default:
				break;
			}
			cout << "=====================================================================================\n\n";
		default:
			break;
		}
	}
    cout << "Hello World!\n";
}
