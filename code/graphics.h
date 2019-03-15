#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// #include "all.h"

//Structure definitions
typedef struct {
  double r;
  double g;
  double b;
} Color;

struct {
  gushort count;
} glob;


//Constants
//TODO: Make own file?
int FONT_SIZE = 12;
int LOOP_WAIT = 500;
int WINDOW_SIZE = 1600;
int CIRCLE_HEIGHT = 35;
int LINE_WIDTH = 3;
int BRANCH_WIDTH = 7;
char* FONT = "Purisa";
double HEIGHT_CONSTANT = 4.0;
double TEXT_DISTANCE = 0.5;

//Color declarations; instantiated in Main function
Color* RED;
Color* BLACK;
Color* WHITE;

//Global variables
struct node *ROOT;
struct node *MIN;
int NUM_OF_TASKS;
int GENERATE_NEW_TASKS;

//Function declarations
Color *make_color(double r, double b, double g);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
static void do_drawing(cairo_t *cr, GtkWidget *widget);
static gboolean time_handler(GtkWidget *widget);
