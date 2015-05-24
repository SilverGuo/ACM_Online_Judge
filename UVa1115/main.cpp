#include <stdio.h> 
#include <math.h>
#include <assert.h>
#include <algorithm>

#define MAXB 1024

using namespace std;

int main() {
	int nb_case, nb_box;
	double level[MAXB], height[MAXB], width[MAXB], depth[MAXB], volume;
	scanf("%d", &nb_case);

	while (nb_case--) {
		scanf("%d", &nb_box);
		
		for (int i = 0; i < nb_box; i++)
			scanf("%lf %lf %lf %lf", &level[i], &height[i], &width[i], &depth[i]);
		scanf("%lf", &volume);

		double level_total = 0, reach = 0, middle;
		double sumV = 0;
		for (int i = 0; i < nb_box; i++) {
			sumV += height[i] * width[i] * depth[i];
			reach = max(reach, level[i] + height[i]);
		}

		if (sumV < volume) {
			puts("OVERFLOW");
			if (nb_case)	puts("");
			continue;
		}

		for (int iter = 0; iter < 100; iter++) {
			middle = (level_total + reach) / 2;
			sumV = 0;
			for (int i = 0; i < nb_box; i++) {
				if (middle < level[i])	continue;
				sumV += width[i] * depth[i] * min(height[i], middle - level[i]);
			}
			if (sumV > volume)
				reach = middle;
			else
				level_total = middle;
		}
		printf("%.2lf\n", level_total);
		if (nb_case)	puts("");
	}
	return 0;
}