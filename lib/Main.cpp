#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Graph.cpp"

using namespace std;

Graph G(10000000);

static int buf[200000000];

int main(int argc, char** argv)
{
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "w", stdout);
	int cnt = fread(buf, sizeof(int), 200000000, stdin);
	int u, v, m = 0;

	long st = clock();
	for (int i = 0; i < cnt; i += 3)
	{
		m = m < buf[i] ? buf[i] : m;
		m = m < buf[i + 1] ? buf[i + 1] : m;
		G.AddEdge(buf[i], buf[i + 1], buf[i + 2]);
	}
	G.SetVexNum(m);
	freopen(argv[3], "r", stdin);
	scanf("%d %d", &u, &v);
	printf("Read Time: %ldms\n", clock() - st);

	if (G.GetVexNum() <= 100000)
	{
		st = clock();
		G.Dijkstra(u, v);
		printf("Dijkstra Time: %ldms\n", clock() - st);
	}

	st = clock();
	G.DijkstraHeap(u, v);
	printf("DijkstraHeap Time: %ldms\n", clock() - st);

	st = clock();
	G.DijkstraFib(u, v);
	printf("DijkstraFib Time: %ldms\n", clock() - st);

	printf("Distance: %d", G.PrintPath(u, v));
	return 0;
}