#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;
vector<vector<int>> adjacent_matrix(unordered_map<int, vector<int>> G)
{
	vector<vector<int>> amat = {};
	std::size_t size_ = G.size();
	vector<int> dummy(size_ + 1);
	amat.push_back(dummy);

	for (auto v : G)
	{
		vector<int> row(size_ + 1);
		for (auto e : v.second)
		{
			row[e] = 1;
		}

		amat.push_back(row);
	};
	return amat;
}

void BFS(unordered_map<int, vector<int>> G, int start)
{
	vector<vector<int>> amat{ adjacent_matrix(G) };
	size_t size_ = G.size();
	vector<int> visited(size_ + 1);
	queue<int> q{};
	visited[start] = 1;
	q.push(start);

	cout << start << ' ';
	while (!q.empty())
	{
		int n = q.front();
		for (size_t j{ 0 }; j < size_ + 1; j++)
		{
			if ((visited[j] == 0) && (amat[n][j] == 1))
			{
				visited[j]++;
				cout << j << ' ';
				q.push(j);
			}
		}
		q.pop();
	}

}

int main()
{
	unordered_map<int, vector<int>> G{ {1,{2,3,4}},{2,{1,3}}, {3,{1,2,4,5}}, {4,{1,3}}, {5,{3,4,6,7}}, {6,{5}}, {7,{5}} };
	BFS(G, 3);
	return 0;
}