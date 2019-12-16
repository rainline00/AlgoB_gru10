#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min(int a, int b, int c) {
	if (a <= b && a <= c) return a;
	else if (b <= a && b <= c) return b;
	else return c;
}

int levenshtein(char* ns, char* ms)
{
	int nlen = strlen(ns) + 1;
	int mlen = strlen(ms) + 1;
	int d[2][mlen];
	int i, j, cost = 0;

	for (j = 0; j < mlen; j++) {
		d[0][j] = j;
		//printf("%d ", d[0][j]);
	}
	printf("\n");

	for (i = 1; i < nlen; i++) {
		d[i % 2][0] = i;
		for (j = 1; j < mlen; j++) {
			cost = ns[i - 1] == ms[j - 1] ? 0 : 1;
			d[i % 2][j] = min(d[(i + 1) % 2][j] + 1, d[i % 2][j - 1] + 1, d[(i + 1) % 2][j - 1] + cost);
		}
		//for (j = 0; j < mlen; j++) printf("%d ", d[i % 2][j]);
		//printf("\n");
		printf("%d\n", i);
	}

	return d[(i + 1) % 2][j - 1];
}

int main(int argc, char** argv) {
	char answer[401000], origin[401000];
	FILE* fp_in = fopen(argv[1], "r");
	FILE* fp_or = fopen(argv[2], "r");

	fscanf(fp_in, "%s", answer);
	fscanf(fp_or, "%s", origin);

	fclose(fp_in);
	fclose(fp_or);

	printf("start\n");
	printf("distance:%d\n", levenshtein(answer, origin));
	printf("end\n");
}