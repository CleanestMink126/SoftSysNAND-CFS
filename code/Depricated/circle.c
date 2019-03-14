#include "all.h"
#include "vis.h"

static void do_drawing(cairo_t *, GtkWidget *);

int WINDOW_SIZE = 1500;
int circle_height = 35;

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
    gpointer user_data)
{
  do_drawing(cr, widget);

  return FALSE;
}

static void do_drawing(cairo_t *cr, GtkWidget *widget)
{
  GtkWidget *win = gtk_widget_get_toplevel(widget);

  int width, height;

  gtk_window_get_size(GTK_WINDOW(win), &width, &height);

  cairo_set_line_width(cr, 3);
  // cairo_set_source_rgb(cr, 0.69, 0.19, 0);

  cairo_translate(cr, width/2, height/2);
  cairo_arc(cr, 0, 0, circle_height, 0, 2 * M_PI);
  cairo_stroke_preserve(cr);

  cairo_set_source_rgb(cr, 0.69, 0.19, 0);
  cairo_fill(cr);
}


int main (int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(window), darea);

  g_signal_connect(G_OBJECT(darea), "draw",
      G_CALLBACK(on_draw_event), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_SIZE, WINDOW_SIZE);
  gtk_window_set_title(GTK_WINDOW(window), "Fill & stroke");

  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}
