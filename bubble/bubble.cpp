#include <iostream>
#include<ctime>
#include<Windows.h>

using namespace std;
const int MAX_ARR_SIZE = 30;

int BubbleSort(int arr[], int arrSize) {
	int counter = 0, temp;
	for (int i = 0; i < arrSize - 1; i++) {
		for (int j = 0; j < arrSize - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				counter += 3;
			}
			counter++;
		}
	}
	return counter;
}

void SortedArr() {
	for (int j = 0; j <= MAX_ARR_SIZE; j++) {
		int* arr = new int[j];
		for (int i = 0; i < j; i++)
			arr[i] = i;
		cout << "Количество операций при упорядоченном массиве размера " << j << ":  " << BubbleSort(arr, j) << endl;
		delete[] arr;
	}
	cout << endl << endl;
}

void SortedInReverseOrderArr() {
	for (int j = 0; j <= MAX_ARR_SIZE; j++) {
		int* arr = new int[j];
		for (int i = 0; i < j; i++)
			arr[i] = j - i;
		cout << "Количество операций при реверсивном массиве размера " << j << ":  " << BubbleSort(arr, j) << endl;
		delete[] arr;
	}
	cout << endl << endl;
}

void RandomArr() {
	double resultBubbleSort = 0;
	for (int j = 0; j <= MAX_ARR_SIZE; j++) {
		int* arr = new int[j];
		for (int k = 0; k < 10000; k++) {
			for (int i = 0; i < j; i++)
				arr[i] = rand() % 1000;
			resultBubbleSort += BubbleSort(arr, j);
		}
		cout << "Количество операций при случайно заполненном массиве размера " << j << ":  " << resultBubbleSort / 10000 << endl;
		delete[]arr; resultBubbleSort = 0;
	}
	cout << endl << endl;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	SortedArr();
	SortedInReverseOrderArr();
	RandomArr();
}
