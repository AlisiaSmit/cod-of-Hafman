#include "header.h"

int bits[8] = { 0 };
int spare_bits[8] = { 0 };
int num_bit = 0;

void byte_to_bits(unsigned char byte, int *arr)
{
	for (int i = 0; i < 8; i++)
		arr[i] = (byte >> (7 - i)) & 1;
}

unsigned char read_bytes(FILE *in, int *arr)
{
	unsigned char c;
	c = fgetc(in);
	byte_to_bits(c, arr);
	return c;
}

tree* chose_breanch(tree* breanch)
{
	tree *tmp = breanch;
	if (!(breanch->left))
	{
		breanch = breanch->left;
		breanch = (tree*)calloc(1, sizeof(tree));
		tmp->left = breanch;
	}
	else
	{
		breanch = breanch->right;
		breanch = (tree*)calloc(1, sizeof(tree));
		tmp->right = breanch;
	}
	breanch->root = tmp;
	return breanch;
}

void replacement(FILE *in) 
{
	for  (int i = 0; i < 8; i++)
		bits[i] = spare_bits[i];
	unsigned char d = 0;
	d = read_bytes(in, spare_bits);
}

unsigned char read_char_sym(FILE *in)
{
	unsigned char elem = 0;
	int tmp = num_bit + 1;
	int j = 0;
	num_bit++;

	for (num_bit; num_bit < 8; num_bit++)
		elem = (elem << 1) | bits[num_bit];

	num_bit = num_bit % 8;
	replacement(in);

	
	for (j = 0; j < tmp; j++, num_bit++)
		elem = (elem << 1) | bits[num_bit];

	if(num_bit == 8)	replacement(in);
	num_bit = num_bit % 8;

	return elem;
}
 
tree* tree_up(tree *breanch, FILE *in, int *lv)
{
	while (bits[num_bit])
	{
		if((*lv) == 0) 
			return breanch;
		num_bit++; (*lv)--;
		breanch = breanch->root;
		if (num_bit == 8)
			replacement(in);
		num_bit = num_bit % 8;
	}
	num_bit--;
	return breanch;
}

tree* scanf_tree(FILE *in, tree *breanch, int num_cod_sym)
{
	int lv = 0;
	unsigned char c, d;
	unsigned char elem = 0;
		
	c = read_bytes(in, bits);
	d = read_bytes(in, spare_bits);
	
	while(num_cod_sym != 0)
	{
		for (num_bit; num_bit < 8; num_bit++)
		{
			if (bits[num_bit] == 0)
			{
				breanch = chose_breanch(breanch);
				lv++;
			}
			else
			{
				elem = read_char_sym(in);
				num_cod_sym--;
				breanch->val = elem;
				breanch = tree_up(breanch, in, &lv);
				
				if (num_cod_sym == 0) 
					return breanch;
			}
		}
		replacement(in);
		num_bit = 0;
	}
	return breanch;
}

unsigned char search_in_tree(tree* root, FILE *in)
{
	num_bit++;
	if (num_bit == 8)
	{
		replacement(in);
		num_bit = 0;
	}
	if (root->val) return root->val;
	if (bits[num_bit] == 0) return search_in_tree(root->left, in);
							return search_in_tree(root->right, in);
}

void decoding_text(FILE *in, FILE *out, tree *root, int byte_indent, long long int sizef)
{
	unsigned char c;
	num_bit++;
	while (!feof(in))
	{
		num_bit--;
		c = search_in_tree(root, in);
		fprintf(out, "%c", c);
		sizef--;
	}
	if (sizef)
	{
		//вот эта часть неправильная
		//for (int i = num_bit; i < 8 - byte_indent; i++)
		//{
		/*	if (root->val)
			{
				c = root->val;
				root = tmp;
				i--;
				c = root->val;
				fprintf(out, "%c", c);
				continue;
			}
			else 
				if (bits[i] == 0) root = root->left;
				else root = root->right;*/
		num_bit--;
		for (num_bit; num_bit < 8 - byte_indent; num_bit++)
		{
			c = search_in_tree(root, in);
			num_bit--;
			fprintf(out, "%c", c);
			sizef--;
		}		
	}
}

void printf_one_sym(FILE *in, FILE *out)
{
	int count = 0;
	char c = 0;

	fscanf(in, "%d", &count);
	fseek(in, 1, SEEK_CUR);
	c = fgetc(in);

	for (int i = 0; i < count; i++)
		fprintf(out, "%c", c);
	
	end_prog(in, out);
}

void decoder(FILE *in, FILE *out)
{
	tree *root = (tree*)calloc(1, sizeof(tree));
	fseek(in, 3, SEEK_SET);

	int byte_indent;
	int num_cod_sym;
	long long int sizef = 0;
	fscanf(in, "%d", &byte_indent);
	fscanf(in, "%d", &num_cod_sym);

	if (num_cod_sym == 0) end_prog(in, out);

	fscanf(in, "%Id", &sizef);


	fseek(in, 1, SEEK_CUR);
	root = scanf_tree(in, root, num_cod_sym);

	//fprintf(out, "c \r");
	decoding_text(in, out, root, byte_indent, sizef);
}