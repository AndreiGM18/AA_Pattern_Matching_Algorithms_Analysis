#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 1000001

static int nr_appearances;
static char out_path[13];
static int appearances[LEN];
  
// Preprocessing for strong good suffix rule
void preprocess_strong_suffix(int *shift, int *border_position, char *pat, int m)
{
	int i = m, j = m + 1;
	border_position[i] = j;
  
	while (i > 0)
	{
		/* If the character at position i - 1 does not match the one at j - 1,
		 * then continues searching to right of the pattern for border
		 */
		while (j <= m && pat[i - 1] != pat[j - 1])
		{
			/* Stops skipping the occurrences and shifts the pattern
			 * from i to j
			 */
			if (!shift[j])
				shift[j] = j - i;
  
			// Updates the position of next border 
			j = border_position[j];
		}

		// Border found, stores the  beginning position of border
		--i;
		--j;

		border_position[i] = j; 
	}
}
  
// Preprocessing for case 2
void preprocess_case2(int *shift, int *border_position, char *pat, int m)
{
	int i, j;
	j = border_position[0];
	for (i = 0; i <= m; ++i)
	{
		/* Sets the border position of the first character of the pattern
		 * to all indices in the array shift having shift[i] = 0
		 */ 
		if (!shift[i])
			shift[i] = j;
  
		/* Suffix is now shorter than border_position[0]
		 * j = the position of next widest border
		 */
		if (i == j)
			j = border_position[j];
	}
}
  
// The actual search algorithm
void search(char *pat, char *text)
{
	// s is the shift of the pattern with respect to text
	int s = 0, j;
	int m = strlen(pat) - 1;
	int n = strlen(text) - 1;
  
	int border_position[m + 1], shift[m + 1];
  
	// Initializing
	for (int i = 0; i < m + 1; ++i)
		shift[i] = 0;
	
	preprocess_strong_suffix(shift, border_position, pat, m);
	preprocess_case2(shift, border_position, pat, m);

	while (s <= n - m)
	{
		j = m - 1;
		
		// --j while the characters are matching
		while (j >= 0 && pat[j] == text[s + j])
			--j;
  
		// j becomes negative if the pattern is found
		if (j < 0) {
			appearances[nr_appearances++] = s;
 
			s += shift[0];
		} else
			// Shifts the pattern shift[j + 1] times
			s += shift[j + 1];
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