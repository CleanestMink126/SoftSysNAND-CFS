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

//Function to set task color so for more readable code
void set_task_color_1(struct node* n){
	double g = (40.0  - (n->priority + 20.0))/40.0;
	double arr[] = {0.0, g, 0.0};
 	n->priority_color[0] = arr[0];
 	n->priority_color[1] = arr[1];
 	n->priority_color[2] = arr[2];
}

/* fucntion for generating tastruct node generate_task(){sk to be processed */
struct node* generate_task(int num_tasks, double min_vtime){

  double Ndistribute;
  Ndistribute = exp(generate_Ndistribute_random(MEAN_RUNTIME, STD_RUNTIME));
	printf("Runtime: %lf\n", Ndistribute );

  struct node* new_task = (struct node*)malloc(sizeof(struct node));;
  new_task->pid = num_tasks;
  new_task->state = 0;
  new_task->IO_use = 0;
  new_task->priority = rand()%40-20;
	set_task_color_1(new_task);
  new_task->lifetime = Ndistribute;
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
  run_task -> vtime += delta * (double)1024/pow(1.25,-1 * (int)run_task->priority);
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

//  int main(){
//    srand(time(0));
//    double value = (double)1024/pow(1.25,(double)30);
//    printf("value: %f\n", value);
//    struct node *new = generate_task(4,0);
//    increment_vtime(new,0.1);
//    increment_vtime(new,0.1);
//    increment_vtime(new,0.1);

//    printf("let's see the weight: %d\n", prio_to_weight[39]);
//    printf("priority value: %f\n", generate_task(3,0)->priority);

//    struct node *should_terminate = generate_task(7,0);
//    printf("given lifetime of should_terminate: %f\n", should_terminate->lifetime);
//    printf("priority of should_terminate: %f\n", should_terminate->priority);

//    for (int i; i<100; i++){
//      printf("lifetime: %f\n",generate_task(5,0) -> lifetime);
//    }
//    /* check if the task is actually popped */
//    return 0;
//  }
