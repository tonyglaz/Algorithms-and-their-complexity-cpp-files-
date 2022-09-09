#include <iostream>
#include <vector>
#include <stack>
#include <ctime>

using namespace std;

const int oo = 88888888;
int sum;
double counter, result;

pair<int, int> arc;

vector < vector< pair<int, int>>> fillingGraph(int i, double probability) {
	vector < vector < pair<int, int> > > Graph;
	Graph.resize(i);
	for (int r = 0; r < i; r++) {
		for (int m = 0; m < i; m++) {
			int localProbability = rand() % 10;
			if ((m != r) && ((0.1 * localProbability) < probability)) {
				arc.first = m;
				arc.second = (rand() % 100) + 1;
				Graph[r].push_back(arc);
			}
		}
	}
	return Graph;
}

double Algorithm(int i, vector < vector < pair<int, int> > > Graph) {
	 result = 0;
	 sum = 0;
	 counter = 0;
	for (int r = 0; r < i; r++) {
		vector<int> dist(i, oo);
		dist[r] = 0;
		vector<char> u(i);
		for (int a = 0; a < i; ++a) {
			int v = -1;
			for (int j = 0; j < i; ++j)
				if (!u[j] && (v == -1 || dist[j] < dist[v]))
					v = j;
			if (dist[v] == oo)
				break;
			u[v] = true;
			for (int j = 0; j < Graph[v].size(); j++) {
				int to = Graph[v][j].first, len = Graph[v][j].second;
				if (dist[v] + len < dist[to])
					dist[to] = dist[v] + len;
			}
		}
		for (int m = 0; m < dist.size(); m++)
			if ((dist[m] != oo) && (dist[m] != 0)) {
				sum += dist[m];
				counter++;
			}
	}
	if (counter != 0)
		result = sum / counter;
	return result;
}

int main() {
	setlocale(0, "");
	srand(time(NULL));
	double finally=0;
	for (int i=2; i <= 10; i++) {
		cout << "-------------\n";
		cout << "Число вершин:" << i << endl;
		cout << "-------------\n";
		for (double j = 0.1; j <= 1; j += 0.1) {
			finally = 0;
			vector < vector < pair<int, int> > > Graph;
			for (int k = 0; k < 1000; k++) {
				Graph=fillingGraph(i,j);
				finally+=Algorithm(i,Graph);
			}
			finally /= 1000;
				cout << " Вероятность наличия ребра: " << j << " Среднее значение кратчайшего пути: " << finally << endl;
		}
	}
}
