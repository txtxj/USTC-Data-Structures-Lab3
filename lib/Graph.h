#ifndef GRAPH
#define GRAPH

class Graph
{
private:
	// 边
	class Arc
	{
	public:
		int v;		// 终点
		int dis;	// 距离
		int nxt;	// 前向星下一条边
	};

	int vexNum;		// 顶点数
	int edgeNum;	// 边数

	int* head;		// 首条边链表
	Arc* edge;		// 边链表

	int* pre;		// 前驱
	int* dis;		// 距离

public:
	Graph(const int n);
	~Graph();
	// 设定顶点数，初始化
	void SetVexNum(int n);
	// 获取顶点数
	const int GetVexNum() const;
	// 加边
	void AddEdge(const int u, const int v, const int d);
	// 朴素算法
	void Dijkstra(const int u, const int v);
	// STL算法
	void DijkstraHeap(const int u, const int v);
	// Fib堆算法
	void DijkstraFib(const int u, const int v);
	// 输出最短路
	const int PrintPath(const int u, const int v) const;
};

#endif