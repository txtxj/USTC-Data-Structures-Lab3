#include <cstdlib>
#include <cstdio>

using namespace std;


static char buf[10000000];
static int output[200000000];
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
	freopen("info.bin", "wb", stdout);
	int cnt = 0;
	while (true)
	{
		output[cnt] = read();
		if (output[cnt] == EOF) break;
		output[cnt + 1] = read();
		output[cnt + 2] = read();
		cnt += 3;
	}
	fwrite(output, 1, cnt * sizeof(int), stdout);
	return 0;
}
