#include "header.h"

int verification(FILE *in);

int main(int argc, char *argv[])
{
	FILE *in, *out;
	char c;

	if (argc < 2) return 0;

	in = fopen(argv[1], "rb");
	if(verification(in)) return 0;

	out = fopen(argv[2], "w+b");

	c = fgetc(in);

	if (c == 'c') encoder(in, out);
	if (c == 'd') decoder(in, out);

	fclose(in);
	fclose(out);

	return 0;
}

int verification(FILE *in)
{
	if (in == NULL)
	{
		printf("%s", "Error: file not found");
		fclose(in);
		return 1;
	}
	return 0;
}