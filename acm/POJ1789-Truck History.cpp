#include<iostream>
#include<string>
using namespace std;

const int DISTANCE_INF = 10;          //无穷大 字母最大长度为7  随便大于7的数字都可以
const int TRUCK_TYPES_MAX = 2001;    // 最大允许的字符串数量  需要加1 因为为了方便 索引是从第一个开始放的

char str[TRUCK_TYPES_MAX][8];  // TRUCK_TYPES_MAX 个字符串 用来存放 输入字符串
int dist[TRUCK_TYPES_MAX][TRUCK_TYPES_MAX] = { 0 };  // TRUCK_TYPES_MAX * TRUCK_TYPES_MAX 的矩阵 用来存放两字符串的距离 

													 // 比较 left 和 right 中不同的字母个数  长度都为 len
int weight(char left[], char  right[], unsigned int len)
{
	int w = 0;
	for (int k = 0; k < len; k++) {
		if (left[k] != right[k]) {
			w++;
		}
	}
	return w;
}

/*
算法描述编辑
1).输入：一个加权连通图，其中顶点集合为V，边集合为E；
2).初始化：Vnew = {x}，其中x为集合V中的任一节点（起始点），Enew = {},为空；
3).重复下列操作，直到Vnew = V：
a.在集合E中选取权值最小的边<u, v>，其中u为集合Vnew中的元素，而v不在Vnew集合当中，并且v∈V（如果存在有多条满足前述条件即具有相同权值的边，则可任意选取其中之一）；
b.将v加入集合Vnew中，将<u, v>边加入集合Enew中；
4).输出：使用集合Vnew和Enew来描述所得到的最小生成树。
*/

int prim(int types)
{
	int prim_w = 0;  //最小生成树的总权值

	bool u[TRUCK_TYPES_MAX]; //记录某顶点是否属于最小生成树
	int low_dis[TRUCK_TYPES_MAX];  //各个源点到其它点的最短路

								   // 需要用 memset 来初始化
	memset(low_dis, DISTANCE_INF, sizeof(low_dis));
	memset(u, false, sizeof(u));

	// 2).初始化：Vnew = {x}，其中x为集合V中的任一节点（起始点），Enew = {},为空；
	int s = 1;
	u[1] = true;  // 从第一个点开始
	int m = 1;       //最小生成树已经完成的点数

					 // 3).重复下列操作，直到Vnew = V：
	while (m < types)
	{
		int min_w = DISTANCE_INF;   // 初始距离为 DISTANCE_INF
		int flag_point;  // 最小距离的点

						 // a.在集合E中选取权值最小的边<u, v>，其中u为集合Vnew中的元素，而v不在Vnew集合当中，并且v∈V（如果存在有多条满足前述条件即具有相同权值的边，则可任意选取其中之一）；
		for (int j = 2; j <= types; j++)
		{
			if (!u[j]) {  // 需要没有处理过的点
				if (low_dis[j] > dist[s][j]) {
					low_dis[j] = dist[s][j];
				}

				if (min_w > low_dis[j])  // 一定会找到一个点的  因为初始值为 DISTANCE_INF
				{
					min_w = low_dis[j];
					flag_point = j;      // 找到的最小边的另一点
				}
			}
		}

		// b.将v加入集合Vnew中，将<u, v>边加入集合Enew中；
		u[flag_point] = true;
		prim_w += min_w;      //当前最小生成树的总权值
		s = flag_point;  // 下一次  从这个点再开始找下一个点
		m++;
	}
	return prim_w;
}

int main(void)
{
	int truck_types = 0;  //输入字符串的个数

	while (cin >> truck_types && truck_types)
	{
		for (int i = 1; i <= truck_types; i++) {  // 注意 是从索引 1 开始的
			cin >> str[i];
		}

		for (int i = 1; i <= truck_types - 1; i++) {  // 注意 是从索引 1 开始的
			for (int j = i + 1; j <= truck_types; j++) {
				dist[i][j] = dist[j][i] = weight(str[i], str[j], 7);  // 计算两两之间距离  放入矩阵
			}
		}

		cout << "The highest possible quality is 1/" << prim(truck_types) << '.' << endl;

	}
	return 0;
}