#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	FILE *input;
	char *pipeString;
	pipeString = (char *) malloc (500 * sizeof (char));

	int nTimeframes = 0;

	if (strstr (argv[1], ".xz")) {
		snprintf (pipeString, 500, "xzcat %s", argv[1]);
		input = popen (pipeString, "r"); }
	else
		input = fopen (pipeString, "r");

	char lineString[1000];

	while (fgets (lineString, 1000, input))
	{
		if (strstr (lineString, "ITEM: TIMESTEP"))
		{
			nTimeframes++;
			printf("Counting timeframes... %d                \r", nTimeframes);
			fflush (stdout);
		}
	}

	printf("Number of timeframes in the input file: %d\n", nTimeframes);

	fclose (input);
	return 0;
}