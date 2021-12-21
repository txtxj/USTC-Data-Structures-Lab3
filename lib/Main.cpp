#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Graph.cpp"

using namespace std;

Graph G(10000000);

static int buf[200000000];

int p = 0, cnt = 0;

int read()
{
	if (p >= cnt) return -1;
	else return buf[p++];
}

int main(int argc, char** argv)
{
	freopen(argv[1], "rb", stdin);
	freopen(argv[2], "w", stdout);
	cnt = fread(buf, sizeof(int), 200000000, stdin);
	int u, v, m = 0, e, b, c;

	long st = clock();

	while (true)
	{
		e = read();
		if (e == -1) break;
		for (int i = 0; i < e; i++)
		{
			b = read();
			c = read();
			G.AddEdge(m, b, c);
		}
		m++;
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