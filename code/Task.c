/* Task related code for CFS
  recent updates: tasks are generated in a while loop. functions that generate task,
  increment virtual runtime, and pops a task that is complete are roughly implemented.

  point of concerns:
  1. would it be possible to pop tasks by freeing?
  2. accessing specific tasks using functions to change variables within the task
*/

#include<stdio.h>
#include<stdlib.h>
#include "node.h"
#include <time.h>
#include <unistd.h>

struct node *tasks;

/* fucntion for generating task to be processed */
struct node* generate_task(){
  struct node new_task;
  struct node* new_task_ptr = (struct node*)malloc(sizeof(struct node));
  new_task.lifetime = 10;
  new_task.vtime = 0;
  return new_task_ptr;
}

/* fucntion that increments virtual runtime of certain task if it is ran */
void increment_vtime(struct node *run_task){
  run_task -> vtime += 1;
}

/* fucntion that pops a task that has run for longer than its lifetime */
void check_runtime(struct node *check_task){
  if(check_task -> vtime > check_task -> lifetime){
    free(check_task);
  }
}

int main()
{
    time_t end;
    time_t start = time(NULL);
    time_t seconds = 10; // end loop after this time has elapsed

    end = start + seconds;

    printf("processing activated at %s", ctime(&start));

    while (start < end)
    {
        /* Do stuff while waiting */
        sleep(1);   // sleep 1s.
        start = time(NULL);
        generate_task();
        printf("task generated at time : %s", ctime(&start));

    }

    printf("end time is %s", ctime(&end));

    return 0;
}
