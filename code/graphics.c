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

  if(direction == 0){
    xmove = -CIRCLE_HEIGHT;
    xrel = -curr_x;
  }
  else {
    xmove = CIRCLE_HEIGHT;
    xrel = curr_x;
  }

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

  if(root->color == 'B'){
    cairo_set_source_rgb(cr, RED->r, RED->g, RED->b);
  }
  else {
    cairo_set_source_rgb(cr, BLACK->r, BLACK->g, BLACK->b);
  }

  char id[7] = "";
  char vtime[7] = "";
  snprintf(id, sizeof(id), "%d", root->pid);
  snprintf(vtime, sizeof(vtime), "%.1f", root->vtime);

  cairo_translate(cr, -TEXT_DISTANCE*CIRCLE_HEIGHT, 0);
  cairo_show_text(cr, id);
  cairo_fill(cr);

  cairo_translate(cr, 0, FONT_SIZE);
  cairo_show_text(cr, vtime);
  cairo_fill(cr);
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

  //Recursively do the drawing that we want
  drawing_recursive(cr, widget, temp);
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

int main(int argc, char *argv[])
{

  GtkWidget *window;
  GtkWidget *darea;
  RED = make_color(0.69, 0.19, 0.0);
  BLACK = make_color(0.0, 0.0, 0.0);
  WHITE = make_color(1.0, 1.0, 1.0);
  ROOT = build_tree();

  glob.count = 0;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_title(GTK_WINDOW(window), "RB Tree Demo");

  g_timeout_add(LOOP_WAIT, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
