#include<cstdio>
#include<string>
#include<vector>
#include<map>

using namespace std;

int main(){

	map<string, int> Haab;

	Haab["pop"] = 0;
	Haab["no"] = 1;
	Haab["zip"] = 2;
	Haab["zotz"] = 3;
	Haab["tzec"] = 4;
	Haab["xul"] = 5;
	Haab["yoxkin"] = 6;
	Haab["mol"] = 7;
	Haab["chen"] = 8;
	Haab["yax"] = 9;
	Haab["zac"] = 10;
	Haab["ceh"] = 11;
	Haab["mac"] = 12;
	Haab["kankin"] = 13;
	Haab["muan"] = 14;
	Haab["pax"] = 15;
	Haab["koyab"] = 16;
	Haab["cumhu"] = 17;
	Haab["uayet"] = 18;

	const char Tzolkin[][20] = {
		"imix", "ik", "akbal", "kan", "chicchan",
		"cimi", "manik", "lamat", "muluk", "ok",
		"chuen", "eb", "ben", "ix", "mem", "cib",
		"caban", "eznab", "canac", "ahau"
	};

	int nb_case, DD, YY;
	char s[30];
	
	int sum;

	scanf("%d", &nb_case);
	printf("%d\n", nb_case);

	for (int i = 0; i<nb_case; i++){
		scanf("%d. %s %d", &DD, s, &YY);

		sum = DD + Haab[s] * 20 + YY * 365;

		printf("%d %s %d\n", sum % 13 + 1, Tzolkin[sum % 20], sum / 260);
	}
}