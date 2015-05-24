#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<cmath>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include<set>

using namespace std;

struct Piece{ // represente piece
	int x, y;
	bool check(){
		if (x<8 && x >= 0 && y<8 && y >= 0)
			return true;
		return false;
	}
};

struct Node{ // each node store the information of four points
	Piece pos[4];
	int move;
}init, tar;

map<int, int>m; // map hash code position to kind 
map<int, int>::iterator it; 
int possible[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; // possible method of move

bool cmp(Piece p1, Piece p2); // compara funtion used by get_hash
int get_hash(Piece *cache);
bool bfs(int kind, Node u); // bfs

int main(){
	while (scanf("%d%d", &init.pos[0].x, &init.pos[0].y) != EOF){
		m.clear();
		for (int i = 1; i<4; i++)
			scanf("%d%d", &init.pos[i].x, &init.pos[i].y);
		for (int i = 0; i<4; i++)
			scanf("%d%d", &tar.pos[i].x, &tar.pos[i].y);
		for (int i = 0; i<4; i++){
			init.pos[i].x--; init.pos[i].y--;
			tar.pos[i].x--; tar.pos[i].y--;
		}
		bfs(1, init); // store the possibilities get by init within 4 moves
		printf("%s\n", bfs(2, tar) ? "YES" : "NO");
	}
	return 0;
}

bool cmp(Piece p1, Piece p2){
	return p1.x != p2.x ? p1.x<p2.x : p1.y<p2.y;
}

int get_hash(Piece *cache){
	int hashcode = 0;
	sort(cache, cache + 4, cmp);
	for (int i = 0; i<4; i++){
		hashcode |= (cache[i].x << (6 * i));
		hashcode |= (cache[i].y << (6 * i + 3));
	}
	return hashcode;
}

bool bfs(int kind, Node u){
	Node v;
	queue<Node> que;
	u.move = 0;
	if (kind == 2){ // if can directly match an existance position
		it = m.find(get_hash(u.pos));
		if (it != m.end())
			return true;
	}
	m[get_hash(u.pos)] = kind; // add u into map
	que.push(u);
	while (!que.empty()){
		u = que.front(); // get u
		que.pop(); // delete u in que
		if (u.move >= 4)
			continue;
		for (int i = 0; i<4; i++){ // four method de move
			for (int j = 0; j<4; j++){ // four pieces
				v = u; v.move++;
				v.pos[j].x += possible[i][0];
				v.pos[j].y += possible[i][1];
				int k;
				if (!v.pos[j].check())
					continue;
				for (k = 0; k<4; k++) // judge if it need to jump over a piece
					if (k != j&&v.pos[k].x == v.pos[j].x&&v.pos[k].y == v.pos[j].y)
						break;
				if (k == 4){
					int HASH = get_hash(v.pos);
					it = m.find(HASH);
					if (kind == 1){
						if (it == m.end()){
							m[HASH] = 1;
							que.push(v);
						}
					}
					else{
						if (it == m.end()){
							m[HASH] = 2;
							que.push(v);
						}
						else if ((*it).second == 1) // new position v already produced by kind 1
							return true;
					}
				}
				else{
					v.pos[j].x += possible[i][0];
					v.pos[j].y += possible[i][1];
					if (!v.pos[j].check())
						continue;
					for (k = 0; k<4; k++)
						if (k != j&&v.pos[k].x == v.pos[j].x&&v.pos[k].y == v.pos[j].y)
							break;
					if (k == 4){ // cannot jump over two pieces
						int HASH = get_hash(v.pos);
						it = m.find(HASH);
						if (kind == 1){
							if (it == m.end()){
								m[HASH] = 1;
								que.push(v);
							}
						}
						else{
							if (it == m.end()){
								m[HASH] = 2;
								que.push(v);
							}
							else if ((*it).second == 1)
								return true;
						}
					}
				}
			}
		}
	}
	return false;
}