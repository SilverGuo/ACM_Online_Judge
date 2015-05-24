#include <cstdio>
#include <vector>
#include <queue>

#define MAXITR 1005

using namespace std;

vector<int> graph[MAXITR];
int color[MAXITR];
int mark[MAXITR];

bool paint(int v, int c){
	color[v] = c;
	for (size_t i = 0; i<graph[v].size(); ++i) {
		if (color[graph[v][i]] == c) return false;
		if (color[graph[v][i]] == 0 && !paint(graph[v][i], -c)) return false;
	}
	return true;
}

bool dfs(int nb_itr){
	for (int i = 1; i <= nb_itr; i++) {
		if (color[i] == 0) {
			if (!paint(i, 1)) {
				printf("Impossible\n");
				return false;
			}
		}
	}
	return true;
}

int main(){
	int nb_itr, nb_str;

	while (scanf("%d %d", &nb_itr, &nb_str) != EOF){
		//bool possible = true;

		for (int i = 1; i <= nb_itr; i++){
			graph[i].clear();
			color[i] = 0;
			mark[i] = 0;
		}
		for (int i = 0; i < nb_str; i++){
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		/*for (int i = 1; i <= nb_itr; i++){
			if (color[i] == -1){
				for (int j = 0; j < (int)graph[i].size(); j++){
					if (color[graph[i][j]] != -1){
						color[i] = 1 - color[graph[i][j]];
						break;
					}
				}
				if (color[i] == -1){
					color[i] = 0; 
				}
			}
			for (int j = 0; j < (int)graph[i].size(); j++){
				if (color[graph[i][j]] == color[i]){
					possible = false;
				}
				else if (color[graph[i][j]] == -1){
					color[graph[i][j]] = 1 - color[i];
				}
			}
		}

		if (!possible){
			printf("Impossible\n");
			continue;
		}*/

		if (!dfs(nb_itr))
			continue;
		
		int nb_need = 0;

		for (int i = 1; i <= nb_itr; i++){
			if (mark[i] == 0){
				queue<int> q;
				int colorp = 0; 
				int colorn = 0;

				mark[i] = 1;
				q.push(i);
				if (color[i] == -1) colorn++;
				else colorp++;
				int itr;

				while (!q.empty()){
					itr = q.front();
					q.pop();

					for (int j = 0; j < (int)graph[itr].size(); j++){
						if (mark[graph[itr][j]] == 0){
							q.push(graph[itr][j]);
							mark[graph[itr][j]] = 1;
							if (color[graph[itr][j]] == -1) colorn++;
							else colorp++;
						}
					}
				}

				if (colorn > colorp){
					nb_need += colorp;
				}
				else nb_need += colorn;
			}
		}
		printf("%d\n", nb_need);
	}
	return 0;
}