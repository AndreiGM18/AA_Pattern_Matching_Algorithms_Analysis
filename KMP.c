#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1000001

static int nr_appearances;
static char out_path[13];
static int appearances[LEN];

// Initializes LPS (longest prefix suffix)
void preprocessLPS(char *pat, int M, int *lps)
{
	int len = 0;
 
	lps[0] = 0;
 
	int i = 1;
	while (i < M) {
		if (pat[i] == pat[len]) {
			++len;

			lps[i] = len;

			++i;
		} else {
			if (len) {
				len = lps[len - 1];
 
			} else {
				lps[i] = 0;
				++i;
			}
		}
	}
}

// The actual search algorithm
void search(char *pat, char *txt)
{
	int M = strlen(pat) - 1;
	int N = strlen(txt) - 1;
 
	int lps[M];
 
	// Preprocesses the pattern (calculate lps[] array)
	preprocessLPS(pat, M, lps);
 
	int i = 0;
	int j = 0;
	while ((N - i) >= (M - j)) {
		if (pat[j] == txt[i]) {
			++j;
			++i;
		}
 
		if (j == M) {
			appearances[nr_appearances++] = i - j;

			j = lps[j - 1];
		} else if (i < N && pat[j] != txt[i]) {
			// Skips matching characters that match anyway
			if (j) {
				j = lps[j - 1];
			} else {
				++i;
			}
		}
	}
}
 
int main(int argc, char *argv[])
{
	char test_nr_str[3], in_path[13] = "in/test";
	strcpy(out_path, "out/test");

	strcat(in_path, argv[1]);
	strcat(in_path, ".in");

	strcat(out_path, argv[1]);
	strcat(out_path, ".out");

	FILE *in = fopen(in_path, "r");
	FILE *out = fopen(out_path, "w");

	char *pat = (char *)malloc(LEN * sizeof(char)); 
	char *txt = (char *)malloc(LEN * sizeof(char));
	fgets(pat, LEN, in);
	fgets(txt, LEN, in);

	fclose(in);

	search(pat, txt);

	fprintf(out, "%d\n", nr_appearances);
	for (int i = 0; i < nr_appearances; ++i)
		fprintf(out, "%d ", appearances[i]);

	fprintf(out, "\n");
	
	fclose(out);

	free(pat);
	free(txt);

	return 0;
}