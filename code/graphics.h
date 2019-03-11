#include "all.h"
#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double r;
  double g;
  double b;
} Color;

struct {
  gushort count;
} glob;

int FONT_SIZE = 15;
int LOOP_WAIT = 5000;
int WINDOW_SIZE = 1500;
int CIRCLE_HEIGHT = 45;
int LINE_WIDTH = 3;
Color* RED;
Color* BLACK;
struct node *ROOT;

Color *make_color(double r, double b, double g);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
static void do_drawing(cairo_t *cr, GtkWidget *widget);
static gboolean time_handler(GtkWidget *widget);
int main(int argc, char *argv[]);
