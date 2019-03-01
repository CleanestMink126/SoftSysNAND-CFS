
struct node
{
    int pid;
    int state;
    int lifetime;
    double vtime;
    double IO_use;
    double priority;
    //------Below are only useful for RB tree. Don't modify -----
    char color;  // for color property
    //links for left, right children and parent
    struct node *left, *right, *parent;
};
