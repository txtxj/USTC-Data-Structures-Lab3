 #pragma once

#define MAXVEX 30000000
#define MAXEDGE 60000000
#define MAXDIS 0x3f

#include "FibHeap.cpp"
#include "Graph.h"
#include <cstring>
#include <cstdio>
#include <utility>
#include <queue>

Graph::Graph(int n = 0)
{
	vexNum = n;
	edgeNum = 0;

	head = new int[MAXVEX];
	edge = new Arc[MAXEDGE];
	pre = new int[MAXVEX];
	dis = new int[MAXVEX];

	std::memset(head, 0, MAXVEX * sizeof(int));
}

Graph::~Graph()
{
	delete[] head;
	delete[] edge;
	delete[] pre;
	delete[] dis;
}

void Graph::SetVexNum(int n)
{
	vexNum = n;
}

const int Graph::GetVexNum(void) const
{
	return vexNum;
}

void Graph::AddEdge(int u, int v, int d)
{
	edge[++edgeNum] = Arc{v, d, head[u]};
	head[u] = edgeNum;
}

void Graph::Dijkstra(int u)
{
	bool* vis = new bool[MAXVEX];
	std::memset(pre, 0, MAXVEX * sizeof(int));
	std::memset(dis, MAXDIS, MAXVEX * sizeof(int));
	std::memset(vis, 0, MAXVEX * sizeof(bool));
	int s = u;
	dis[s] = 0;
	while (!vis[s])
	{
		vis[s] = true;
		for (int i = head[s]; i != 0; i = edge[i].nxt)
		{
			if (!vis[edge[i].v] && dis[edge[i].v] > dis[s] + edge[i].dis)
			{
				pre[edge[i].v] = s;
				dis[edge[i].v] = dis[s] + edge[i].dis;
			}
		}
		int m = 0x7fffffff;
		for (int i = 1; i <= vexNum; i++)
		{
			if (!vis[i] && m > dis[i])
			{
				m = dis[i];
				s = i;
			}
		}
	}
	delete[] vis;
}

void Graph::DijkstraHeap(int u)
{
	bool* vis = new bool[MAXVEX];
	std::memset(pre, 0, MAXVEX * sizeof(int));
	std::memset(dis, MAXDIS, MAXVEX * sizeof(int));
	std::memset(vis, 0, MAXVEX * sizeof(bool));
	dis[u] = 0;
	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > Q;
	Q.push(std::pair<int, int>(0, u));
	while (!Q.empty())
	{
		int x = Q.top().second;
		Q.pop();
		if (vis[x])
		{
			continue;
		}
		vis[x] = true;
		for (int i = head[x]; i != 0; i = edge[i].nxt)
		{
			if (!vis[edge[i].v] && dis[edge[i].v] > dis[x] + edge[i].dis)
			{
				pre[edge[i].v] = x;
				dis[edge[i].v] = dis[x] + edge[i].dis;
				Q.push(std::pair<int, int>(dis[edge[i].v], edge[i].v));
			}
		}
	}
	delete[] vis;
}

void Graph::DijkstraFib(int u)
{
	bool* vis = new bool[MAXVEX];
	std::memset(pre, 0, MAXVEX * sizeof(int));
	std::memset(dis, MAXDIS, MAXVEX * sizeof(int));
	std::memset(vis, 0, MAXVEX * sizeof(bool));
	dis[u] = 0;
	FibHeap<std::pair<int, int> >Q;
	Q.MakeHash(vexNum + 1);
	for (int i = 1; i <= vexNum; i++)
	{
		Q.Insert(std::pair<int, int>(dis[i], i), i);
	}
	while (!Q.Empty())
	{
		int x = Q.Minimum().second;
		Q.RemoveMin();
		if (vis[x])
		{
			continue;
		}
		vis[x] = true;
		for (int i = head[x]; i != 0; i = edge[i].nxt)
		{
			if (!vis[edge[i].v] && dis[edge[i].v] > dis[x] + edge[i].dis)
			{
				Q.Update(edge[i].v, std::pair<int, int>(dis[x] + edge[i].dis, edge[i].v));
				pre[edge[i].v] = x;
				dis[edge[i].v] = dis[x] + edge[i].dis;
			}
		}
	}
	delete[] vis;
}

const int Graph::PrintPath(int u, int v) const
{
	int* st = new int[MAXVEX];
	int top = 0;
	while (u != v)
	{
		st[++top] = v;
		v = pre[v];
	}
	std::printf("PATH: %d", u);
	while (top)
	{
		std::printf(" -> %d", st[top--]);
	}
	std::putchar('\n');
	v = st[1];
	delete[] st;
	return dis[v];
}
