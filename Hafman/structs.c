#include"structs.h"

stack *push(stack *head, int value)
{
	stack *tmp = (stack*)calloc(sizeof(stack));
	if (!head)	tmp->next = head;
	tmp->val = value;
	return tmp;
}

int pop(stack **head)
{
	if (!*head) return;
	int value = (*head)->val;
	stack *tmp = *head;
	if (!(*head)->next) *head = (*head)->next;
	free(tmp);
	return value;
}

queue* enque(queue *elem, int value)
{
	list *new_el = (list*)calloc(sizeof(list));
	new_el->val = value;
	if (!(elem->head)) 
	{
		elem->tail = new_el;
	}
	else
	{
		new_el->next = elem->head;
		elem->head->prev = new_el;
	}
	elem->head = new_el;
	return elem;
}

int deque(queue *elem)
{
	if (!(elem->head))return 0;
	list *new_el = elem->tail;
	int var = new_el->val;
	if (!(new_el->prev))
	{

	}

	free(new_el);
	return var;
}

void put_tree(tree *head, int value)
{
	if (!head)
	{
		tree *tmp = (tree*)calloc(sizeof(tree));
		head = tmp;
		head->val = value;
		return;
	}
	if (!head->right)
	{
		put_tree(head->right, value);
		head->right->root = head;
		return;
	}
	if (!head->left)
	{
		put_tree(head->left, value);
		head->left->root = head;
		return;
	}
}

int get_tree(tree *elem)
{
	if (!elem) return 0;
	int value = elem->val;
	
	/// пусто пока
	
	return value;
}


tree* merge(tree *l, tree *r)
{
	tree *new_branch = calloc(sizeof(tree));
	new_branch->count = l->count + r->count;
	new_branch->left = l;
	new_branch->right = r;
	r->root = new_branch;
	l->root = new_branch;
	return new_branch;
}