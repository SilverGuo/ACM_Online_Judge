#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

#define MAXTREE 500

using namespace std;

vector<int> graph[MAXTREE];
int mark[MAXTREE];

int main(){
	int nb_case;
	scanf("%d", &nb_case);
	int k = nb_case;

	while (nb_case--){
		int nb_tree, nb_path;
		scanf("%d %d", &nb_tree, &nb_path);

		for (int i = 0; i < nb_tree; i++){
			graph[i].clear();
		}

		for (int i = 0; i < nb_path; i++){
			int a, b;
			scanf("%d %d", &a, &b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}

		int length = 20000;

		for (int i = 0; i < nb_tree; i++){
			queue<int> q;
			int tree;

			for (int j = 0; j < nb_tree; j++){
				mark[j] = -1;
			}

			mark[i] = 0;
			q.push(i);

			while (!q.empty()){
				tree = q.front();
				q.pop();

				for (int j = 0; j < (int)graph[tree].size(); j++){
					if (mark[graph[tree][j]] != -1){
						if (mark[tree] <= mark[graph[tree][j]])
							length = min(length, mark[graph[tree][j]] + mark[tree] + 1);
					}
					else {
						mark[graph[tree][j]] = mark[tree] + 1;
						q.push(graph[tree][j]);
					}
				}
			}
		}

		if (length == 20000){
			printf("Case %d: impossible\n", k - nb_case);
		}
		else{
			printf("Case %d: %d\n", k - nb_case, length);
		}
		
	}
	return 0;
}