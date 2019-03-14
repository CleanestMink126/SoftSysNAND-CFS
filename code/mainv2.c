#include "all.h"
#include "graphicsv2.c"

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

  //Helpful stuff for timing
  srand(time(0));
  time_t end, start;
  time_t seconds = 10; // end loop after this time has elapsed
  struct timespec tim;
  tim.tv_sec = 0;
  tim.tv_nsec = 100000000L;
  end = start + seconds;
  printf("processing activated at %s", ctime(&start));
  //Helpful stuff for red black trees
  NUM_OF_TASKS = 0;
  struct node *root = NULL;
  // struct node *min = NULL;
  struct node* n;
  int starting_tasks = 12;
  GENERATE_NEW_TASKS = 0;


  //-----------Generate tasks------------
  for(int i = 0; i < starting_tasks; i++){
    n = generate_task(NUM_OF_TASKS, 0);
    insert(&root, &MIN, n);
    NUM_OF_TASKS++;
  }

  ROOT = root;

  gtk_main();


    printf("end time is %s", ctime(&end));


    return 0;
}
