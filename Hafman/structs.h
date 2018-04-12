#ifndef __STRUCTS_H__
	#define __SRUCTS_H__

typedef struct Stack_St
{
	int val;
	struct Stack_st *next;
}stack;

typedef struct List_st
{
	int val;
	struct List_st *next;
	struct List_st *prev;
}list;

typedef struct Queue_st
{
	list *head;
	list *tail;
}queue;

typedef struct Tree_st
{
	int count;
	unsigned char val;
	struct Tree_st *right;
	struct Tree_st *left;
	struct Tree_st *root;
}tree;

typedef struct Priority_Q_st
{
	tree *elem;
	struct Priority_Q_st *next;
}prio_q;


// добавляет элемент в начало стека
// возврящает ссылку наэтот элемент
stack *push(stack *head, int value);

// если стек пуст, ничего не возвращает
// если нет - возврящает элемент из начаа стека
// и переобозначает голову стека
int pop(stack **head);

queue *enque(queue *elem, int value);


int deque(queue *elem);


// добавляет корень или вотвь под корнем
// не предусматривает случай, когда корень и вктви заняты
// проврка на это ложится на плечи вызывающего фукцию
void put_tree(tree *head, int value);

int get_tree(tree *head);

#endif