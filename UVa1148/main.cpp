#include <cstdio>
#include <vector>
#include <queue>

#define MAXPOINT 100000

using namespace std;
vector<int> graph[MAXPOINT];

int find(int start, int end, vector<int> graph[MAXPOINT]){
	queue<int> q;
	int distance[MAXPOINT];
	for (int i = 0; i < MAXPOINT; i++){
		distance[i] = 0;
	}

	q.push(start);
	int point;

	while (!q.empty()){
		point = q.front();
		q.pop();
		
		for (int i = 0; i < graph[point].size(); i++){
			if (distance[graph[point][i]] == 0){
				distance[graph[point][i]] = distance[point] + 1;
				q.push(graph[point][i]);
			}
		}
		if (distance[end] > 0){
			return distance[end] - 1;
		}
	}
	return -1;
}

int main(){
	int nb_case;
	scanf("%d", &nb_case);

	while (nb_case--){
		int nb_point;
		scanf("%d", &nb_point);

		for (int i = 0; i < nb_point; i++){
			int point, nb_adj, adj;
			scanf("%d %d", &point, &nb_adj);
			graph[point].clear();
			for (int j = 0; j < nb_adj; j++){
				scanf("%d", &adj);
				graph[point].push_back(adj);
			}
		}

		int start, end;
		scanf("%d %d", &start, &end);

		printf("%d %d %d\n", start, end, find(start, end, graph));

		if (nb_case)
			printf("\n");
	}
	return 0;
}