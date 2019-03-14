#include "graphics.h"


int count = 0;
int curr_number = 0;
double curr_x = 0;
double curr_y = 0;

Color *make_color(double r, double b, double g){
  Color *c = malloc(sizeof(Color));
  c->r = r;
  c->g = g;
  c->b = b;
  return c;
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);
  return FALSE;
}

static void draw_line(GtkWidget *widget, cairo_t *cr, int direction){
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  cairo_move_to (cr, 0, 0);
  int xmove, xrel;
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

  cairo_set_line_width (cr, 2);
  cairo_stroke(cr);
  cairo_fill(cr);
}

static int set_color(GtkWidget *widget, cairo_t *cr, char in){
  if(in == 'R'){
    cairo_set_source_rgb(cr, RED->r, RED->g, RED->b);
    return 1;
  }
  else {
    cairo_set_source_rgb(cr, BLACK->r, BLACK->g, BLACK->b);
    return 0;
  }
}

static void circle_text(GtkWidget *widget, cairo_t *cr, struct node* root){
  GtkWidget *win = gtk_widget_get_toplevel(widget);

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


static void drawing_recursive(cairo_t *cr, GtkWidget *widget, struct node* root){
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  int color, direction;

  color = set_color(widget, cr, root->color);

  cairo_arc(cr, 0, 0, CIRCLE_HEIGHT, 0, 2 * M_PI);
  cairo_stroke_preserve(cr);
  cairo_fill(cr);

  circle_text(widget, cr, root);


  if(root->left != NULL){
    curr_x = curr_x / 2;
    curr_y = curr_y - HEIGHT_CONSTANT*CIRCLE_HEIGHT;
    direction = 0;

    draw_line(widget, cr, direction);


    cairo_translate(cr, (int) -curr_x, (int) CIRCLE_HEIGHT * HEIGHT_CONSTANT);
    drawing_recursive(cr, widget, root->left);
    cairo_translate(cr, (int) curr_x, (int) CIRCLE_HEIGHT * -HEIGHT_CONSTANT);

    curr_x = curr_x * 2;
    curr_y = curr_y + HEIGHT_CONSTANT*CIRCLE_HEIGHT;
  }

  if(root->right != NULL){
    curr_x = curr_x / 2;
    curr_y = curr_y - HEIGHT_CONSTANT*CIRCLE_HEIGHT;
    direction = 1;

    draw_line(widget, cr, direction);

    cairo_translate(cr, (int) curr_x, (int) CIRCLE_HEIGHT * HEIGHT_CONSTANT);
    drawing_recursive(cr, widget, root->right);
    cairo_translate(cr, (int) -curr_x, (int) CIRCLE_HEIGHT * -HEIGHT_CONSTANT);
    
    curr_x = curr_x * 2;
    curr_y = curr_y + HEIGHT_CONSTANT*CIRCLE_HEIGHT;
  }

}

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  struct node* temp = ROOT;

  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  curr_x = width/2;
  curr_y = CIRCLE_HEIGHT*3;

  //Set up where we want to start with appropriate things
  cairo_translate(cr, curr_x, curr_y);
  cairo_select_font_face(cr, "Purisa",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size(cr, FONT_SIZE);
  cairo_set_line_width(cr, LINE_WIDTH);

  //Paint over any prior background
  cairo_set_source_rgb (cr, WHITE->r, WHITE->g, WHITE->b);
  cairo_paint (cr);

  drawing_recursive(cr, widget, temp);
}

//Maybe run code here, update every glob, and sleep?
//Or, more likely, update every 1000 globs
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
