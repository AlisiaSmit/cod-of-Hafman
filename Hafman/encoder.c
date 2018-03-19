#include "header.h"

#define NOT_FOUND -1;

int abc[256] = { 0 };

typedef struct Queue_st
{
	struct Queue *next;
	struct Queue *prev;
}Queue;

typedef struct Tree_st
{
	struct Tree_st *reight;
	struct Tree_st *left;
	char value;
	int count;
}Tree;


void file_processing(FILE *in);
int search_min(int *abc);
void create_tree(Tree *head);
void create_queue(Queue *head, Queue *tail);
Queue* enque(Queue *tail, unsigned char sym);


void file_processing(FILE *in)
{
	unsigned char syms[3];
	short red_el = 0, i = 0;

	do
	{
		red_el = (short)fread(syms, sizeof(char), 1, in);
	
		for (i; i < red_el; i++)
			abc[syms[i]] ++;
		
		i = 0;
	} while (red_el == 3);
}

int search_min(int *abc)
{
	int i = 0;
	int min_i = NOT_FOUND;
	int min = 0;
	for (i; i < 256; i++)
	{
		if (abc[i] < min)
		{
			min = abc[i];
			min_i = i;
		}
	}

	if (min_i != -1)   // if (min_i != NOT_FOUND) doesn't work
		abc[min_i] = 0;
	return min_i;
}

Queue* enque(Queue *tail, unsigned char sym)
{

}

void create_queue(Queue *head, Queue *tail)
{
	int i = 0;
	while ((i = search_min(abc)) != -1) // with NOT_FOUND doesn't work
	{
	tail = enque(tail, (unsigned char)i);

	}
}

// where? What?
void create_tree(Tree *head)
{
	int value;
	value = search_min(abc);
}

void encoder(FILE *in, FILE *out)
{
	Queue *head_q = NULL, *tail = NULL;
	Tree *head_t = NULL;

	fseek(in, 2, SEEK_CUR);

	file_processing(in);
	create_queue(head_q, tail);
	create_tree(head_t);
}