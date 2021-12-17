#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Graph.cpp"

using namespace std;

Graph G(10000000);

int main()
{
	freopen("infoS.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int u, v, d;
	int m = 0;

	long st = clock();
	while (~scanf("%d %d %d", &u, &v, &d))
	{
		m = m < u ? u : m;
		m = m < v ? v : m;
		G.AddEdge(u, v, d);
	}
	G.SetVexNum(m);
	freopen("inputS.txt", "r", stdin);
	scanf("%d %d", &u, &v);
	printf("Read Time: %ldms\n", clock() - st);

	if (G.GetVexNum() <= 100000)
	{
		st = clock();
		G.Dijkstra(u);
		printf("Dijkstra Time: %ldms\n", clock() - st);
	}

	st = clock();
	G.DijkstraHeap(u);
	printf("DijkstraHeap Time: %ldms\n", clock() - st);

	st = clock();
	G.DijkstraFib(u);
	printf("DijkstraFib Time: %ldms\n", clock() - st);

	printf("Distance: %d", G.PrintPath(u, v));
	return 0;
}