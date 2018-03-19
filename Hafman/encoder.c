#include "header.h"

void count_sym(char *syms, short elems);
void processing(FILE *in);
int seearch_max(char *abc);

int abc[256] = { 0 };

typedef struct Tree_st
{
	struct Tree_st *reight;
	struct Tree_st *left;
	char value;
	int count;
}Tree;

void processing(FILE *in)
{
	unsigned char syms[3];
	short red_el = 0;

	do
	{
		red_el = (short)fread(syms, sizeof(char), 1, in);
		count_sym(syms, red_el);
	} while (red_el == 3);
}

void count_sym(unsigned char *syms, short elems)
{
	short i = 0;
	for (i; i < elems; i++)
		abc[syms[i]] ++;
}

void encoder(FILE *in, FILE *out)
{
	fseek(in, 2, SEEK_CUR);

	processing(in);
	
}