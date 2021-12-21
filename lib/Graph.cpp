#define MAXVEX 30000000
#define MAXEDGE 60000000
#define MAXDIS 0x3f

#include "FibHeap.cpp"
#include "Graph.h"
#include <cstring>
#include <cstdio>
#include <utility>
#include <queue>

using std::printf;
using std::putchar;
using std::pair;
using std::priority_queue;
using std::greater;
using std::memset;
using std::vector;

Graph::Graph(const int n)
{
	vexNum = n;
	edgeNum = 0;

	head = new int[MAXVEX];
	edge = new Arc[MAXEDGE];
	pre = new int[MAXVEX];
	dis = new int[MAXVEX];

	memset(head, 0, MAXVEX * sizeof(int));
}

Graph::~Graph()
{
	delete[] head;
	delete[] edge;
	delete[] pre;
	delete[] dis;
}

void Graph::SetVexNum(const int n)
{
	vexNum = n;
}

const int Graph::GetVexNum() const
{
	return vexNum;
}

void Graph::AddEdge(const int u, const int v, const int d)
{
	edge[++edgeNum] = Arc{v, d, head[u]};
	head[u] = edgeNum;
}

void Graph::Dijkstra(const int u, const int v)
{
	bool* vis = new bool[MAXVEX];
	memset(pre, 0, MAXVEX * sizeof(int));
	memset(dis, MAXDIS, MAXVEX * sizeof(int));
	memset(vis, 0, MAXVEX * sizeof(bool));
	int s = u;
	dis[s] = 0;
	while (!vis[s])
	{
		if (s == v) break;
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

void Graph::DijkstraHeap(const int u, const int v)
{
	bool* vis = new bool[MAXVEX];
	memset(pre, 0, MAXVEX * sizeof(int));
	memset(dis, MAXDIS, MAXVEX * sizeof(int));
	memset(vis, 0, MAXVEX * sizeof(bool));
	dis[u] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q;
	Q.push(pair<int, int>(0, u));
	while (!Q.empty())
	{
		int x = Q.top().second;
		if (x == v) break;
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
				Q.push(pair<int, int>(dis[edge[i].v], edge[i].v));
			}
		}
	}
	delete[] vis;
}

void Graph::DijkstraFib(const int u, const int v)
{
	bool* vis = new bool[MAXVEX];
	memset(pre, 0, MAXVEX * sizeof(int));
	memset(dis, MAXDIS, MAXVEX * sizeof(int));
	memset(vis, 0, MAXVEX * sizeof(bool));
	dis[u] = 0;
	FibHeap<pair<int, int> >Q;
	Q.MakeHash(vexNum + 1);
	Q.Insert(pair<int, int>(0, u), u);
	while (!Q.Empty())
	{
		int x = Q.Minimum().second;
		if (x == v) break;
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
				if (Q.hash[edge[i].v] == nullptr)
				{
					Q.Insert(pair<int, int>(dis[x] + edge[i].dis, edge[i].v), edge[i].v);
				}
				else
				{
					Q.Update(edge[i].v, pair<int, int>(dis[x] + edge[i].dis, edge[i].v));
				}
				pre[edge[i].v] = x;
				dis[edge[i].v] = dis[x] + edge[i].dis;
			}
		}
	}
	delete[] vis;
}

const int Graph::PrintPath(const int u, const int v) const
{
	auto st = new int[MAXVEX];
	int top = 0, vv = v;
	while (u != vv)
	{
		st[++top] = vv;
		vv = pre[vv];
	}
	printf("PATH: %d", u);
	while (top)
	{
		printf(" -> %d", st[top--]);
	}
	putchar('\n');
	vv = st[1];
	delete[] st;
	return dis[vv];
}
