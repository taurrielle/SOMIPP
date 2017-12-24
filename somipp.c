#include "somipp.h"


void push (heap_t *h, int priority, Order *data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (node_t *)realloc(h->nodes, h->size * sizeof (node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority < priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

Order *pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    Order * data = h->nodes[1].data;

    h->nodes[1] = h->nodes[h->len];
    int priority = h->nodes[1].priority;

    h->len--;

    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority > priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority > h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}

q_node * newNode(Foods i){
    q_node * temp = (q_node*)malloc(sizeof(q_node));
    temp->item = i;
    temp->next = NULL;
    return temp;
}

queue *createQueue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->front = q->rear = NULL;
    return q;
}

void enQueue(queue *q, Foods i) {
    q_node *temp = newNode(i); //(q_node*)malloc(sizeof(q_node));
    temp->item = i;
    temp->next = NULL;

    if (q->rear == NULL)
    {
       q->front = q->rear = temp;
       return;
    }

    q->rear->next = temp;
    q->rear = temp;
}

q_node *deQueue(queue *q) {
    if (q->front == NULL)
       return NULL;

    q_node *temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL)
       q->rear = NULL;
    return temp;
}

void initialize_foods(Foods menu[FOODS_SIZE]) {
    // pizza
    menu[0].preparation_time = 20;
    menu[0].complexity = 2;
    strcpy(menu[0].cooking_apparatus, "oven");

    // salad
    menu[1].preparation_time = 10;
    menu[1].complexity = 1;
    strcpy(menu[1].cooking_apparatus, "");

    // zeama
    menu[2].preparation_time = 7;
    menu[2].complexity = 1;
    strcpy(menu[2].cooking_apparatus, "stove");

    // scallop sashimiwith meyer lemon confit
    menu[3].preparation_time = 32;
    menu[3].complexity = 3;
    strcpy(menu[3].cooking_apparatus, "");

    // island duckwith mulberry mustard
    menu[4].preparation_time = 35;
    menu[4].complexity = 3;
    strcpy(menu[4].cooking_apparatus, "oven");

    // wafles
    menu[5].preparation_time = 10;
    menu[5].complexity = 1;
    strcpy(menu[5].cooking_apparatus, "stove");

    // aubergine
    menu[6].preparation_time = 20;
    menu[6].complexity = 2;
    strcpy(menu[6].cooking_apparatus, "oven");

    // lasagna
    menu[7].preparation_time = 30;
    menu[7].complexity = 2;
    strcpy(menu[7].cooking_apparatus, "oven");
}


Order make_order(int nr_items, int id){
    Order order;
    int i, menu_item_id, priority, max_preparation_time = 0;

    order.items = (Foods*)malloc(nr_items * sizeof(Foods));

    for(i = 0; i < nr_items; i++)
    {
        menu_item_id = rand() % 7;
        order.items[i] = menu[menu_item_id];
        order.items[i].order_id = id;

        if(max_preparation_time < order.items[i].preparation_time)
        {
            max_preparation_time = order.items[i].preparation_time;
        }
    }

    order.items_size = nr_items;
    order.priority = rand() % 5 + 1;
    order.max_wait = max_preparation_time * 1.3;
    return order;
}

void * thread_function(void *cook_rank)
{
    Order *temp = NULL;
    q_node *node;
    int i, j, m, k;
    int rank = (int)cook_rank;
    Foods food_item;

    while(1)
    {
        pthread_mutex_lock(&mutex);
        node = deQueue(que);
        pthread_mutex_unlock(&mutex);

        if(node == NULL){
            pthread_mutex_lock(&mutex);
            temp = pop(h);
            pthread_mutex_unlock(&mutex);

            if (temp != NULL)
            {
                pthread_mutex_lock(&mutex);
                for(j = 0; j < (*temp).items_size; j++)
                {
                    enQueue(que, (*temp).items[j]);
                }
                pthread_mutex_unlock(&mutex);
            }
        }
        else
        {
            if(rank >= node->item.complexity)
            {
                printf("\nCOOK with rank %d took an item with complexity %d and it will be ready in %d seconds.\n", rank, node->item.complexity,  node->item.preparation_time);
                sleep(node->item.preparation_time);
            }
            else
            {
                pthread_mutex_lock(&mutex);
                food_item = node->item;
                enQueue(que, food_item);
                pthread_mutex_unlock(&mutex);
            }
        }
    }
    pthread_exit(NULL);
}

void * waiters_thread()
{
    int nr_items, j, id;
    id = 1;

    for (j = 0; j < 50; j++)
    {

        int wait = rand() % 2 + 2;
        sleep(wait);

        nr_items = rand() % 5 + 1;
        orders[j] = make_order(nr_items, id);

        pthread_mutex_lock(&mutex); // lock a mutex
        push(h, orders[j].priority, &orders[j]);

        pthread_mutex_unlock(&mutex); //release a mutex
        printf("\nNew Order!!! With %d items. Move people!\n", nr_items);
        fflush(stdout);
        id++;
    }
    pthread_exit(NULL);
}