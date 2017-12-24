#include "somipp.h"

int main()
{
    srand((unsigned)time(NULL));

    int i, j, n, m, error_code, sleep_time, nr_items, time, nr_thread;
    Order order;
    Order* temp;
    Cook cook1, cook2, cook3;
    pthread_t waiter_thread, cook_thread1, cook_thread2, cook_thread3;

    h = (heap_t *)calloc(1, sizeof (heap_t));
    que = createQueue();
    initialize_foods(menu);

    cook1.rank = 1;
    cook2.rank = 2;
    cook3.rank = 3;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&waiter_thread, NULL, waiters_thread, NULL);

    pthread_create(&cook_thread1, NULL, thread_function, (void *)cook1.rank);
    pthread_create(&cook_thread2, NULL, thread_function, (void *)cook2.rank);
    pthread_create(&cook_thread3, NULL, thread_function, (void *)cook3.rank);

    pthread_join(waiters_thread, NULL);

    pthread_join(cook_thread1, NULL);
    pthread_join(cook_thread2, NULL);
    pthread_join(cook_thread3, NULL);

    pthread_mutex_destroy(&mutex);



    // initialize_foods(menu);

    // Foods item = menu[0];

    // printf("Prep time: %d\n", item.preparation_time);
    // printf("Complexity: %d\n", item.complexity);
    // printf("Cooking apparatus: %s\n", item.cooking_apparatus);

    // enQueue(q, item);

    // q_node *node = deQueue(q);

    // Foods itemmmm;

    // itemmmm = node->item;

    // printf("Prep time: %d\n", itemmmm.preparation_time);
    // printf("Complexity: %d\n", itemmmm.complexity);
    // printf("Cooking apparatus: %s\n", itemmmm.cooking_apparatus);

    // funct(h);

    // temp = pop(h);

    // printf("Prep time: %d\n", (*temp).items[0].preparation_time);
    // printf("Priority: %d\n", (*temp).priority);
    // printf("Max wait: %d\n", (*temp).max_wait);


    // for(i = 0; i < 10; i++)
    // {
    //     nr_items = rand() % 5 + 1;
    //     orders[i] = make_order(nr_items);
    //     push(h, orders[i].priority, &orders[i]);
    // }

    // funct2(h);



    // heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    // initialize_foods(menu);


    // for(m = 0; m < 10; m++)
    // {
    //     j = 0;
    //     nr_thread = 0;
    //     temp = pop(h);

    //     printf("ITEMS SIZE: %d\n", (*temp).items_size);

    //     for(j = 0; j < (*temp).items_size; j++)
    //     {
    //         time = (*temp).items[j].preparation_time;

    //         pthread_create(&thread[nr_thread], NULL, &thread_function, (void *)time);

    //         nr_thread++;

    //         if(nr_thread == 3)
    //         {
    //             nr_thread = 0;

    //             pthread_join(thread[0], NULL);
    //             pthread_join(thread[1], NULL);
    //             pthread_join(thread[2], NULL);
    //         }
    //     }
    //     printf("Order done\n");
    // }
    return 0;
}


