/* Task related code for CFS
  recent updates: tasks are generated in a while loop. functions that generate task,
  increment virtual runtime, and pops a task that is complete are roughly implemented.

  point of concerns:
  1. would it be possible to pop tasks by freeing?
  2. accessing specific tasks using functions to change variables within the task
*/
#include "all.h"

double generate_Ndistribute_random(const double mean, const double stdDev) {

	int hasSpare = 0;
	static double spare;
	if(hasSpare) {
		hasSpare = 0;
		return mean + stdDev * spare;
	}

	hasSpare = 1;
	static double u, v, s;
	do {
		u = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		v = (rand() / ((double) RAND_MAX)) * 2.0 - 1.0;
		s = u * u + v * v;
	}
	while( (s >= 1.0) || (s == 0.0) );
	s = sqrt(-2.0 * log(s) / s);
	spare = v * s;
  if (mean + stdDev * u * s<0){
    return 0;
  }else{
    return mean + stdDev * u * s;
  }
}
/* fucntion for generating tastruct node generate_task(){sk to be processed */
struct node* generate_task(int num_tasks){
  struct node* new_task = (struct node*)malloc(sizeof(struct node));;
  new_task->pid = num_tasks;
  new_task->state = 0;
  new_task->IO_use = 0;
  new_task->priority = 0;
  new_task->lifetime = generate_Ndistribute_random(15.0, 10.0);
  new_task->vtime = generate_Ndistribute_random(15.0, 10.0);
  return new_task;
}

/* function that adds task to que once generated*/
void add_task(struct node *p, struct node a, int * num_tasks){
  if ( *num_tasks < MAX_TASKS){
    p[*num_tasks] = a;
    *num_tasks += 1;
  }
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
