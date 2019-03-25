/* Task related code for CFS*/

#include "all.h"
//Generates sample from a log-normal distribution with the following mean and STD
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

//Function to set task color for mode 1
void set_task_color_1(struct node* n){
	double g = (40.0  - (n->priority + 20.0))/40.0;
	double arr[] = {0.0, g, 0.0};
 	n->priority_color[0] = arr[0];
 	n->priority_color[1] = arr[1];
 	n->priority_color[2] = arr[2];
}

/* fucntion for generating task to be processed
 struct node generate_task(){ */
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


/* fucntion that increments virtual runtime of certain task if it is ran
Returns: whether or not the task had ended
*/
int increment_vtime(struct node *run_task, float delta){
  run_task -> vtime += delta * (double)1024/pow(1.25,-1 * (int)run_task->priority);
  run_task -> lifetime -= delta;
  printf("vtime is now: %f\n", run_task->vtime);
  return check_runtime(run_task);
}

/* fucntion that pops a task that has run for longer than its lifetime
Returns: Whether or not the task has ended
 */
int check_runtime(struct node *check_task){
  if(check_task -> lifetime < 0){
    printf("task with pid %d is terminated and thus popped!\n", check_task->pid);
    free(check_task);
    return 1;
  }
  return 0;
}
