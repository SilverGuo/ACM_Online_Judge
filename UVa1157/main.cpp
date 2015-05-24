#include <cstdio>
#include <stack>

#define MAX 400

using namespace std;

int mat[MAX][MAX];
stack<int> ord;
int out[MAX];
bool mark[MAX];
bool used[MAX];

bool exam(int row, int col){
	int k = col;
	while (k--){
		out[k] = ord.top();
		ord.pop();
	}
	for (int k = 0; k < col; k++){
		ord.push(out[k]);
	}

	for (int i = 0; i < row; i++){
		int cont = 0;
		for (int j = 0; j < col; j++){
			if (mat[i][out[j]] == 1){
				if (cont == 0){
					cont = 1;
				}
				if (cont == 2){
					return false;
				}
			}
			if (mat[i][out[j]] == 0){
				if (cont == 1){
					cont = 2;
				}
			}
		}
	}
	return true;
}

bool pred(int row, int col, int nord){
	int k = nord;
	while (k--){
		out[k] = ord.top();
		ord.pop();
	}
	for (int k = 0; k < nord; k++){
		ord.push(out[k]);
	}

	for (int i = 0; i < row; i++){
		for (int j = 0; j < col; j++){
			used[j] = false;
		}

		if ((mat[i][out[nord - 1]] == 0) && (mat[i][out[nord - 2]] == 1)){
			int left = 0;
			int right = 0;
			used[nord - 1] = true;
			for (int k = 0; k < nord - 1; k++){
				used[out[k]] = true;
				if (mat[i][out[k]] == 1){
					left = 1;
				}
			}
			for (int j = 0; j < col; j++){
				if ((!used[j])&&(mat[i][j] == 1)){
					right = 1;
				}
			}
			if ((left == 1) && (right == 1)){
				return false;
			}
		}
	}
	return true;
}

bool find(int next, int row, int col){
	ord.push(next);

	if ((ord.size() > 1)&&(!pred(row, col, ord.size()))){
		ord.pop();
		return false;
	}

	if (ord.size() == col){
		if (exam(row, col)){
			for (int i = 0; i < col; i++){
				printf("%d\n", out[i]);
			}
			ord.pop();
			return true;
		}
		ord.pop();
		return false;
	}

	for (int i = 1; i < col; i++){
		if (!mark[i]){
			mark[i] = true;
			if (find(i, row, col)){
				ord.pop();
				return true;
			}
			mark[i] = false;
		}
	}
	ord.pop();
	return false;
}

int main(){
	int nb_case;
	scanf("%d", &nb_case);

	while (nb_case--){
		int row, col;
		int cache;
		scanf("%d", &row);
		scanf("%d", &col);
		for (int i = 0; i < row; i++){
			for (int j = 0; j < col; j++){
				scanf("%1d", &cache);
				mat[i][j] = cache;
			}
		}
		for (int j = 0; j < col; j++){
			mark[j] = false;
		}
		mark[0] = true;

		find(0, row, col);
		if(nb_case)
			printf("\n");
	}
	return 0;
}