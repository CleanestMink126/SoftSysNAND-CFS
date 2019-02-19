/* Task related code for CFS */

#include<stdio.h>
#include<stdlib.h>

struct task{
  int state; //not sure if this should be in type int. This variable tells whether task is running, sleeping, etc.
  int priority;
  struct sched_entity e; //this task sturct also contains sced_entity struct
  cont struct sched_class *shced_class; //not sure about how to implement class in c, but I guess necessary functions are included in this class in some way
}

struct sched_entity{
  struct node; // the node from rbtree.c
  double vtime;
  struct load-weight load; // So there should be a structre called load that includes information about weight, that is related to priorities of sched_entities.
}

struct node
{
    int pid;
    double vtime;
    double IO_use;
    double priority;
    //------Below are only useful for RB tree. Don't modify -----
    char color;  // for color property
    //links for left, right children and parent
    struct node *left, *right, *parent;
};

static void enqueue(struct cfs_rb, struct entity){
  //add task
}

static void dequeue(struct cfs_rb, struct entity){
  //remove task
}

static void pick_next_task(struct cfs_rb, struct entity){
  //picks left-most node from rb_Tree and returns associated sched_entity
}

static void put_prev_task(struct cfs_rb, struct entity){
  //returns currently running task to rb_tree
}

static void check_preempt(struct cfs_rb, struct task new_task){

  //cfs_rb -> current_task -> sched_class -> check_preempt_curr(cfs_rb, new_task)
  /* this function preempts current task and
  replace with new_task after checking whether if it would be valid depending on vtime?*/
}
