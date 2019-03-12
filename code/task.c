/* Task related code for CFS
  recent updates: tasks are generated in a while loop. functions that generate task,
  increment virtual runtime, and pops a task that is complete are roughly implemented.

  point of concerns:
  1. would it be possible to pop tasks by freeing?
  2. accessing specific tasks using functions to change variables within the task
*/

/*TO DO:
  - implement incrementing vtime using nice values
  - check if certain task has run for enough time
  - pop the task when it terminates
  */
#include "all.h"

/* higher priority values for lower nice values */

static const int prio_to_weight[40] = {
 /* -20 */     39,     38,     37,     36,     35,
 /* -15 */     34,     33,     32,     31,     30,
 /* -10 */      29,      28,      27,      26,      25,
 /*  -5 */      24,      23,      22,      21,      20,
 /*   0 */      19,       18,       17,       16,       15,
 /*   5 */       14,       13,       12,       11,       10,
 /*  10 */       9,        8,        7,        6,        5,
 /*  15 */        4,        3,        2,        1,        0,
};


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
struct node* generate_task(int num_tasks, double min_vtime){

  struct node* new_task = (struct node*)malloc(sizeof(struct node));;
  new_task->pid = num_tasks;
  new_task->state = 0;
  new_task->IO_use = 0;
  new_task->priority = rand()%40-20;
  new_task->lifetime = generate_Ndistribute_random(50.0, 20.0);
  new_task->vtime = min_vtime;
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
int increment_vtime(struct node *run_task, float delta){
  run_task -> vtime += delta * (double)1024/pow(1.25,(int)run_task->priority);
  run_task -> lifetime -= delta;
  printf("vtime is now: %f\n", run_task->vtime);
  return check_runtime(run_task);
}

/* fucntion that pops a task that has run for longer than its lifetime */
int check_runtime(struct node *check_task){
  if(check_task -> lifetime < 0){
    printf("task with pid %d is terminated and thus popped!\n", check_task->pid);
    free(check_task);
    return 1;
    //printf("vtime: %f\n",i->vtime);
    //check_task = NULL;
  }
  return 0;
}

/* Temporary main function to test above functions */

// int main(){
//   srand(time(0));
//   double value = (double)1024/pow(1.25,(double)30);
//   printf("value: %f\n", value);
//   struct node *new = generate_task(4,0);
//   increment_vtime(new,0.1);
//   increment_vtime(new,0.1);
//   increment_vtime(new,0.1);
//
//   printf("let's see the weight: %d\n", prio_to_weight[39]);
//   printf("priority value: %f\n", generate_task(3,0)->priority);
//
//   struct node *should_terminate = generate_task(7,0);
//   printf("given lifetime of should_terminate: %f\n", should_terminate->lifetime);
//   printf("priority of should_terminate: %f\n", should_terminate->priority);
//
//   for (int i; i<1000; i++){
//     if (increment_vtime(should_terminate,0.1)){
//       break;
//     }
//   }
//   /* check if the task is actually popped */
//   return 0;
// }
