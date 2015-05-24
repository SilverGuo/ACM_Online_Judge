#include <vector>
#include <cstdio>

using namespace std;

int main(){
	int nb_case;

	scanf("%d", &nb_case);

	while (nb_case--){
		vector<int> rule[110];
		bool ready[110];
		int nb_task;
		int nb_rule;
		int task, nb_need, cache_task;
		
		scanf("%d", &nb_task);
		scanf("%d", &nb_rule);

		for (int i = 0; i < nb_rule; i++)
		{
			scanf("%d", &task);
			scanf("%d", &nb_need);
			while (nb_need--)
			{
				scanf("%d", &cache_task);
				rule[task].push_back(cache_task);
			}
		}

		for (int i = 1; i <= nb_task; i++)
			ready[i] = false;
		
		for (int k = 1; k <= nb_task; k++)
		{
			for (int i = 1; i <= nb_task; i++)
			{
				int ct = 0;
				if (ready[i])continue;
				for (int j = 0; j < int(rule[i].size()); j++)
				{
					if (!ready[rule[i][j]])
					{
						ct++;
					}
				}
				if (ct == 0)
				{
					ready[i] = true;
					printf("%d", i);
					if (k != nb_task)
						printf(" ");
					break;
				}
			}
		}
		printf("\n");
		if (nb_case)
			printf("\n");
	}
	return 0;
}

