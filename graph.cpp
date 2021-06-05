#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include "graph.h"

using namespace std;

Edge::Edge(vertex v1, vertex v2, weight w)
{
	v1_ = v1;
	v2_ = v2;
	w_ = w;
}


Graph::Graph(vertex n)
{
	for (vertex j{ 1 }; j <= n; j++)
	{
		vertices_.push_back(j);
	}
};

void Graph::SetEdge(vertex v1, vertex v2, weight w)
{
	Edge e{ v1,v2,w };
	Edges_.push_back(e);
}

void Graph::SetEdge(vector<Edge>& vs)
{
	Edges_.insert(Edges_.end(), vs.begin(), vs.end());
}

void Graph::SetEdge(Edge e)
{
	Edges_.push_back(e);
}

void Graph::GetEdge()
{
	for (auto e : Edges_)
	{
		cout << e.v1_ << ' ' << e.v2_ << ' ' << e.w_ << '\n';
	}
}

vector<vector<weight>> Graph::adjacent_matrix()
{
	vector<vector<weight>> amat{};

	size_t size_ = vertices_.size();
	vector<weight> dummy(size_ + 1, INT_MAX);
	amat.push_back(dummy);

	for (size_t j{ 1 }; j < size_ + 1; j++)
	{
		vector<weight> row(size_ + 1, INT_MAX);
		amat.push_back(row);
	};

	for (Edge e : Edges_)
	{
		if ((amat[e.v1_][e.v2_] == INT_MAX) && (amat[e.v2_][e.v1_]) == INT_MAX)
		{
			amat[e.v1_][e.v2_] = e.w_;
			amat[e.v2_][e.v1_] = e.w_;
		}
	};

	for (size_t i{ 1 }; i < size_ + 1; i++)
	{
		for (size_t j{ 1 }; j < size_ + 1; j++)
		{
			if (amat[i][j] == INT_MAX) { cout << 0 << ' '; }
			else{ cout << amat[i][j] << ' '; }

		}
		cout << '\n';
	}
	cout << '\n';

	return amat;
}

Graph Graph::minimum_span()
{
	Graph Span(vertices_.size());
	Edge min_edge{ 0, 0, INT_MAX };

	for (size_t j{ 0 }; j < Edges_.size(); j++)
	{
		if (min_edge.w_ > Edges_[j].w_)
		{
			min_edge = Edges_[j];
		}
	}
	Span.SetEdge(min_edge);

	vector<vector<weight>> amat{ this->adjacent_matrix() };

	vector<weight> near(vertices_.size() + 1, min_edge.v2_);

	amat[min_edge.v1_][min_edge.v1_] = 0;
	amat[min_edge.v2_][min_edge.v2_] = 0;

	for (size_t i{ 1 }; i < vertices_.size() + 1; i++)
	{
		if (amat[min_edge.v1_][i] < amat[min_edge.v2_][i])
		{
			near[i] = min_edge.v1_;
		}
	}
	
	while (Span.Edges_.size() < Span.vertices_.size()-1)
	{
		int next_x = 0;
		for (size_t i{ 1 }; i < vertices_.size() + 1; i++)
		{
			if ((amat[next_x][near[next_x]] > amat[i][near[i]]) && (i != near[i]))
			{
				next_x = i;
			}
		}

		Span.SetEdge(next_x, near[next_x], amat[next_x][near[next_x]]);
		amat[next_x][next_x] = 0;

		for (size_t i{ 1 }; i < vertices_.size() + 1; i++)
		{
			if (amat[i][next_x] <= amat[i][near[i]])
			{
				near[i] = next_x;
			}
		}
	};
	
	return Span;
}



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

void bfs(unordered_map<int, vector<int>> G, int start)
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

void dfs(unordered_map<int, vector<int>> G, int start)
{
	size_t size_ = G.size();
	static vector<vector<int>> amat{ adjacent_matrix(G) };
	static vector<int> visited(size_ + 1);
	visited[start] = 1;

	cout << start << ' ';

	for (size_t j{ 0 }; j < size_ + 1; j++)
	{
		if ((visited[j] == 0) && (amat[start][j] == 1))
		{
			dfs(G, j);
			visited[j] = 1;
		}
	}
}

int main()
{
    unordered_map<int, vector<int>> g{ {1,{2,3,4}},{2,{1,3}}, {3,{1,2,4,5}}, {4,{1,3}}, {5,{3,4,6,7}}, {6,{5}}, {7,{5}} };
    unordered_map<int, vector<int>> g2{ {1,{2,3}}, {2,{1,4,5}},{3,{1,6,7}},{4,{2}},{5,{2}},{6,{3}},{7,{3}} };

	vector<Edge> edges{ {1,6,5}, {1,2,25}, {2,7,6},{2,3,9},{3,4,10},{4,5,12},{4,7,11},{5,6,40},{5,7,16}};

	Graph G{ 7 };

	G.SetEdge(edges);
	Graph Span_G{ G.minimum_span() };

	Span_G.GetEdge();
    return 0;
}
