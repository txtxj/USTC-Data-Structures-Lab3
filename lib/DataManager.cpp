#define MAXVEX 30000000

#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

// 快速读入
static char buf[10000000];			// 输入缓冲区
static int output[200000000];		// 输出缓冲区
static char *st = buf, *ed = buf;

// 读取单个字符
inline char getc(void)
{
	return st == ed && (ed = (st = buf) + fread(buf, 1, 10000000, stdin), st == ed) ? EOF : *st++;
}

// 读取非负整数
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

vector<pair<int, int> > v[MAXVEX];

// argv[1] info.txt
// argv[2] info.bin
int main(int argc, char** argv)
{
	freopen(argv[1], "r", stdin);
	freopen(argv[2], "wb", stdout);
	int cnt = 0;
	int a = 0, b = 0, c = 0;
	int maxv = 0;
	while (true)
	{
		a = read();
		if (a == EOF) break;
		b = read();
		c = read();
		if (a > maxv) maxv = a;
		if (b > maxv) maxv = b;
		v[a].push_back(pair<int, int>(b, c));
	}
	// 对于每一个顶点，
	// 不记录其顶点编号，只记录其出度 d_i
	// 其后为 2 * d_i 个整数，表示 d_i 条边
	// 共计需要记录 |V| 个出度、 |E| 个边，每条边两个数据
	// 总数据量为严格的 |V| + 2 * |E| 
	for (int i = 0; i <= maxv; i++)
	{
		output[cnt++] = v[i].size();
		for (auto u : v[i])
		{
			output[cnt++] = u.first;
			output[cnt++] = u.second;
		}
	}
	fwrite(output, 1, cnt * sizeof(int), stdout);
	return 0;
}
