#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>

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

Color *red = make_color(0.69, 0.19, 0);
int WINDOW_SIZE = 1500;
int circle_height = 35;
int count = 0;

static void do_drawing(cairo_t *, GtkWidget *);

struct {
  gushort count;
} glob;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
    gpointer user_data)
{
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  static gdouble const trs[8][8] = {
      { 0.0, 0.15, 0.30, 0.5, 0.65, 0.80, 0.9, 1.0 },
      { 1.0, 0.0,  0.15, 0.30, 0.5, 0.65, 0.8, 0.9 },
      { 0.9, 1.0,  0.0,  0.15, 0.3, 0.5, 0.65, 0.8 },
      { 0.8, 0.9,  1.0,  0.0,  0.15, 0.3, 0.5, 0.65},
      { 0.65, 0.8, 0.9,  1.0,  0.0,  0.15, 0.3, 0.5 },
      { 0.5, 0.65, 0.8, 0.9, 1.0,  0.0,  0.15, 0.3 },
      { 0.3, 0.5, 0.65, 0.8, 0.9, 1.0,  0.0,  0.15 },
      { 0.15, 0.3, 0.5, 0.65, 0.8, 0.9, 1.0,  0.0, }
  };

  GtkWidget *win = gtk_widget_get_toplevel(widget);

  gint width, height;
  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  cairo_translate(cr, width/2, circle_height + 5);

  gint i = 0;
  for (i = 0; i < glob.count; i++) {
      cairo_translate(cr, (int) circle_height * 1.5, (int) circle_height * 1.5);
      cairo_set_line_width(cr, 3);

      cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
      cairo_set_source_rgba(cr, red->r, red->g, red->b);

      cairo_arc(cr, 0, 0, circle_height, 0, 2 * M_PI);
      cairo_stroke_preserve(cr);

      cairo_set_source_rgb(cr, 0.69, 0.19, 0);
      cairo_fill(cr);

      // cairo_move_to(cr, 0.0, -10.0);
      // cairo_line_to(cr, 0.0, -40.0);
      // cairo_rotate(cr, M_PI/4);
      //
      // cairo_stroke(cr);
  }
}




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

  glob.count = 0;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);

  g_signal_connect(G_OBJECT(darea), "draw",
      G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_title(GTK_WINDOW(window), "Waiting demo");

  g_timeout_add(100, (GSourceFunc) time_handler, (gpointer) window);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
