#include<iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <string>
#include<fstream>
using namespace std;

pair<int, int> randDisjunctiveClause(int n) {
    while (true) {
        int rand_f = rand() % (n + 1);
        if (rand() % 2 == 1)
            rand_f -= 2 * rand_f;
        int rand_s = rand() % (n + 1);
        if (rand() % 2 == 1)
            rand_s -= 2 * rand_s;
        if (rand_f == 0 && rand_s == 0)
            continue;
        else return make_pair(rand_f, rand_s);
    }
}

vector <pair<int, int>> randCNF(int n) {
    vector <bool> literalIsUsing(n, false);
    vector <pair<int, int>> resultCNF;
    for (int i = 0; i < n * n; i++) {
        while (true) {
            pair<int, int> example = randDisjunctiveClause(n);
            pair<int, int> reverse_example = make_pair(example.second, example.first);
            if (find(resultCNF.begin(), resultCNF.end(), example) != resultCNF.end() || find(resultCNF.begin(), resultCNF.end(), reverse_example) != resultCNF.end())
            {
                continue;
            }
            else {
                if (example.first != 0)
                    literalIsUsing[abs(example.first) - 1] = true;
                if (example.second != 0)
                    literalIsUsing[abs(example.second) - 1] = true;
                resultCNF.push_back(example);
                break;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!literalIsUsing[i])
            resultCNF.push_back(make_pair((i + 1), 0));
    }
    return resultCNF;
}

int complexityOf2SAT(vector <pair<int, int>> CNF) {
    int counter = 0;
    bool process = true;
    while (process) {
        bool change_event = false;
        int size = CNF.size();
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (CNF[i] == make_pair(0, 0) || CNF[j] == make_pair(0, 0)) {
                    counter++;
                    process = false;
                    break;
                }
                if (CNF[i].first == CNF[j].first * (-1)) {
                    CNF.push_back(make_pair(CNF[i].second, CNF[j].second));
                    CNF.erase(CNF.begin() + i);
                    CNF.erase(CNF.begin() + j - 1);
                    counter += 3;
                    change_event = true;
                    break;
                }
                else if (CNF[i].first == CNF[j].second * (-1)) {
                    CNF.push_back(make_pair(CNF[i].second, CNF[j].first));
                    CNF.erase(CNF.begin() + i);
                    CNF.erase(CNF.begin() + j - 1);
                    counter += 3;
                    change_event = true;
                    break;
                }
                else if (CNF[i].second == CNF[j].first * (-1)) {
                    CNF.push_back(make_pair(CNF[i].first, CNF[j].second));
                    CNF.erase(CNF.begin() + i);
                    CNF.erase(CNF.begin() + j - 1);
                    counter += 3;
                    change_event = true;
                    break;
                }
                else if (CNF[i].second == CNF[j].second * (-1)) {
                    CNF.push_back(make_pair(CNF[i].first, CNF[j].first));
                    CNF.erase(CNF.begin() + i);
                    CNF.erase(CNF.begin() + j - 1);
                    counter += 3;
                    change_event = true;
                    break;
                }
            }
            if (!process || change_event)
                break;
        }
        if (!change_event)
            process = false;
    }
    return counter;
}


int main()
{
    ofstream kek("sss.txt");
    srand(time(NULL));
    for (int n = 1; n <= 50; n++) {
        double complexity = 0;
        for (int i = 0; i < 1000; i++) {
            vector <pair<int, int>> CNF = randCNF(n);
            complexity += complexityOf2SAT(CNF);
        }
        kek<< n << "\t" << complexity / 1000 << endl;
    }
}