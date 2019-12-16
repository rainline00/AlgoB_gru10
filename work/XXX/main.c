#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	int a, b, c, d, length;
} text;

char data[400010],answer[400010];
char str[40500][120];
int dlength;
text* s;
int limit = 6;

int charcmp(const void* l, const void* r) {
	char* lc = (char*)l;
	char* rc = (char*)r;
	return (strlen(lc) < strlen(rc)) ? -1 : 1;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int bm(int n,int start) {
	int i = start + s[n].length - 1, p = 0;
	while (i < dlength) {
		p = s[n].length - 1;
		while (p >= 0 && i < dlength) {
			if (data[i] == 'x' || data[i] == str[n][p]) {
				i--;
				p--;
			}
			else break;
		}
		if (p < 0) return i + 1;

		int shift;
		if (data[i] == 'a') shift = s[n].a;
		else if (data[i] == 'b') shift = s[n].b;
		else if (data[i] == 'c') shift = s[n].c;
		else if (data[i] == 'd') shift = s[n].d;

		i += max(shift, s[n].length - p);
	}
	return -1;
}

int main(int argc, char** argv) {

	assert(argc == 3);
	FILE* fp_in = fopen(argv[1], "r");
	assert(fp_in != NULL);
	FILE* fp_out = fopen(argv[2], "w");
	assert(fp_out != NULL);

	clock_t begin = clock();

	//input T '
	fscanf(fp_in, "%s", data);
	dlength = strlen(data);

	//input S
	int i = 0, j, k;
	while (fscanf(fp_in, "%s", str[i++]) != EOF) {}

	int num = i - 1;

	//S -> quick sort
	qsort(str, num, sizeof(str[0]), charcmp);

	//text type construction
	s = (text*)malloc((num+1) * sizeof(text));

	//initiate s
	int count;
	for (i = 0; i < num; i++) {
		count = 0;
		s[i].length = strlen(str[i]);
		s[i].a = s[i].b = s[i].c = s[i].d = s[i].length;

		for (k = s[i].length - 1; k >= 0; k--) {
			if (s[i].a == s[i].length && str[i][k] == 'a') {
				s[i].a = s[i].length - k - 1;
				if (s[i].a == 0) s[i].a = 1;
				count++;
			}
			else if (s[i].b == s[i].length && str[i][k] == 'b') {
				s[i].b = s[i].length - k - 1;
				if (s[i].b == 0) s[i].b = 1;
				count++;
			}
			else if (s[i].c == s[i].length && str[i][k] == 'c') {
				s[i].c = s[i].length - k - 1;
				if (s[i].c == 0) s[i].c = 1;
				count++;
			}
			else if (s[i].d == s[i].length && str[i][k] == 'd') {
				s[i].d = s[i].length - k - 1;
				if (s[i].d == 0) s[i].d = 1;
				count++;
			}
			if (count == 4) break;
		}
		//fprintf(fp_out, "%d %d %d %d %d %s\n", s[i].length, s[i].a, s[i].b, s[i].c, s[i].d, str[i]);
	}
	//fprintf(fp_out, "%d %d\n", dlength, num);

	strcpy(answer, "");

	//BM
	int p, start = 0;
	for (i = 0; i < num; i++) {
		printf("%d\n", i);
		if (s[i].length < limit) continue;
		while (start + s[i].length - 1 < dlength) {
			p = bm(i, start);
			if (p != -1) {
				for (j = 0; j < s[i].length; j++) answer[p + j] = str[i][j];
				start = p + 1;
			}
			else {
				break;
			}
		}
		start = 0;
	}

	printf("-----write-----\n");

	for (i = 0; i < dlength; i++) {
		fprintf(fp_out, "%c", answer[i]);
	}
	fprintf(fp_out, "\n");

	clock_t end = clock();
	printf("%fsec.\n", (double)(end - begin) / CLOCKS_PER_SEC);

	return 0;
}
