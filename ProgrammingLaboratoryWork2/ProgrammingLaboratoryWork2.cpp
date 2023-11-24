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

void merge(int array[], int const left, int const mid,
	int const right)
{
	int const subArrayOne = mid - left + 1;
	int const subArrayTwo = right - mid;

	auto* leftArray = new int[subArrayOne],
		* rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return;

	int mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
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

void countLessValue(int arr[], int sizeArr, int value) {
	int countLess = 0;
	
	for (countLess = 0; countLess < sizeArr; countLess++)
	{
		if (arr[countLess] >= value)
			break;
	}

	cout << "Count less value a: " << countLess << "\n";
}

void countMoreValue(int arr[], int sizeArr, int value) {
	int countMore;
	
	for (countMore = sizeArray - 1; countMore >= 0; countMore--)
	{
		if (arr[countMore] <= value)
			break;
	}

	cout << "Count more value: " << sizeArray - 1 - countMore << "\n";
}

int linearSearch(int arr[], int sizeArr, int value) {
	startTime = steady_clock::now();
	for (int i = 0; i < sizeArr; i++)
	{
		if (value == arr[i])
		{
			endTime = steady_clock::now();
			return i;
		}
	}
	endTime = steady_clock::now();
	return -1;
}

int binarySearch(int arr[], int sizeArr, int value) {
	startTime = steady_clock::now();
	int low = 0, high = sizeArr - 1;
	while (low <= high)
	{
		int middle = low + (high - low) / 2;
		if (value == arr[middle]) {
			endTime = steady_clock::now();
			return middle;
		}

		if (value > arr[middle]) {
			low = middle + 1;
		}

		if (value < arr[middle]) {
			high = middle - 1;
		}
	}
	endTime = steady_clock::now();
	return -1;
}

void swapElement(int arr[], int sizeArr, int first, int second) {
	startTime = steady_clock::now();
	if (first < 0 || second < 0 || first >= sizeArr || second >= sizeArr) {
		endTime = steady_clock::now();
		cout << "Error! Incorrect values.\n\n";
		return;
	}
	else {
		int temp = arr[first];
		arr[first] = arr[second];
		arr[second] = temp;
	}
	endTime = steady_clock::now();
	cout << "Time spent Swap Element: "
		<< duration_cast<nanoseconds>(endTime - startTime).count()
		<< " nanoseconds.\n\n";
}

int main()
{   
    bool isLive = true;
	while (isLive)
	{
		int arrayNum[sizeArray];
		fillArray(arrayNum, sizeArray);
		int userSelectNum, chooseUserArray, numberUser, result;

		int firstIndex, secondIndex;

		bool isSort;

		cout << "Please, Select a number to choose actions with array: \n";
		cout << "\t 1 - Brute Force Sorting\n";
		cout << "\t 2 - Quick Sorting\n";
		cout << "\t 3 - Merge Sorting\n";
		cout << "\t 4 - Search Min and Max value\n";
		cout << "\t 5 - Display Average Min and Max\n";
		cout << "\t 6 - Display Count Less Value\n";
		cout << "\t 7 - Display Count More Value\n";
		cout << "\t 8 - Binary Search\n";
		cout << "\t 9 - Swap value\n";
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
			displayArray(arrayNum, sizeArray);
			startTime = steady_clock::now();
			mergeSort(arrayNum, 0, sizeArray - 1);
			endTime = steady_clock::now();
			displayArray(arrayNum, sizeArray);
			cout << "Time spent Merge Sorting: "
				<< duration_cast<nanoseconds>(endTime - startTime).count()
				<< " nanoseconds.\n\n";
			cout << "=====================================================================================\n\n";
			break;

		case 4:
			cout << "============================= Search Min and Max value ==============================\n";
			cout << "Do you want Search Min and Max in?\n";
			cout << "\t1 - UnSorted Array\n";
			cout << "\t2 - Sorted Array\n";
			cout << "Number: ";
			cin >> chooseUserArray;
			switch (chooseUserArray)
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
			cin >> chooseUserArray;
			switch (chooseUserArray)
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
			break;

		case 6:
			cout << "=========================== Display Count Less value ================================\n";
			quickSort(arrayNum, 0, sizeArray - 1);
			displayArray(arrayNum, sizeArray);
			cout << "Add a number for search count less value: ";
			cin >> numberUser;
			countLessValue(arrayNum, sizeArray, numberUser);
			cout << "=====================================================================================\n\n";
			break;
			
		case 7:
			cout << "=========================== Display Count More value ================================\n";
			quickSort(arrayNum, 0, sizeArray - 1);
			displayArray(arrayNum, sizeArray);
			cout << "Add a number for search count more value: ";
			cin >> numberUser;
			countMoreValue(arrayNum, sizeArray, numberUser);
			cout << "=====================================================================================\n\n";
			break;
		
		case 8:
			cout << "================================= Binary Search =====================================\n";
			quickSort(arrayNum, 0, sizeArray - 1);
			displayArray(arrayNum, sizeArray);
			cout << "Add a number for search element in array: ";
			cin >> numberUser;

			result = linearSearch(arrayNum, sizeArray, numberUser);
			cout << "\nTime spent Linear Search: "
				<< duration_cast<nanoseconds>(endTime - startTime).count()
				<< " nanoseconds.\n\n";
			
			result = binarySearch(arrayNum, sizeArray, numberUser);
			cout << "Time spent Binary Search: "
				<< duration_cast<nanoseconds>(endTime - startTime).count()
				<< " nanoseconds.\n\n";

			result == -1 
				? cout << "Given value does not exist in the array!\n"
				: cout << "The Index of the value is: " << result << "!\n";
			cout << "=====================================================================================\n\n";
			break;

		case 9:
			cout << "================================= Swap Elements =====================================\n";
			displayArray(arrayNum, sizeArray);
			cout << "Add a first index: ";
			cin >> firstIndex;

			cout << "Add a second index: ";
			cin >> secondIndex;

			swapElement(arrayNum, sizeArray, firstIndex, secondIndex);

			displayArray(arrayNum, sizeArray);
			cout << "=====================================================================================\n\n";
			break;
		default:
			break;
		}
	}
    cout << "Hello World!\n";
}
