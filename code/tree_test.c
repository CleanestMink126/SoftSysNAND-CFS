#include "all.h"
#include "vis.h"

//TODO: pop out into separate file
typedef struct {
  double r;
  double g;
  double b;
} Color;

Color *make_color(double r, double b, double g){
  Color *c = malloc(sizeof(Color));
  c->r = r;
  c->g = g;
  c->b = b;
  return c;
}

int FONT_SIZE = 13;
int LOOP_WAIT = 500;
int WINDOW_SIZE = 1500;
int circle_height = 35;
int count = 0;
int curr_number = 0;

static void do_drawing(cairo_t *, GtkWidget *);



struct {
  gushort count;
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
  do_drawing(cr, widget);

  return FALSE;
}

static void drawing_recursive(cairo_t *cr, GtkWidget *widget){
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  cairo_translate(cr, -2*circle_height, -2*circle_height);

}

/*
  NOTES:
  Cairo always saves last drawing point; need to be at the desired root location going into each drawing drawing_recursive
  IT's a standard divide/conquer strategy?
*/

static void do_drawing(cairo_t *cr, GtkWidget *widget) {
  GtkWidget *win = gtk_widget_get_toplevel(widget);
  Color *red = make_color(0.69, 0.19, 0.0);
  Color *black = make_color(0.0, 0.0, 0.0);

  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  cairo_translate(cr, width/2, circle_height + 5);

  cairo_select_font_face(cr, "Purisa",
      CAIRO_FONT_SLANT_NORMAL,
      CAIRO_FONT_WEIGHT_BOLD);

  cairo_set_font_size(cr, FONT_SIZE);

  gint i = 0;
  for (i = 0; i < 5; i++) {
      cairo_set_line_width(cr, 3);

      // Circle
      cairo_set_source_rgb(cr, red->r, red->g, red->b);
      cairo_translate(cr, (int) circle_height * 1.5, (int) circle_height * 1.5);
      cairo_arc(cr, 0, 0, circle_height, 0, 2 * M_PI);
      cairo_stroke_preserve(cr);

      cairo_fill(cr);

      //Text
      cairo_set_source_rgb(cr, black->r, black->g, black->b);
      char str[10];
      sprintf(str, "%d", curr_number);
      cairo_show_text(cr, str);
      cairo_fill(cr);
      cairo_translate(cr, 0, FONT_SIZE);
      cairo_show_text(cr, "41");
      cairo_translate(cr, 0, -FONT_SIZE);
      cairo_fill(cr);
      curr_number++;

      // drawing_recursive(cr, widget);
      // cairo_move_to(cr, 0.0, -10.0);
      // cairo_line_to(cr, 0.0, -40.0);
      // cairo_rotate(cr, M_PI/4);
      //
      // cairo_stroke(cr);
  }
}

//Maybe run code here, update every glob, and sleep?
//Or, more likely, update every 1000 globs
static gboolean time_handler(GtkWidget *widget)
{
  glob.count += 1;
  gtk_widget_queue_draw(widget);
  // sleep(1);

  return TRUE;
}

int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  glob.count = 0;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_title(GTK_WINDOW(window), "Waiting demo");

  g_timeout_add(LOOP_WAIT, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);

  gtk_main();
  printf("Sup?");
  return 0;
}
