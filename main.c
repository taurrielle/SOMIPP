#include "somipp.h"

int main()
{
    srand((unsigned)time(NULL));

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

    return 0;
}


