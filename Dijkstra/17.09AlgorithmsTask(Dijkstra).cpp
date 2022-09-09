#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
using namespace std;

const int N = 10;

const int oo = 88888888;
int sum; double result;
pair<int, int> arc;
bool Adj[N][N];

vector < vector< pair<int, int>>> fillingTree(int n) {
	vector < vector < pair<int, int> > > Graph(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			Adj[i][j] = false;

	for (int i = 1; i < n; i++) {
		int to = rand() % i;
		Graph[i].emplace_back(to, rand() % 1000 + 1);
		Graph[to].emplace_back(i, rand() % 1000 + 1);
		Adj[i][to] = true;
		Adj[to][i] = true;
	}
	return Graph;
}

vector < vector< pair<int, int>>> fillingGraph(int n, int m) {
	vector < vector < pair<int, int> > > Graph = fillingTree(n);
	for (int i = n - 1; i < m; i++) {
		while (true) {
			int from = rand() % n;
			int to = rand() % n;
			if (from == to) continue;
			bool isAlreadyThere = Adj[from][to];
			if (isAlreadyThere) continue;
			Graph[from].emplace_back(to, rand() % 1000 + 1);//push_back добавляет копию объекта (или обеспечивает перемещение, если возможно)
			Graph[to].emplace_back(from, rand() % 1000 + 1);// а emplace_back создает объект непосредственно в конце вектора, т.е. без лишнего копирования (или перемещения).
			Adj[from][to] = true;
			Adj[to][from] = true;
			break;
		}
	}
	return Graph;
}

int Algorithm(int i, vector < vector < pair<int, int> > > Graph) {
	result = 0;
	sum = 0;
	int counter = 2;
	for (int r = 0; r < i; r++) {
		vector<int> dist(i, oo);
		counter += i;
		dist[r] = 0;
		counter++;
		vector<char> u(i);
		counter += i;
		for (int a = 0; a < i; ++a) {
			int v = -1;
			counter++;
			for (int j = 0; j < i; ++j) {
				counter++;
				if (!u[j]) {
					counter++;
					if (v == -1) {
						v = j; 
						counter++;
					}
					else {
						counter++;
						if (dist[j] < dist[v]) {
							v = j; 
							counter++;
						}
					}
				}
			}
			counter++;
			if (dist[v] == oo)
				break;
			u[v] = true;
			counter++;
			for (int j = 0; j < Graph[v].size(); j++) {
				int to = Graph[v][j].first, len = Graph[v][j].second; 
				counter += 2;
				counter += 2;
				if (dist[v] + len < dist[to]) {
					dist[to] = dist[v] + len;
					counter += 2;
				}
			}
		}
	}
	return counter;
}

int main() {
	setlocale(0, "");
	srand(time(NULL));

	for (int n = 2; n <= 10; n++) {
		cout << "Number of operations with " << n << " vertices: " << endl;
		for (int m = n - 1; m <= n * (n - 1) / 2; m++) {
			double count = 0;
			for (int i = 0; i < 1000; i++) {
				vector < vector< pair<int, int>>> graph = fillingGraph(n, m);
				count += Algorithm(n, graph);
			}
			cout << "number of edges  " << m << " : " << count / 1000 << endl;
		}
		cout << endl;
	}
}