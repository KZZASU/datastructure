#pragma once

using namespace std;
typedef unsigned int vertex;
typedef int weight;

class Edge
{
private:
	vertex v1_;
	vertex v2_;
	weight w_;

public:
	Edge(vertex v1, vertex v2, weight w_ = 1);
	friend class Graph;
};

class Graph
{
private:
	vector<vertex> vertices_;
	vector<Edge> Edges_;

public:
	Graph() = delete;
	Graph(vertex);

	void SetEdge(vertex, vertex, weight);
	void SetEdge(vector<Edge>&);
	void SetEdge(Edge);
	vector<vector<weight>> adjacent_matrix();
	Graph minimum_span();

};

