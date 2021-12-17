#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Graph.cpp"

using namespace std;

Graph G(10000000);

static char buf[10000000];
static char *st = buf, *ed = buf;
inline char getc(void)
{
	return st == ed && (ed = (st = buf) + fread(buf, 1, 10000000, stdin), st == ed) ? EOF : *st++;
}
inline int read(void)
{
	int x = 0;
	char c = getc();
	while (c < '0' || c > '9')
	{
		if (c == EOF) return EOF;
		c = getc();
	}
	while (c >= '0' && c <= '9')
	{
		x = (x << 1) + (x << 3) + (c ^ 48);
		c = getc();
	}
	return x;
}

int main()
{
	freopen("info.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int u, v, d;
	int m = 0;

	long st = clock();
	while (true)
	{
		u = read();
		if (u == EOF) break;
		v = read();
		d = read();
		m = m < u ? u : m;
		m = m < v ? v : m;
		G.AddEdge(u, v, d);
	}
	G.SetVexNum(m);
	freopen("input.txt", "r", stdin);
	scanf("%d %d", &u, &v);
	printf("Read Time: %ldms\n", clock() - st);

	// if (G.GetVexNum() <= 100000)
	// {
	// 	st = clock();
	// 	G.Dijkstra(u);
	// 	printf("Dijkstra Time: %ldms\n", clock() - st);
	// }

	st = clock();
	G.DijkstraHeap(u);
	printf("DijkstraHeap Time: %ldms\n", clock() - st);

	st = clock();
	G.DijkstraFib(u);
	printf("DijkstraFib Time: %ldms\n", clock() - st);

	printf("Distance: %d", G.PrintPath(u, v));
	return 0;
}