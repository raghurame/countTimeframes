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

	int nTimeframes = 0, nLines = 0, nAtoms = 0, nLinesPerTimeframe, nPerfectTimeframe = 0, nImperfectTimeframe = 0;
	int isAtomLine = 0;

	if (strstr (argv[1], ".xz")) {
		snprintf (pipeString, 500, "xzcat %s", argv[1]);
		input = popen (pipeString, "r"); }
	else
		input = fopen (pipeString, "r");

	char lineString[1000];

	while (fgets (lineString, 1000, input))
	{
		nLines++;
		nLinesPerTimeframe++;

		if ((isAtomLine == 1) && (nAtoms == 0)) {
			sscanf (lineString, "%d\n", &nAtoms);
			isAtomLine = 0; }

		if (strstr (lineString, "ITEM: TIMESTEP")) {
			nTimeframes++;
			printf("Counting timeframes... %d                \r", nTimeframes);
			fflush (stdout);

			if ((nLinesPerTimeframe == (nAtoms + 9)) && (nAtoms > 0) && (nLinesPerTimeframe > 10))
				nPerfectTimeframe++;

			else if ((nLinesPerTimeframe != (nAtoms + 9)) && (nAtoms > 0) && (nLinesPerTimeframe > 10))
				nImperfectTimeframe++;

			nLinesPerTimeframe = 0; }

		if (strstr (lineString, "ITEM: NUMBER OF ATOMS"))
			isAtomLine = 1;
	}

	printf("Number of timeframes in the input file: %d\n", nTimeframes);
	printf("Total number of lines: %d\nNumber of timeframes calculated from total number of lines: %d (%d)\n", nLines, nLines / (nAtoms + 9), nLines % (nAtoms + 9));
	printf("Perfect timeframes: %d\nImperfect timeframes: %d\n\n", nPerfectTimeframe, nImperfectTimeframe);

	fclose (input);
	return 0;
}