#include "header.h"
#include "structs.h"

#define NOT_FOUND -1

int abc[256] = { 0 };

prio_q *insertElem(prio_q * head, tree *elem);
void file_processing(FILE *in);
int search_max(int *abc);

prio_q *insertElem(prio_q * head, tree *elem)
{
	prio_q *new_elem = calloc(sizeof(prio_q));
	new_elem->elem = elem;
	new_elem->next = NULL;
	if (!head)	return new_elem;
	if (new_elem->elem->count <= head->elem->count)
	{
		new_elem->next = head;
		return new_elem;
	}
	prio_q *tmp = head;
	while (!(tmp->next))
	{
		if (new_elem->elem->count <= tmp->next->elem->count)
		{
			new_elem->next = tmp->next;
			tmp->next = new_elem;
			return head;
		}
		tmp = tmp->next;
	}
	tmp->next = new_elem;
	return head;
}

void file_processing(FILE *in)
{
	unsigned char syms[3];
	short red_el = 0, i = 0;

	do
	{
		red_el = (short)fread(syms, sizeof(char), 3, in);
	
		for (i; i < red_el; i++)
			abc[syms[i]] ++;
		
		i = 0;
	} while (red_el == 3);
}

int search_max(int *abc)
{
	int i = 0;
	int max_i = NOT_FOUND;
	int max = 0;
	for (i; i < 256; i++)
	{
		if (abc[i] > max)
		{
			max = abc[i];
			max_i = i;
		}
	}

	return max_i;
}


tree *build_HT(prio_q *head)
{
	tree *buf;
	prio_q *new_head, *first, *second;

	while (head->next != NULL)
	{
		new_head = head->next->next;
		first = head; 
		second = head->next;
		buf = merge(first->elem, second->elem);
		head = insertElem(new_head, buf);
		free(first);
		free(second);
	}
	buf = head->elem;
	free(head);
	return buf;
}

prio_q* create_que(prio_q *head)
{
	int num = search_max(abc);
	prio_q *tmp = NULL;
	prio_q *new_el;
	tree *singl_tree;
	while (num != NOT_FOUND)
	{
		new_el = (prio_q*)calloc(sizeof(prio_q));
		singl_tree = (tree*)calloc(sizeof(tree));
		singl_tree->count = abc[num];
		singl_tree->val = (unsigned char)num;
		abc[num] = 0;
		new_el->elem = singl_tree;
		head = new_el;
		head->next = tmp;
		tmp = new_el;
		num = search_max(abc);
	}
	return head;
}


void encoder(FILE *in, FILE *out)
{
	prio_q *head = NULL;
	tree *root = NULL;
	
	fseek(in, 2, SEEK_CUR);

	file_processing(in);
	head = create_que(head);
	root = build_HT(head);
}