#ifndef SOMIPP_H_
#define SOMIPP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define FOODS_SIZE 8


typedef struct Foods
{
    int preparation_time;
    int complexity;
    char cooking_apparatus[6];
    int order_id;
} Foods;

typedef struct Order
{
   Foods * items;
   int items_size;
   int priority;
   int max_wait;
} Order;

typedef struct Cook
{
  int rank
} Cook;


typedef struct {
    int priority;
    Order *data;
} node_t;

typedef struct {
    node_t *nodes;
    int len;
    int size;
} heap_t;

typedef struct {
    Foods item;
    struct q_node *next;
} q_node;

typedef struct queue {
    q_node *front, *rear;
} queue;


heap_t *h;  //priority queue
queue *que;   //simple queue

pthread_mutex_t mutex;

Foods menu[FOODS_SIZE];
Order orders[50];

Order *pop (heap_t *h);
void push (heap_t *h, int priority, Order *data);

q_node *newNode(Foods i);
queue *createQueue();
void enQueue(queue *q, Foods i);
q_node *deQueue(queue *q);


void initialize_foods(Foods menu[FOODS_SIZE]);
Order make_order(int nr_items, int id);


void * thread_function();
void * waiters_thread();

#endif