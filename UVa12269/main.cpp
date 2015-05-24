#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
	int nbr, nbl;
	float width;
	scanf("%d %d %f", &nbr, &nbl, &width);
	int i;
	float incache;
	vector<int> output;
	int nb_judge = 0;

	while ((nbr != 0) || (nbl != 0) || (width != 0)){
		vector<float> centr;
		vector<float> centl;
		int right = 1;

		for (i = 0; i < nbr; i++) {
			scanf("%f", &incache);
			centr.push_back(incache);
		}
		for (i = 0; i < nbl; i++) {
			scanf("%f", &incache);
			centl.push_back(incache);
		}

		sort(centr.begin(), centr.end(), less<float>());
		sort(centl.begin(), centl.end(), less<float>());

		if ((centr[0] > width / 2) || ((75.0 - centr[nbr - 1]) > width / 2)){
			right = 0;
		}
		if ((centl[0] > width / 2) || ((100.0 - centl[nbl - 1]) > width / 2)){
			right = 0;
		}


		for (i = 0; i < nbr - 1; i++) {
			if (centr[i + 1] - centr[i] > width)
				right = 0;
		}
		for (i = 0; i < nbl - 1; i++) {
			if (centl[i + 1] - centl[i] > width)
				right = 0;
		}

		if (right == 1) {
			output.push_back(1);
		}
		else {
			output.push_back(0);
		}
		nb_judge++;

		scanf("%d%d%f", &nbr, &nbl, &width);
	}
	
	for (i = 0; i < nb_judge; i++){
		if (output[i] == 1){
			printf("YES\n");
		}
		else {
			printf("NO\n");
		}
	}
}