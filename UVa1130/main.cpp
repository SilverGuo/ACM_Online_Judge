#include <cstdio>
#include <iostream>
#include <string>
#include <queue>

#define MAX 50

using namespace std;

int road[MAX][MAX];
int plan[MAX][MAX];
int mark[MAX][MAX];
queue<int> timeq[MAX][MAX];
int possible[5][2] = { { 0, 1 }, { 1, 0 }, { 0, 0 }, { -1, 0 }, { 0, -1 } };

//bool repeat(int x, int y, int n)
//{
//	if (mark[x][y] == -1){
//		mark[x][y] = time[x][y];
//		return false;
//	}
//
//	int told, tnew;
//	told = mark[x][y];
//	tnew = time[x][y];
//
//	if (told - tnew == 5120){
//		return true;
//	}
//
//	mark[x][y] = time[x][y];
//	return false;
//}

bool free(int xx, int yy, int x, int y){
	if (plan[x][y] == 0){
		if (road[x][y] == 0)return true;
		else return false;
	}

	int rec;
	rec = (timeq[xx][yy].front() + 1) % (plan[x][y] * 2);
	if (rec < plan[x][y]){
		if (road[x][y] == 0)return true;
		else return false;
	}

	if (road[x][y] == 0)return false;
	else return true;
}

bool addtime(int xx, int yy, int xn, int yn){
	if (timeq[xn][yn].empty()) return true;

	if (timeq[xn][yn].size() == 2) return false;

	if (timeq[xn][yn].front() == timeq[xx][yy].front() + 1) return false;

	return true;
}

bool find(int x, int y, int n){
	queue<int> q[2];
	
	q[0].push(x);
	q[1].push(y);
	timeq[x][y].push(0);
	int xx, yy;

	while (!q[0].empty()){
		xx = q[0].front();
		yy = q[1].front();
		q[0].pop();
		q[1].pop();

		if (xx == n - 1 && yy == n - 1){
			printf("%d\n", timeq[xx][yy].front());
			return true;
		}

		if (timeq[xx][yy].front() > 5120 * n * n){
			return false;
		}

		/*if (repeat(xx, yy, n)){
			continue;
		}*/

		for (int i = 0; i < 5; i++){
			int xn = xx + possible[i][0];
			int yn = yy + possible[i][1];
			if (xn >= 0 && xn < n && yn >= 0 && yn < n && free(xx, yy, xn, yn) && addtime(xx, yy, xn, yn)){
				q[0].push(xn);
				q[1].push(yn);
				timeq[xn][yn].push(timeq[xx][yy].front() + 1);
			}
			if (i == 4){
				timeq[xx][yy].pop();
			}
		}
	}
	return false;
}

int main(){
	int n;
	bool isfirst = true;

	while (scanf("%d\n", &n) != EOF){
		string linestr;
		int cache;
		for (int i = 0; i < n; i++){
			getline(cin, linestr);
			for (int j = 0; j < n; j++){
				if (linestr[j] == '.'){
					road[i][j] = 0;
				}
				else{
					road[i][j] = 1;
				}
			}
		}
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				scanf("%1d", &cache);
				plan[i][j] = cache;
				while(!timeq[i][j].empty()) timeq[i][j].pop();
				//mark[i][j] = -1;
			}
		}

		if (!isfirst) printf("\n");
		if (isfirst) isfirst = false;

		if (!find(0, 0, n)){
			printf("NO\n");
		}

	}
	return 0;
}