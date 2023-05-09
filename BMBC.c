#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1000001
#define ASCII_CHARS 256

static int nr_appearances;
static char out_path[13];
static int appearances[LEN];

// The preprocessing function for Boyer Moore (bad character)
void badcharpreprocess(char *str, int size, int badchar[ASCII_CHARS])
{
	int i;
 
	// Initializing
	for (i = 0; i < ASCII_CHARS; ++i)
		badchar[i] = -1;
 
	// Fill the actual value with the last occurrence of the character
	for (i = 0; i < size; ++i)
		badchar[(int) str[i]] = i;
}
 
// The actual search algorithm
void search(char *pat, char *txt)
{
	int m = strlen(pat) - 1;
	int n = strlen(txt) - 1;
 
	int badchar[ASCII_CHARS];

	badcharpreprocess(pat, m, badchar);
 
	int shift = 0;
	while (shift <= (n - m))
	{
		int j = m - 1;
 
		/* Keeps reducing the index of the pattern while characters of pattern
		 * and text are matching at the current shift
		 */
		while (j >= 0 && pat[j] == txt[shift + j])
			--j;
 
		/* If the pattern is present at the current shift, then index j will
		 * become negative
		 */
		if (j < 0)
		{
			appearances[nr_appearances++] = shift;
 
			/* Shifts the pattern so that the next character in text aligns
			 * with the last occurrence of it in pattern.
			 * shift + m must be less than n so that it does not go over the
			 * text's length
			 */
			shift += shift + m < n ? m - badchar[txt[shift + m]] : 1;
 
		}
 
		else
			/* Shifts the pattern so that the bad character in text aligns
			 * with the last occurrence of it in pattern.
			 * Only allows positive shifts, since negative shifts may happen
			 * if the last occurrence of the bad character in the is right of
			 * the current character
			 */
			shift += j - badchar[txt[shift + j]] > 1 ? j - badchar[txt[shift + j]] : 1;
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