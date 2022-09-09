#include <iostream>
#include<ctime>
#include<Windows.h>
#include <iomanip>

using namespace std;


const int MAX_ARR_SIZE = 100;

int Hoarasort(int L, int R, int A[])
{
	int counter = 0;
	int i, j; float bar, w;
	i = L; j = R; counter += 2;
	bar = A[(L + R) / 2]; counter += 3;
	do
	{
		counter++;
		while (A[i] < bar) {
			i++; counter += 2;
		};
		counter++;
		while (bar < A[j]) {
			j--; counter += 2;
		}
		counter++;
		if (i <= j) {
			w = A[i]; A[i] = A[j]; A[j] = w;
			i++; j--; counter += 5;
		}
		counter++;
	} while (i <= j);
	counter++;
	if (L < j) counter += Hoarasort(L, j, A);
	counter++;
	if (i < R) counter += Hoarasort(i, R, A);
	return counter;
}

int SortedArr(int j) {

	int* arr = new int[j];
	for (int i = 0; i < j; i++)
		arr[i] = i;
	int result = Hoarasort(0, j - 1, arr);
	delete[] arr;
	return result;
}

int maximumСomplexityAgorithmArr(int j) {
	int* arr = new int[j+1];
	arr[0] = 0;
	for (int i = 1; i < j; i++) {
		int c = (i + 1) / 2;
		arr[i] = arr[c];
		arr[c] = i;
	}
	int result = Hoarasort(0, j - 1, arr);
	delete[] arr;
	return result;
}

double RandomArr(int j) {
	double resultSort = 0;
	int* arr = new int[j];
	for (int k = 0; k < 10000; k++) {
		for (int i = 0; i < j; i++)
			arr[i] = rand() % 1000;
		resultSort += Hoarasort(0, j - 1, arr);
	}
	delete[]arr; 
	return resultSort / 10000;
}

int main()
{

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	srand(time(NULL));
	cout <<setw(12)<<"Минимальная||"<<setw(8)<<"Максимальная"<<setw(11)<<"||Средняя\n";
	for (int j = 0; j <= MAX_ARR_SIZE; j++) {
		cout <<setw(3)<<j<<setw(8)<<SortedArr(j) << "||"<<setw(9) << maximumСomplexityAgorithmArr(j) <<setw(6)<<"||" << RandomArr(j) << endl;
	}
}