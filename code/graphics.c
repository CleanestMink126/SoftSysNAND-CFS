#include "graphics.h"

int count = 0;
int curr_number = 0;
double curr_x = 0;
double curr_y = 0;

/*
Color object making method. No current color delete method.
Inputs:
double r (red value on scale of 0-1)
double b (blue value on scale of 0-1)
double g (green value on scale of 0-1)

Returns: A pointer to a color allocated in the heap
*/
Color *make_color(double r, double b, double g){
  Color *c = malloc(sizeof(Color));
  c->r = r;
  c->g = g;
  c->b = b;
  return c;
}


/*
GTK function that I believe is necessary. May be able to kill but not vocused on that.
Inputs:
GtkWidget* widget
cairo_t* cr
gpointer user_data (unclear if necessary)

Returns: gboolean (FALSE)
*/
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);
  return FALSE;
}


/*
Helper function to set the color based on the color of a node (a char in, R/B).
Inputs:
cairo_t *cr
char color_in

Returns: void
*/
static void set_color(cairo_t *cr, char color_in){
  if(color_in == 'R'){
    cairo_set_source_rgb(cr, RED->r, RED->g, RED->b);
  }
  else {
    cairo_set_source_rgb(cr, BLACK->r, BLACK->g, BLACK->b);
  }
}


/*
Draws a line from current location to the desired node ("root"). Direction indicates the direction the node is.
Inputs:
GtkWidget* widget
cairo_t* cr
int direction (direction that a root is from its parent; 0 is left and 1 is right)
struct node* root (node to whom a line is being drawn)

Returns: void
*/
static void draw_line(GtkWidget *widget, cairo_t *cr, int direction, struct node* root){
  cairo_move_to (cr, 0, 0);
  int xmove, xrel;

  set_color(cr, root->color);

  //Figure out what direction from the root node you will go to your child
  if(direction == 0){
    xmove = -CIRCLE_HEIGHT;
    xrel = -curr_x;
  }
  else {
    xmove = CIRCLE_HEIGHT;
    xrel = curr_x;
  }
  
  //Move and draw your line
  cairo_move_to(cr, xmove, 0);
  cairo_rel_line_to(cr, xrel, (int) CIRCLE_HEIGHT * HEIGHT_CONSTANT);
  cairo_set_line_width (cr, BRANCH_WIDTH);
  cairo_stroke(cr);
  cairo_fill(cr);
  cairo_set_line_width(cr, LINE_WIDTH);
}


/*
Writes the necessary text of a node on a given node.
Inputs:
GtkWidget* widget
cairo_t* cr
struct node* root (node whose text is to be displayed)

Returns: void
*/
static void circle_text(GtkWidget *widget, cairo_t *cr, struct node* root){
  //Set color (opposite of node color)
  if(root->color == 'B'){
    cairo_set_source_rgb(cr, RED->r, RED->g, RED->b);
  }
  else {
    cairo_set_source_rgb(cr, BLACK->r, BLACK->g, BLACK->b);
  }

  //Set the strings you want
  char id[7] = "";
  char vtime[7] = "";
  snprintf(id, sizeof(id), "%d", root->pid);
  snprintf(vtime, sizeof(vtime), "%.1f", root->vtime);

  //Proint the first string
  cairo_translate(cr, -TEXT_DISTANCE*CIRCLE_HEIGHT, 0);
  cairo_show_text(cr, id);
  cairo_fill(cr);

  //Print the second string
  cairo_translate(cr, 0, FONT_SIZE);
  cairo_show_text(cr, vtime);
  cairo_fill(cr);
  //Go back to the initial location
  cairo_translate(cr,  TEXT_DISTANCE*CIRCLE_HEIGHT, -FONT_SIZE);
}

/*
Draws a circle of size CONSTANT_HEIGHT.
Inputs:
cairo_t* cr
GtkWidget* widget
struct node* root (node to be drawn)

Returns: void
*/
static void draw_circle(GtkWidget *widget, cairo_t *cr, struct node* root){
  set_color(cr, root->color);
  cairo_arc(cr, 0, 0, CIRCLE_HEIGHT, 0, 2 * M_PI);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);
}


/*
The function that iterates through all nodes and draws the tree.
Inputs:
cairo_t* cr
GtkWidget* widget
struct node* root (node to be drawing the tree from)

Returns: void
*/
static void drawing_recursive(cairo_t *cr, GtkWidget *widget, struct node* root){
  //Set up variables
  int direction;

  //Draw left child
  if(root->left != NULL){
    //Calculate next node position
    curr_x = curr_x / 2;
    curr_y = curr_y - HEIGHT_CONSTANT*CIRCLE_HEIGHT;
    direction = 0;

    draw_line(widget, cr, direction, root->left);

    //Translate to new position, draw node, then return to current position
    cairo_translate(cr, (int) -curr_x, (int) CIRCLE_HEIGHT * HEIGHT_CONSTANT);
    drawing_recursive(cr, widget, root->left);
    cairo_translate(cr, (int) curr_x, (int) CIRCLE_HEIGHT * -HEIGHT_CONSTANT);

    //reset position to current position
    curr_x = curr_x * 2;
    curr_y = curr_y + HEIGHT_CONSTANT*CIRCLE_HEIGHT;
  }

  //Draw right child
  if(root->right != NULL){
    //Calculate next node position
    curr_x = curr_x / 2;
    curr_y = curr_y - HEIGHT_CONSTANT*CIRCLE_HEIGHT;
    direction = 1;

    draw_line(widget, cr, direction, root->right);

    //Translate to new position, draw node, then return to current position
    cairo_translate(cr, (int) curr_x, (int) CIRCLE_HEIGHT * HEIGHT_CONSTANT);
    drawing_recursive(cr, widget, root->right);
    cairo_translate(cr, (int) -curr_x, (int) CIRCLE_HEIGHT * -HEIGHT_CONSTANT);

    //reset position to current position
    curr_x = curr_x * 2;
    curr_y = curr_y + HEIGHT_CONSTANT*CIRCLE_HEIGHT;
  }

  //Draw the current node
  draw_circle(widget, cr, root);
  circle_text(widget, cr, root);

}

/*
Main do_drawing method used by gtk.
Inputs:
cairo_t* cr
GtkWidget *widget

Returns: void
*/
static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  //Background setup and variable creation
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  struct node* temp = ROOT;
  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);
  curr_x = width/2;
  curr_y = CIRCLE_HEIGHT*3;

  //Set up where we want to start with appropriate things
  cairo_translate(cr, curr_x, curr_y);
  cairo_select_font_face(cr, FONT, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, FONT_SIZE);
  cairo_set_line_width(cr, LINE_WIDTH);

  //Paint over any prior background
  cairo_set_source_rgb (cr, WHITE->r, WHITE->g, WHITE->b);
  cairo_paint (cr);

  struct node* n;
  int put_back = 1;

  n = delete_min(&ROOT, &MIN);
  printf("PID:%i    Vtime:%lf\n",n -> pid, n ->vtime);
  put_back = 1;
  while(n -> vtime <= MIN -> vtime){
    puts("Increment\n");
    if (increment_vtime(n,1)){
      put_back = 0;
      break;
    }//I didnt decrement the number of nodes cause it causes PID collisions
    int prob = rand() % 4;
    if (prob == 0 && GENERATE_NEW_TASKS && NUM_OF_TASKS < MAX_TASKS){
      struct node* b = generate_task(NUM_OF_TASKS, MIN -> vtime);
      insert(&ROOT, &MIN, b);
      printf("lifetime: %f \n", n->lifetime);
      NUM_OF_TASKS++;
    }
  }
  if(put_back){
    insert(&ROOT, &MIN, n);
    printf("Put back\n");
  }else{
    printf("Terminated\n");
  }
  printf("PID:%i    Vtime:%lf\n",n -> pid, n ->vtime);
  printf("-----------------\n");

  //Recursively do the drawing that we want
  drawing_recursive(cr, widget, ROOT);
}


/*
A time_handler function. Used in conjunction with glob. 1 Glob = 1 ms
Inputs: GTKWidget widget

Returns: a gboolean
*/
static gboolean time_handler(GtkWidget *widget)
{
  glob.count += 1;
  gtk_widget_queue_draw(widget);

  return TRUE;
}
