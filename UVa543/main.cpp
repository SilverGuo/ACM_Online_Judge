#include <cstdio>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>

using namespace std;

bool IsPrime(int x);

struct FactoryPrime {
	int num;
	int i;
	bool right;
};

int main(){
	int num;
	scanf("%d", &num);
	vector<struct FactoryPrime> output;
	int i;

	while (num != 0){
		int right = 0;

		for (i = 3; i < (num / 2) + 1; i++){
			if (IsPrime(i)){
				if (IsPrime(num - i)){
					right = 1;
					break;
				}
			}
		}

		if (right == 1){
			struct FactoryPrime cache;
			cache.num = num;
			cache.i = i;
			cache.right = true;
			output.push_back(cache);
		}
		else{
			struct FactoryPrime cache;
			cache.num = num;
			cache.i = 0;
			cache.right = false;
			output.push_back(cache);
		}

		scanf("%d", &num);
	}

	vector<struct FactoryPrime>::iterator iter = output.begin();
	for (iter; iter != output.end(); ++iter){
		if (iter->right){
			num = iter->num;
			int a = iter->i;
			int b = num - a;
			printf("%d = %d + %d\n", num, a, b);
		}
		else{
			printf("Goldbach\'s conjecture is wrong.");
		}
	}
}

bool IsPrime(int x){
	for (int i = 2; i <= (int)sqrt(x); i++){
		if ((x % i) == 0)
			return false;
	}
	return true;
}