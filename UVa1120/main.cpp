#include <cstdio>
#include <vector>

using namespace std;

int main(){
	int nb_case;
	int k;
	scanf("%d", &nb_case);
	vector<int> right;

	for (k = 0; k < nb_case; k++){
		int i, j;
		int total = 0;
		int nb_value = 0;
		int cache_coin = 0;
		scanf("%d %d", &total, &nb_value);

		vector<int> coins;
		scanf("%d", &cache_coin);
		coins.push_back(cache_coin);
		for (i = 1; i < nb_value; i++){
			scanf("%d", &cache_coin);
			coins.push_back(cache_coin + coins[i - 1]);
		}

		vector<bool> possible;
		possible.push_back(true);
		for (i = 1; i <= total; i++){
			possible.push_back(false);
		}

		for (i = 0; i < nb_value; i++){
			for (j = coins[i]; j <= total; j++){
				possible[j] = possible[j] | possible[j - coins[i]];
			}
		}

		if (possible[total]){
			right.push_back(1);
		} else{
			right.push_back(0);
		}

	}

	for (k = 0; k < nb_case - 1; k++){
		if (right[k] == 1){
			printf("YES\n\n");
		}
		else{
			printf("NO\n\n");
		}
	}
	if (right[nb_case - 1] == 1){
		printf("YES\n\n");
	}
	else{
		printf("NO\n\n");
	}
}
