// C program for Red-Black Tree insertion
//Adapted from https://gist.github.com/VictorGarritano/5f894be162d39e9bdd5c
//I did a good amount of adjustment because the code was wrong
#include "all.h"

void print_node(struct node *n){
  if(n->parent != NULL){
    printf("      Parent: %f %c\n",n->parent->vtime, n->parent->color);
  }else{
    printf("      Parent: NULL\n");
  }
  printf("            N: %f %c\n",n->vtime, n->color);
  if(n->left != NULL){
    printf("Left: %f %c     ",n->left->vtime, n->left->color);
  }else{
    printf("Left: NULL     ");
  }

  if(n->right != NULL){
    printf("Right: %f %c\n",n->right->vtime, n->right->color);
  }else{
    printf("Right: NULL\n");
  }
}

// Left Rotation
//root: root of the trees
//x: top node to be rotated
void left_rotate(struct node **root,struct node *x)
{
    //y stored pointer of right child of x
    struct node *y = x->right;
    //store y's left subtree's pointer as x's right child
    x->right = y->left;
    //update parent pointer of x's right
    if (x->right != NULL)
        x->right->parent = x;
    //update y's parent pointer
    y->parent = x->parent;
    // if x's parent is null make y as root of tree
    if (x->parent == NULL)
        (*root) = y;
    // store y at the place of x
    else if (x == x->parent->left)
        x->parent->left = y;
    else    x->parent->right = y;
    // make x as left child of y
    y->left = x;
    //update parent pointer of x
    x->parent = y;
}


// Right Rotation (Similar to left_rotate)
void right_rotate(struct node **root,struct node *y)
{
    struct node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent =y->parent;
    if (x->parent == NULL)
        (*root) = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Utility function to fixup the Red-Black tree after standard BST insertion
void insert_fix_up(struct node **root,struct node *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z->color == 'R' && z->parent->color == 'R')
    {
        struct node *y;

        // Find uncle and store uncle in y
        if (z->parent == z->parent->parent->left)
            y = z->parent->parent->right;
        else
            y = z->parent->parent->left;

        // If uncle is RED, do following
        // (i)  Change color of parent and uncle as BLACK
        // (ii) Change color of grandparent as RED
        // (iii) Move z to grandparent
        if (y != NULL && y->color == 'R')
        {
            y->color = 'B';
            z->parent->color = 'B';
            z->parent->parent->color = 'R';
            z = z->parent->parent;
        }

        // Uncle is BLACK, there are four cases (LL, LR, RL and RR)
        else
        {
            // Left-Left (LL) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Right Rotate Grandparent
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                right_rotate(root,z->parent->parent);
            }

            // Left-Right (LR) case, do following            return;
            // (i)  Swap color of current node  and grandparent
            // (ii) Left Rotate Parent
            // (iii) Right Rotate Grand Parent
            else if (z->parent == z->parent->parent->left &&
                z == z->parent->right)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                left_rotate(root,z->parent);
                right_rotate(root,z->parent);
            }

            // Right-Right (RR) case, do following
            // (i)  Swap color of parent and grandparent
            // (ii) Left Rotate Grandparent
            else if (z->parent == z->parent->parent->right &&
                z == z->parent->right)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                left_rotate(root,z->parent->parent);
            }

            // Right-Left (RL) case, do following
            // (i)  Swap color of current node  and grandparent
            // (ii) Right Rotate Parent
            // (iii) Left Rotate Grand Parent
            else if (z->parent == z->parent->parent->right &&
                z == z->parent->left)
            {
                char ch = z->color ;
                z->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                right_rotate(root,z->parent);
                left_rotate(root,z->parent);
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}

// Utility function to insert newly node in RedBlack tree
void insert(struct node **root, struct node **min, struct node *z)
{
    if(((*min)==NULL) || (*min)->vtime > z->vtime){
      (*min) = z;
    }
    z->left = z->right = z->parent = NULL;
    z->color = 'R';

     //if root is null make z as root
    if (*root == NULL)
    {
        z->color = 'B';
        (*root) = z;
    }
    else
    {
        struct node *y = NULL;
        struct node *x = (*root);
        // Follow standard BST insert steps to first insert the node
        while (x != NULL)
        {
            y = x;
            if (z->vtime < x->vtime)
                x = x->left;
            else
                x = x->right;
        }
        z->parent = y;
        if (z->vtime >= y->vtime)
            y->right = z;
        else
            y->left = z;
        // call insert_fix_up to fix reb-black tree's property if it
        // is voilated due to insertion.
        insert_fix_up(root,z);
    }
}

// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%f%c ", root->vtime,root->color);
    inorder(root->right);
}
//--------------------------------------------------
//All my code from now on
/*
This function will recursively check the validity of a RB tree through black
node distance and no red parent-children.

returns: Black distace to all the NULL leaves or -1 if the tree is not valid
*/
int check_valid_recur(struct node *c){
  if(c == NULL){
    return 0; //Base case
  }
  //Check that no Red Node has a red child
  if(c->color == 'R'){
    if(c->left != NULL && c->left->color == 'R'){
      printf("Red Child Error\n");
      return -1;
    } else if (c->right != NULL && c->right->color == 'R'){
      printf("Red Child Error\n");
      return -1;
    }
  }
  //Recursively call on children
  int l_val= check_valid_recur(c->left);
  int r_val= check_valid_recur(c->right);
  //Check that children follow tree rule and have same black height
  if(r_val == -1 || l_val == -1 || r_val != l_val){
    return -1;
  }
  //Return height(increment if it is a black node)
  return l_val + (c->color == 'B');
}


//Code to resolve the problem of a double black node in a tree
void resolve_db(struct node **root, struct node *db, struct node *parent){
  //advised by https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
  if(db == (*root)){
    return;
  }
  struct node *s = parent->right;
  //3 cases:
  /*
  1.s is red
  2,one of S's children is red
  3.all is black (recursive)
  */
  if(s == NULL){
    resolve_db(root, parent, parent->parent);
  }else if(s->color =='R'){
    //Case 1
    s->color = 'B';
    parent->color = 'R';
    left_rotate(root, parent);
    resolve_db(root, db, parent);
  //Case 2 Right Right
  }else if(s->right != NULL && s->right->color == 'R'){
    s->right->color = s->color;
    s->color = parent->color;
    parent->color = 'B';
    left_rotate(root, parent);
  }else if(s->left != NULL && s->left->color == 'R'){
    //Case 2 Right Left
    s->left->color = parent->color;
    parent->color = 'B';
    right_rotate(root, s);
    left_rotate(root, parent);
  }else{
    //Case 3
    s->color = 'R';
    if (parent->color == 'B'){
      resolve_db(root, parent, parent->parent);
    }else{
      parent->color = 'B';
    }
  }
}

/*Delte the minimum from a RB tree. May adjust min and root pointers
Input:
root: pointer to pointer to the root of the trees
min: pointer to pointer to the minimum node of the trees
Returns: pointer to removed minimum node
*/
struct node* delete_min(struct node **root, struct node **min){

  struct node *x = (*min);
  if(x == NULL){
    printf("BIG OOPS: min null\n");
    return NULL;
  }
  //Check case where the minimum has a right child and
  if(x->right != NULL){
    (*min) = x->right;
    x->right->color = 'B';
    x->right->parent = x->parent;
    if(x->parent != NULL) x->parent->left = x->right;
    else *root = x->right;
  }else if(x != (*root)){
    //Minimum does not have child and is red
    (*min) = x->parent;
    x->parent->left = NULL;
    if (x->color == 'B'){//we have a double black situation
      resolve_db(root, NULL, *min); //pass in double black node and its parent
    }
  }else{
    (*root) = NULL;
    (*min) = NULL;
    return x;
  }
  (*root)->color = 'B'; //keep root always black
  x->parent = NULL;
  x->right = NULL;
  x->color = 'R';
  return x;
}

/* Drier program to test above function*/
int test_funtctionality()
{
    struct node *root = NULL;
    struct node *min = NULL;
    struct node* n;
    //-----------Insert values------------
    int values[] = {10,20,40,30,50,35,25,37,34,46,7,6,44,23,56,67,1000,2,3,230,20,23,12,45};
    for(int i = 0; i < sizeof(values)/sizeof(int); i++){
      n = (struct node*)malloc(sizeof(struct node));
      n->vtime = (double) values[i];
      insert(&root, &min, n);
      printf("Min: %f\n", (double) min->vtime);
    }
    //--------------Show IOT------------------
    printf("inorder Traversal Is : ");
    inorder(root);
    printf("\nHeight of tree: %i\n", check_valid_recur(root));
    //---------------Delete min N times--------------
    for(int i = 0; i < sizeof(values)/sizeof(int); i++){
      printf("----------------------------------------\n");
      if(min != NULL){
        printf("Min %f\n",min->vtime);
      }
      n = delete_min(&root, &min);
      printf("Height of tree: %i\n", check_valid_recur(root));
      //printf("End\n");
    }
    return 0;
}

/* Drier program to test above function*/
struct node* build_tree()
{
    struct node *root = NULL;
    struct node *min = NULL;
    struct node* n;
    //-----------Insert values------------
    int values[] = {10,20,40,30,50,35,25,37,34,46,7,6,44,23,56,67,1000,2,3,230,20,23,12,45};
    for(int i = 0; i < sizeof(values)/sizeof(int); i++){
      n = (struct node*)malloc(sizeof(struct node));
      n->vtime = (double) values[i];
      insert(&root, &min, n);
    }
    // inorder(root);

    return root;
}
