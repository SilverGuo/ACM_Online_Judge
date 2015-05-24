#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int main() {

	int AdjMat[110][110];
	int nb_case;
	int nb_maze, nb_exit, timer, nb_con, u, v, cost;

	scanf("%d", &nb_case);

	while (nb_case--) {
		scanf("%d\n%d\n%d\n%d\n", &nb_maze, &nb_exit, &timer, &nb_con);
		memset(AdjMat, 63, sizeof AdjMat);

		for (int i = 0; i < nb_con; i++) {
			scanf("%d %d %d", &u, &v, &cost);
			AdjMat[u][v] = cost;
		}

		for (int k = 1; k <= nb_maze; k++)
			for (int i = 1; i <= nb_maze; i++)
				for (int j = 1; j <= nb_maze; j++)
					AdjMat[i][j] = min(AdjMat[i][j], AdjMat[i][k] + AdjMat[k][j]);

		int nb_suc = 0;
		for (int i = 1; i <= nb_maze; i++)
			if (AdjMat[i][nb_exit] <= timer || (i == nb_exit))
				nb_suc++;

		printf("%d\n", nb_suc);
		if (nb_case)
			printf("\n");
	}

	return 0;
}
