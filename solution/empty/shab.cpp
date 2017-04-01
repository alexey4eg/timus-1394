#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <algorithm>
#include <math.h>

using namespace std;

#define maxn 110
#define maxm 11

int ships[maxn];
int rows[maxm];
int n, m;

int shipRow[maxn];


void readInput() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%d", &ships[i]);
	for (int i = 0; i < m; i++)
		scanf("%d", &rows[i]);
}

bool fullSearch(int cur) {
	if (cur == n)
		return true;
	//check for exact match
	for(int i = 0; i<m; i++)
		if (rows[i] == ships[cur]) {
			rows[i] = 0;
			shipRow[cur] = i;
			if (fullSearch(cur + 1))
				return true;
			rows[i] = ships[cur];
			return false;
		}
	int bestFit = -1;
	//check for best fit
	for(int i = 0; i<m; i++)
		if (rows[i] > ships[cur]) {
			if (bestFit == -1 || rows[i] - ships[cur] > rows[bestFit] - ships[cur]) {
				bestFit = i;
			}
		}
	if (bestFit == -1)
		return false;

	shipRow[cur] = bestFit;
	rows[bestFit] -= ships[cur];
	if (fullSearch(cur + 1))
		return true;
	rows[bestFit] += ships[cur];

	//now just full search
	for (int i = 0; i<m; i++)
		if (rows[i] > ships[cur]) {
			shipRow[cur] = i;
			rows[i] -= ships[cur];
			if (fullSearch(cur + 1))
				return true;
			rows[i] += ships[cur];
		}

	return false;
}

void reverseSort() {
	sort(ships, ships + n);
	for (int i = 0; i < n / 2; i++)
		swap(ships[i], ships[n - i - 1]);
}

void solve() {
	reverseSort();
	fullSearch(0);
}

void output() {
	int cnt[maxm];
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < n; i++)
		cnt[shipRow[i]]++;
	for (int i = 0; i < m; i++) {
		printf("%d\n", cnt[i]);
		for (int j = 0; j < n; j++)
			if (shipRow[j] == i)
				printf("%d ", ships[j]);
		printf("\n");
	}
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	readInput();
	solve();
	output();
	return 0;
}