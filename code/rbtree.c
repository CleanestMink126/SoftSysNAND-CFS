// C program for Red-Black Tree insertion
//Adapted from https://gist.github.com/VictorGarritano/5f894be162d39e9bdd5c

#include<stdio.h>
#include<stdlib.h>

//A Red-Black tree node structure
struct node
{
    int data;     // for data part
    char color;  // for color property

    //links for left, right children and parent
    struct node *left, *right, *parent;
};

// Left Rotation
//root: root of the trees
//x: top node to be rotated
void LeftRotate(struct node **root,struct node *x)
{
    if(x == NULL){
      printf("LNull x");
    }
    //y stored pointer of right child of x
    struct node *y = x->right;

    if(y == NULL){
      printf("LNull y");
    }

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


// Right Rotation (Similar to LeftRotate)
void rightRotate(struct node **root,struct node *y)
{
    if(y == NULL){
      printf("RNull y");
    }
    struct node *x = y->left;
    if(x == NULL){
      printf("RNull x");
    }

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
void insertFixUp(struct node **root,struct node *z)
{
    // iterate until z is not the root and z's parent color is red
    while (z != *root && z->parent->color == 'R')
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
            if(z ==NULL){
              printf("No z");
            }
            if(z->parent ==NULL){
              printf("No parent");
            }
            if(z->parent->parent ==NULL){
              printf("No granparent");
            }
            // return;
            if (z->parent == z->parent->parent->left &&
                z == z->parent->left)
            {
                char ch = z->parent->color ;
                z->parent->color = z->parent->parent->color;
                z->parent->parent->color = ch;
                rightRotate(root,z->parent->parent);
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
                LeftRotate(root,z->parent);
                rightRotate(root,z->parent);
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
                LeftRotate(root,z->parent->parent);
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
                rightRotate(root,z->parent);
                LeftRotate(root,z->parent);
            }
        }
    }
    (*root)->color = 'B'; //keep root always black
}

// Utility function to insert newly node in RedBlack tree
void insert(struct node **root, int data)
{
    // Allocate memory for new node
    struct node *z = (struct node*)malloc(sizeof(struct node));
    z->data = data;
    z->left = z->right = z->parent = NULL;

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
            if (z->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;
        if (z->data > y->data)
            y->right = z;
        else
            y->left = z;
        z->color = 'R';

        // call insertFixUp to fix reb-black tree's property if it
        // is voilated due to insertion.

        insertFixUp(root,z);
    }
}

// A utility function to traverse Red-Black tree in inorder fashion
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d%c ", root->data,root->color);
    inorder(root->right);
}

int check_valid_recur(struct node *c){
  if(c == NULL){
    return 0;
  }
  if(c->color == 'R'){
    if(c->left != NULL && c->left->color == 'R'){
      return -1;
    } else if (c->right != NULL && c->right->color == 'R'){
      return -1;
    }
  }
  int l_val= check_valid_recur(c->left);
  int r_val= check_valid_recur(c->right);

  if(r_val == -1 || l_val == -1 || r_val != l_val){
    return -1;
  }
  return l_val + (c->color == 'B');
}

/* Drier program to test above function*/
int main()
{
    // printf("Init");
    struct node *root = NULL;

    // printf("Test");root
    int values[] = {10,20,40,30,50,35,25,37,34,46,7,6,44,23,12,45};
    // int values[] = {10,20};
    for(int i = 0; i < sizeof(values)/sizeof(int); i++){
      printf("%d\n", i);
      insert(&root, values[i]);
    }
    // insert(&root,10);
    // insert(&root,20);
    // insert(&root,40);
    // insert(&root,30);
    // insert(&root,50);
    // insert(&root,35);
    // insert(&root,25);
    // insert(&root,37);
    printf("inorder Traversal Is : ");
    inorder(root);
    printf("\nHeight of tree: %i\n", check_valid_recur(root));

    return 0;
}
