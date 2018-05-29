#include "header.h"

sym *Haf[256];
int abc[256] = { 0 };
int arr_bit[8]; int num_bit;
int haf_cod[8] = { 0 };

int  file_processing(FILE *in)
{
	int count = 0;
	unsigned char syms[1];
	int read_el = 0;

	read_el =(int) fread(syms, sizeof(char), 1, in);
	if (feof(in)) return 0;
	fseek(in, -1, SEEK_CUR);

	do
	{
		read_el = fread(syms, sizeof(char), 1, in);
		if (abc[syms[0]] == 0) count++;
		abc[syms[0]] ++;
	} while (read_el == 1);

	return count;
}

long long int file_size(FILE *in)
{
	long long int count = 0;
	unsigned char syms[1024];
	int read = 0;
	
	fseek(in, 3, SEEK_SET);

	do
	{
		read = fread(syms, sizeof(char), 1024, in);
		count = count + read;
	} while (read == 1024);

	return count;
}

tree* create_branch(int *abc, int num)
{
	tree *root;
	root = (tree*)calloc(1, sizeof(tree));
	memset(root, 0, sizeof(tree));
	root->count = abc[num];
	root->val = (unsigned char)num;
	return root;
}

prio_q* build_queue(int num, prio_q *head)
{
	if (!head)
	{
		prio_q *new_el = (prio_q*)calloc(1, sizeof(prio_q));
		new_el->elem = create_branch(abc, num);
		head = new_el;
		return head;
	}
	if (head->elem->count < abc[num])
	{
		head->next = build_queue(num, head->next);
		return head;
	}

	prio_q *new_el = (prio_q*)calloc(1, sizeof(prio_q));
	new_el->elem = create_branch(abc, num);

	new_el->next = head;
	head = new_el;
	return head;
}

tree* pop(prio_q **el)
{
	prio_q *tmp = *el;
	tree *tr = (*el)->elem;

	*el = (*el)->next;
	free(tmp);

	return tr;
}

tree* merge(tree *l, tree *r)
{
	tree *new_branch = calloc(1, sizeof(tree));
	new_branch->count = l->count + r->count;
	new_branch->left = l;
	new_branch->right = r;
	return new_branch;
}

prio_q* push(prio_q *head, tree *el)
{
	if (!head)
	{
		prio_q *new_el = (prio_q*)calloc(1, sizeof(prio_q));
		new_el->elem = el;
		head = new_el;
		return head;
	}
	if (head->elem->count < el->count)
	{
		head->next = push(head->next, el);
		return head;
	}

	prio_q *new_el = (prio_q*)calloc(1, sizeof(prio_q));
	new_el->elem = el;

	new_el->next = head;
	head = new_el;
	return head;
}

tree* build_tree(prio_q* head)
{
	if (!head) return NULL;
	tree *a, *b, *c;
	while ((head) && (head->next))
	{
		a = pop(&head);
		b = pop(&head);

		c = merge(a, b);
		head = push(head, c);
	}

	a = pop(&head);
	return a;
}

void make_byte(int num, FILE *out)
{
	arr_bit[num_bit] = num;
	num_bit++;
	if (num_bit == 8)
	{
		unsigned char c = 0;
		for (int j = 0; j < 8; j++)
			c = ((c << 1) | arr_bit[j]);
		fprintf(out, "%c", c);
		num_bit = 0;
	}
}

void make_Haf_sym(unsigned char symb, int i)
{
	Haf[symb] = (sym*)calloc(1, sizeof(sym));
	Haf[symb]->count = i;
	Haf[symb]->sym_Haf = (int*)calloc(i, sizeof(int));
	for (int j = 0; j <= i; j++)
		Haf[symb]->sym_Haf[j] = haf_cod[j];
}


void dfs(FILE *out, tree *root, int count_haf)
{
	if (root->left)
	{
		make_byte(0, out);
		haf_cod[count_haf] = 0;
		dfs(out, root->left, count_haf + 1);
		make_byte(1, out);
	}
	if (root->right)
	{
		make_byte(0, out);
		haf_cod[count_haf] = 1;
		dfs(out, root->right, count_haf + 1);
		make_byte(1, out);
	}
	if (!((root->left) || (root->left)))
	{
		make_byte(1, out);
		unsigned int c;
		for (int j = 0; j < 8; j++)
		{
			c = ((root->val) >> (7 - j)) & 1;
			make_byte(c, out);
		}
		make_Haf_sym(root->val, count_haf);
	}
}

void coding_text(FILE *in, FILE *out)
{
	unsigned char c;
	int i = 0;

	c = fgetc(in);
	while (!feof(in))
	{
		for (i = 0; i < Haf[c]->count; i++)
			make_byte(Haf[c]->sym_Haf[i], out);
		c = fgetc(in);
	}

	if (num_bit != 0)
	{
		for (i = num_bit; i < 8; i++)
			arr_bit[i] = 0;
		c = 0;
		for (i = 0; i < 8; i++)
			c = ((c << 1) | arr_bit[i]);
		fprintf(out, "%c", c);
	}
}

void create_new_file(FILE *in, FILE *out, tree *root, int num_cod_sym, long long int count)
{
//	fprintf(out, "d \r  %d ", num_cod_sym);
	fprintf(out, "%d %Id ", num_cod_sym, count);

	dfs(out, root, 0);

	fseek(in, 3, SEEK_SET);
	coding_text(in, out);

//	fseek(out, 3, SEEK_SET);
}

void copy_file(FILE *in)
{
	FILE *copyf = fopen("copyin.txt", "wb");
	fseek(in, 0, SEEK_SET);
	unsigned char c = 0;
	c = fgetc(in);
	while (!feof(in))
	{
		fprintf(copyf, "%c", c);
		c = fgetc(in);
	}
	fclose(copyf);
	fseek(in, 0, SEEK_SET);
}

//void single_sym(FILE *in, FILE *out)
//{
//	int i = 0;
//	for (i = 0; i < 256; i++)
//		if (abc[i] != 0) break;
//
//	fprintf(out, "0 1 %d %c", abc[i] - 1, (unsigned char)i);
//
//	end_prog(in, out);
//}

void empty_file(FILE *in, FILE *out)
{
	fprintf(out, "0 0");
	end_prog(in, out);
}

void encoder(FILE *in, FILE *out)
{
	prio_q *head = NULL;
	tree *root;
	int num_cod_sym = 0;
	long long int fsize = 0;
	 
	copy_file(in);

	fseek(in, 3, SEEK_SET);

	num_cod_sym = file_processing(in);
	if (num_cod_sym != 0) fsize = file_size(in);

	//if (num_cod_sym == 1) single_sym(in, out);
	if (num_cod_sym == 0) empty_file(in, out);

	for (int i = 0; i < 256; i++)
		if (abc[i] != 0)
			head = build_queue(i, head);

	root = build_tree(head);

	create_new_file(in, out, root, num_cod_sym, fsize);
}