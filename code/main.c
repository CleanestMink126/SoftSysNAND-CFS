#include "all.h"

int main()
{
    test_funtctionality();
    struct node tasks[MAX_TASKS];
    time_t end;
    time_t start = time(NULL);
    time_t seconds = 10; // end loop after this time has elapsed

    end = start + seconds;

    printf("processing activated at %s", ctime(&start));

    int *num_of_tasks_ptr;
    int num_of_tasks = 0;
    num_of_tasks_ptr = &num_of_tasks;
    //*num_of_tasks = 0;
    //struct node new;

    while (start < end)
    {
        srand(time(0));
        /* Do stuff while waiting */
        sleep(1);   // sleep 1s.
        start = time(NULL);
        int prob = rand() % 4;
        if (prob == 0){
          printf("task generated at time : %s", ctime(&start));
          struct node new;
          new = generate_task();
          add_task(tasks, new, num_of_tasks_ptr);
          printf("vtime: %fs \n", new.vtime);
        }else{
          puts("task not generated");
        }
    }

    printf("end time is %s", ctime(&end));
    int i;

/* print all tasks in que */
    puts("vtime of generated tasks: \n");
    for(i = 0; i<*num_of_tasks_ptr; i++){
      printf( "%fs \n", tasks[i].vtime);
    }

    return 0;
}
