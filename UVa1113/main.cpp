#include <cstdio>
#include <string.h>
#include <map>

#define MAXCHAR 2 
#define MAXCODE (2048)
#define MAXNODE (1048576)

using namespace std;

class Trie {
public:
	struct Node {
		Node *next[MAXCHAR];
		int cnt;
		void init() {
			cnt = 0;
			memset(next, 0, sizeof(next));
		}
	} nodes[MAXNODE];

	Node *root;
	int size;

	Node* getNode() {
		Node *p = &nodes[size++];
		p->init();
		return p;
	}
	void init() {
		size = 0;
		root = getNode();
	}
	inline int toIndex(char c) {
		return c == '.';
	}

	void insert(const char str[], int w) {
		Node *p = root;
		for (int i = 0, idx; str[i]; i++) {
			idx = toIndex(str[i]);
			if (p->next[idx] == NULL)
				p->next[idx] = getNode();
			p = p->next[idx];
		}
		p->cnt += w;
	}
	int find(const char str[]) {
		Node *p = root;
		for (int i = 0, idx; str[i]; i++) {
			idx = toIndex(str[i]);
			if (p->next[idx] == NULL)
				p->next[idx] = getNode();
			p = p->next[idx];
		}
		return p->cnt;
	}
} tree;

int main(){
	char morcode[MAXCODE], word[MAXCODE], cache[MAXCODE];
	string morse[] = {
		".-", "-...", "-.-.", "-..",
		".", "..-.", "--.", "....",
		"..", ".---", "-.-", ".-..",
		"--", "-.", "---", ".--.",
		"--.-", ".-.", "...", "-",
		"..-", "...-", ".--", "-..-",
		"-.--", "--.." };
	int nb_case, nb_word;
	scanf("%d", &nb_case);
	while (nb_case--) {
		tree.init();

		scanf("%s", morcode);
		scanf("%d", &nb_word);
		for (int i = 0; i < nb_word; i++) {
			scanf("%s", word);
			int m = 0;
			for (int j = 0; word[j]; j++)
				for (int k = 0; morse[word[j] - 'A'][k]; k++)
					cache[m++] = morse[word[j] - 'A'][k];
			cache[m] = '\0';
			tree.insert(cache, 1);
		}

		int length = (int)strlen(morcode);
		int nb_comb[MAXCODE] = {};
		nb_comb[0] = 1; // 
		for (int i = 0; i < length; i++) {
			Trie::Node *p = tree.root;
			for (int j = i; j < length; j++) {
				int u = tree.toIndex(morcode[j]);
				if (p->next[u] == NULL)
					break;
				p = p->next[u];
				nb_comb[j + 1] += nb_comb[i] * p->cnt;
			}
		}

		printf("%d\n", nb_comb[length]);
		if (nb_case)
			puts("");
	}
	return 0;
}
