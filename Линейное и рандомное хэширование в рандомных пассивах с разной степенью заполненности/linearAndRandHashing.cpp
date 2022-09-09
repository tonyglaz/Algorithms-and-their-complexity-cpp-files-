#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;
float counter;

string RandomWord() {
    string example = "";
    int size = rand() % 10 + 1;
    for (int i = 0; i < size; i++) {
        if (rand() % 2 == 0) example += char('a' + rand() % ('z' - 'a'));
        else example += char('A' + rand() % ('Z' - 'A'));
    }
    return example;
}

void Shuffle(vector<string>& example)
{
    int n = example.size();
    for (int i = 0; i < n; i++)
    {
        int j = rand() % n;
        string temporal = example[j];
        example[j] = example[i];
        example[i] = temporal;
    }
}

int HashComputing(string example) {
    int hash_value = 0;
    for (int i = 0; i < example.size(); i++) {
        hash_value += example[i];
    }
    return hash_value;
}

void LineHashing(string mod) {
    for (int i = 0; i < 100; i++) {
        counter = 0;
        for (int j = 0; j < 1000; j++) {
            vector<string> myVector(i, "standart");
            myVector.resize(100);
            if (mod == "Shuffle")
                Shuffle(myVector);
            string new_word = RandomWord();
            int marker = HashComputing(new_word) % 100;
            counter++;
            while (myVector[marker] != "") {
                marker = (marker + 1) % 100;
                counter += 4;
            }
            myVector[marker] = new_word;
            counter++;
        }
        if (mod == "Shuffle") cout << "Линейное хэширование при случайно заполненном масиве со степенью заполненности = " << i << ": " << counter / 1000 << endl;
        else cout << "Линейное хэширование при последовательно заполненном масиве со степенью заполненности = " << i << ": " << counter / 1000 << endl;
    }
    cout << endl;
}

void RandomHashing(string mod) {
    for (int i = 0; i < 100; i++) {
        counter = 0;
        for (int j = 0; j < 1000; j++) {
            vector<string> myVector(i, "standart");
            myVector.resize(100);
            if (mod == "Shuffle")
                Shuffle(myVector);
            string new_word = RandomWord();
            int marker = HashComputing(new_word) % 100;
            int changeTo[1000];
            for (int k = 0; k < 1000; k++)
                changeTo[k] = rand() % 100 + 1;
            counter++;
            int new_change = 0;
            while (myVector[marker] != "") {
                marker = (marker + changeTo[new_change]) % 100;
                new_change = (new_change + 1) % 1000;
                counter += 7;
            }
            myVector[marker] = new_word;
            counter++;
        }
        if (mod == "Shuffle") cout << "Случайное хэширование при случайно заполненном масиве со степенью заполненности = " << i << ": " << counter / 1000 << endl;
        else cout << "Случайное хэширование при последовательно заполненном масиве со степенью заполненности = " << i << ": " << counter / 1000 << endl;
    }
    cout << endl;
}

int main() {
    setlocale(LC_ALL, 0);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(NULL));

    LineHashing("");
    cout << "/|\\" << endl<<endl;
    RandomHashing("");
    cout << "/|\\" << endl << endl;
    LineHashing("Shuffle");
    cout << "/|\\" << endl << endl;
    RandomHashing("Shuffle");
}