#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// #include "all.h"

//Structure definitions

struct {
  gushort count;
} glob;


//Constants
int MODE;
int FONT_SIZE;
int LOOP_WAIT;
int WINDOW_SIZE;
int CIRCLE_HEIGHT;
int LINE_WIDTH;
int BRANCH_WIDTH;
char* FONT;
double HEIGHT_CONSTANT;
double TEXT_DISTANCE;
double MEAN_ALLOT;
double STD_ALLOT;



//Color declarations; instantiated in Main function
double RED[3];
double BLACK[3];
double WHITE[3];

//Global variables
struct node *ROOT;
struct node *MIN;
int NUM_OF_TASKS;
int GENERATE_NEW_TASKS;
double MAX_VTIME;




// Function declarations
gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
void do_drawing(cairo_t *cr, GtkWidget *widget);
gboolean time_handler(GtkWidget *widget);
