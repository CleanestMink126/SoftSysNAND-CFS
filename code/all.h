//Generally useful imports for tasks and RB tree
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>
//definition of node in RB tree
struct node
{
    int pid;
    int state;
    double lifetime;
    double vtime;
    double IO_use;
    double priority;
    //------Below are only useful for RB tree. Don't modify -----
    char color;  // for color property
    //links for left, right children and parent
    struct node *left, *right, *parent;
};

//Definitions for tasks.c
#define MAX_TASKS 100
double generate_Ndistribute_random(const double mean, const double stdDev);
struct node* generate_task(int num_tasks, double min_vtime);
void add_task(struct node *p, struct node a, int * num_tasks);
int increment_vtime(struct node *run_task, float delta);
int check_runtime(struct node *check_task);
static const int prio_to_weight[40];

//Definitions for rbtree.c
void print_node(struct node *n);
void insert(struct node **root, struct node **min, struct node *z);
void inorder(struct node *root);
int check_valid_recur(struct node *c);
struct node* delete_min(struct node **root, struct node **min);
int test_funtctionality();
//Definitions for visualization
//TODO
