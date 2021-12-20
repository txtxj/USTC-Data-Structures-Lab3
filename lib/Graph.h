#ifndef GRAPH
#define GRAPH

class Graph
{
private:
	class Arc
	{
	public:
		int v;
		int dis;
		int nxt;
	};

	int vexNum;
	int edgeNum;

	int* head;
	Arc* edge;

	int* pre;
	int* dis;

public:
	Graph(int);
	~Graph();

	void SetVexNum(int);

	const int GetVexNum(void) const;

	void AddEdge(int, int, int);

	void Dijkstra(int, int);

	void DijkstraHeap(int, int);

	void DijkstraFib(int, int);

	const int PrintPath(int, int) const;
};

#endif