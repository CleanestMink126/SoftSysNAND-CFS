#include "all.h"

int main()
{
    time_t end;
    time_t start = time(NULL);
    time_t seconds = 10; // end loop after this time has elapsed
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000L;

    end = start + seconds;

    printf("processing activated at %s", ctime(&start));

    int num_of_tasks = 0;
    struct node *root = NULL;
    struct node *min = NULL;
    struct node* n;
    //-----------Insert values------------
    int values[] = {10,20,40,30,50,35,25,37,34,46,7,6,44,23,56,67,1000,2,3,230,20,23,12,45};
    int len = sizeof(values)/sizeof(len);
    srand(time(NULL));

    while (start < end)
    {
        /* Do stuff while waiting */
        nanosleep(&tim,NULL);   // sleep 1s.
        start = time(NULL);
        printf("%i\n",rand());
        int prob = rand() % 4; 
        if (prob == 0 && num_of_tasks < len){
          // printf("task generated at time : %s", ctime(&start));
          n = generate_task(num_of_tasks);
          n->vtime = (double) values[num_of_tasks];
          insert(&root, &min, n);
          printf("lifetime: %f \n", n->lifetime);
          num_of_tasks++;
        }else{
          puts("task not generated\n");
        }
    }

    printf("end time is %s", ctime(&end));

/* print all tasks in que */
    puts("lifetime of generated tasks: \n");
    for(int i = 0; i<num_of_tasks; i++){
      n = delete_min(&root, &min);
      printf( "%fs \n", n->vtime);
    }

    return 0;
}
