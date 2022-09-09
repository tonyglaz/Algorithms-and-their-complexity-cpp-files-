#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

const int BASE = 10;//Десятичная система счисления
float karatsuba_counter;
float naive_counter;

vector<unsigned int> GenerateNum(int n) {
	vector< unsigned int > vector(n);
	for (int i = 0; i < n - 1; i++)
		vector[i] = rand() % 10;
	vector[n - 1] = rand() % 9 + 1;
	return vector;
}

pair<vector<unsigned int>, vector<unsigned int>> DivideNumInto2Parts(const vector<unsigned int>& temp) {
	int n = temp.size();
	int tempHalf = (n + 1) / 2;
	vector< unsigned int > leftHalf(tempHalf);
	vector< unsigned int > rightHalf(tempHalf);
	for (int i = 0; i < tempHalf; i++)
		leftHalf[i] = temp[i];
	for (int i = tempHalf; i < n; i++)
		rightHalf[i - tempHalf] = temp[i];
	return make_pair(rightHalf, leftHalf);
}

int Fill_Petrenko(vector<unsigned int> & vectorA, vector<unsigned int>& vectorB) {
	int n;
	if (vectorA.size() > vectorB.size())
		 n = vectorA.size();
	else
		 n = vectorB.size();
	vectorA.resize(n); vectorB.resize(n);
	return n;
}

int Strip(vector<unsigned int>& vector) {
	for (int i = vector.size() - 1; i >= 0; i--) {
		if (vector[i] != 0) {
			vector.resize(i + 1);
			return i + 1;
		}
	}
	vector.resize(1);
	return 1;
}

vector<unsigned int> Addition(vector<unsigned int> vectorA, vector<unsigned int> vectorB) {
	int n =  Fill_Petrenko(vectorA, vectorB);
	int transfer = 0;//хранит перенос
	for (int i = 0; i < n; i++) {
		vectorA[i] += vectorA [i] + transfer;//идем от младших (справа) к старшим (слева) разрядам  и складываем
		karatsuba_counter++;
		if (vectorA[i] >= BASE) {//Если получилось больше, чем основание системы счисления то это перенос
			vectorA[i] -= BASE;//вычитаем 10 из результата(берем 1 цифру)
			transfer = 1;// запоминаем перенос в transfer
			karatsuba_counter++;
		}
		else transfer = 0;
	}
	if (transfer == 1) {
		vectorA.resize(n + 1);
		vectorA[n] = 1;
	}
	return vectorA;
}

vector<unsigned int>  Subtract(vector<unsigned int> vectorA, vector<unsigned int> vectorB) {
	int n =  Fill_Petrenko(vectorA, vectorB);
	int transfer = 0;
	for (int i = 0; i < n; i++) {
		if (vectorB[i] >= vectorB[i] + transfer) {
			vectorA[i] -= vectorB[i] + transfer;
			transfer = 0;
		}
		else {
			vectorA[i] = BASE + vectorA[i] - vectorB[i] - transfer;
			transfer = 1;
		}
		karatsuba_counter++;
	}
	return vectorA;
}


vector<unsigned int>  Naive_Mul(vector<unsigned int>  vectorA, vector<unsigned int>  vectorB) {
	int n =  Fill_Petrenko(vectorA, vectorB);
	vector<unsigned int> result(2 * n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result[i + j] += vectorA[i] * vectorB[j];
			naive_counter++;
		}
	}
	int transfer = 0;
	for (int i = 0; i < 2 * n; i++) {
		result[i] += transfer;
		naive_counter++;
		if (result[i] >= BASE) {
			transfer = result[i] / BASE;
			naive_counter++;
			result[i] %= BASE;
			naive_counter++;
		}
		else transfer = 0;
	}
	Strip(result);
	return result;
}

vector<unsigned int> Shift(const vector<unsigned int>& vectorA, int s) {
	vector<unsigned int>  result(vectorA.size() + s);
	for (int i = 0; i < vectorA.size(); i++)
		result[s + i] = vectorA[i];
	karatsuba_counter++;
	return result;
}

//void OutputVector(vector<unsigned int> someVector) {
//	int n = Strip(someVector);
//	for (int i = n - 1; i >= 0; i--)
//		cout << someVector[i];
//}

vector<unsigned int> Karatsuba_Mul(vector<unsigned int> vectorA, vector<unsigned int> vectorB) {
	int n =  Fill_Petrenko(vectorA, vectorB);
	if (n == 1) {
		unsigned int result = vectorA[0] * vectorB[0];
		karatsuba_counter++;
		if (result >= BASE) {
			vector<unsigned int> someVec{ result % BASE, result / BASE };//0-й элемент будет остаток от деления, а 1-й элемент - частное
			return someVec;
		}
		else {
			return vector<unsigned int>(1, result);
		}
	}

	int vecotrHalf = (n + 1) / 2;
	pair<vector<unsigned int>, vector<unsigned int>> dividedIntoPartsA = DivideNumInto2Parts(vectorA);
	pair<vector<unsigned int>, vector<unsigned int>> dividedIntoPartsB = DivideNumInto2Parts(vectorB);
	vector<unsigned int> vectorA1 = dividedIntoPartsA.first;
	vector<unsigned int>vectorA2 = dividedIntoPartsA.second;
	vector<unsigned int> vectorB1 = dividedIntoPartsB.first;
	vector<unsigned int> vectorB2 = dividedIntoPartsB.second;
	vector<unsigned int> vectorA1B1 = Karatsuba_Mul(vectorA1, vectorB1);
	vector<unsigned int> vectorA2B2 = Karatsuba_Mul(vectorA2, vectorB2);
	vector<unsigned int> sumProduct = Karatsuba_Mul(Addition(vectorA1, vectorA2), Addition(vectorB1, vectorB2));
	vector<unsigned int> part1 = Shift(vectorA1B1, 2 * vecotrHalf);
	vector<unsigned int> part2 = Shift(Subtract(Subtract(sumProduct, vectorA1B1), vectorA2B2), vecotrHalf);
	vector<unsigned int> part3 = vectorA2B2;
	return Addition(Addition(part1, part2), part3);
}

void main() {
	srand(time(NULL));
	vector< unsigned int > vector1;  vector<unsigned  int> vector2;
	vector<unsigned  int> vector3;  vector<unsigned  int> vector4;
	for (int n = 10; n <= 10000; n++) {
		karatsuba_counter = 0;
		naive_counter = 0;
		for (int i = 0; i < 10; i++) {
			vector1 = GenerateNum(n);
			vector2 = GenerateNum(n);
			vector3 = Naive_Mul(vector1, vector2);
		    vector4 = Karatsuba_Mul(vector1, vector2);
		}
		if ((karatsuba_counter / 100) < (naive_counter / 100))
			cout << "Алгоритм Карацубы превзошел обыкновенный алгоритм перемножения чисел при n=" << n <<"!!!\n";
		if (n < 10) {
			cout << "n=" << n << "  /|\\ " << karatsuba_counter / 100 << endl;
			cout << "n=" << n << "  /|\\ " << naive_counter / 100 << endl;
		}
		else {
			cout << "n=" << n << " /|\\ " << karatsuba_counter / 10<<"(karatsuba)" << endl;
			cout << "n=" << n << " /|\\ " << naive_counter / 10 << endl;
		}
	}
}