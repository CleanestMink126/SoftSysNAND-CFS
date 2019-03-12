#include "all.h"

int main()
{
    //Helpful stuff for timing
    srand(time(0));
    time_t end;
    time_t start = time(0);
    time_t seconds = 10; // end loop after this time has elapsed
    struct timespec tim;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000000L;
    end = start + seconds;
    printf("processing activated at %s", ctime(&start));
    //Helpful stuff for red black trees
    int num_of_tasks = 0;
    struct node *root = NULL;
    struct node *min = NULL;
    struct node* n;
    int starting_tasks = 12;
    int max_tasks = 30;
    int generate_new_tasks = 0;
    int put_back = 1;
    //-----------Generate tasks------------
    for(int i = 0; i < starting_tasks; i++){
      n = generate_task(num_of_tasks, 0);
      insert(&root, &min, n);
      num_of_tasks++;
    }

    while (start < end)
    {
        /* Do stuff while waiting */
        nanosleep(&tim,NULL);
        start = time(0);

        n = delete_min(&root, &min);
        printf("PID:%i    Vtime:%lf\n",n -> pid, n ->vtime);
        put_back = 1;
        while(n -> vtime <= min -> vtime){
          puts("Increment\n");
          if (increment_vtime(n,1)){
            put_back = 0;
            break;
          }//I didnt decrement the number of nodes cause it causes PID collisions
          int prob = rand() % 4;
          if (prob == 0 && generate_new_tasks && num_of_tasks < max_tasks){
            // printf("task generated at time : %s", ctime(&start));
            struct node* b = generate_task(num_of_tasks, min -> vtime);
            insert(&root, &min, b);
            printf("lifetime: %f \n", n->lifetime);
            num_of_tasks++;
          }
        }
        if(put_back){
          insert(&root, &min, n);
          printf("Put back\n");
        }else{
          printf("Terminated\n");
        }
        printf("PID:%i    Vtime:%lf\n",n -> pid, n ->vtime);
        printf("-----------------\n");
    }

    printf("end time is %s", ctime(&end));

/* print all tasks in que */
    // puts("lifetime of generated tasks: \n");
    // for(int i = 0; i<num_of_tasks; i++){
    //   n = delete_min(&root, &min);
    //   printf( "%fs \n", n->vtime);
    // }

    return 0;
}
