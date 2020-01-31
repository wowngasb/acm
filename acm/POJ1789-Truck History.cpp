#include<iostream>
#include<string>
using namespace std;

const int inf = 10;          //无穷大（两点间边权最大为7）
const int large = 2001;

int n;  //truck types
char str[large][8];
int dist[large][large] = { 0 };

/*Compute Weight*/

int weight(int i, int j)     //返回两个字符串中不同字符的个数（返回边权）
{
	int w = 0;
	for (int k = 0; k<7; k++)
		if (str[i][k] != str[j][k])
			w++;
	return w;
}

/*Prim Algorithm*/

int prim(void)
{
	int s = 1;       //源点（最初的源点为1）
	int m = 1;       //记录最小生成树的顶点数
	bool u[large]; //记录某顶点是否属于最小生成树
	int prim_w = 0;  //最小生成树的总权值
	int min_w;     //每个新源点到其它点的最短路
	int flag_point;
	int low_dis[large];  //各个源点到其它点的最短路

	memset(low_dis, inf, sizeof(low_dis));
	memset(u, false, sizeof(u));
	u[s] = true;

	while (1)
	{
		if (m == n)      //当最小生成树的顶点数等于原图的顶点数时，说明最小生成树查找完毕
			break;

		min_w = inf;
		for (int j = 2; j <= n; j++)
		{
			if (!u[j] && low_dis[j]>dist[s][j])
				low_dis[j] = dist[s][j];
			if (!u[j] && min_w>low_dis[j])
			{
				min_w = low_dis[j];
				flag_point = j;      //记录最小权边中不属于最小生成树的点j
			}
		}
		s = flag_point;       //顶点j与旧源点合并
		u[s] = true;          //j点并入最小生成树（相当于从图上删除j点，让新源点接替所有j点具备的特征）
		prim_w += min_w;      //当前最小生成树的总权值
		m++;
	}
	return prim_w;
}

int main(void)
{
	int i, j;

	while (cin >> n && n)
	{
		/*Input*/

		for (i = 1; i <= n; i++)
			cin >> str[i];

		/*Structure Maps*/

		for (i = 1; i <= n - 1; i++)
			for (j = i + 1; j <= n; j++)
				dist[i][j] = dist[j][i] = weight(i, j);

		/*Prim Algorithm & Output*/

		cout << "The highest possible quality is 1/" << prim() << '.' << endl;

	}
	return 0;
}