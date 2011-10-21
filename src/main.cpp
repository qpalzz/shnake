#include "game.h"

Game *game;
guint move_timer, draw_timer;

gint glarea_button_press (GtkWidget*, GdkEventButton*);
gint glarea_draw  (GtkWidget*, GdkEventExpose*);
gint glarea_reshape  (GtkWidget*, GdkEventConfigure*);
gint glarea_init  (GtkWidget*);
gint glarea_destroy  (GtkWidget*);
gboolean key_pressed (GtkWidget *widget, GdkEvent  *event, gpointer user_data);
gboolean timeout_draving_cb(gpointer data);
gboolean timeout_moving_cb(gpointer data);
void SetProjectionMatrix(GLsizei, GLsizei);
void SetModelviewMatrix();
GtkWidget* create_menubar();
GtkWidget* create_my_menuitem(GtkWidget *menu,gchar *labelmenu,gchar *labelmenu_r,gchar *active);
void  menuitem_response (GtkMenuItem *menuitem,gpointer user_data);

int main(int, char**);

gint glarea_button_press (GtkWidget* widget, GdkEventButton* event)
{
    int x = event->x;
    int y = event->y;
    if (event->button == 1) {
        g_print ("Button 1 press   (%d, %d)\n", x, y);
        return TRUE;
    }
    if (event->button == 2) {
        g_print ("Button 2 press   (%d, %d)\n", x, y);
        return TRUE;
    }
    return FALSE;
}

gint glarea_draw (GtkWidget* widget, GdkEventExpose* event)
{
    if (event && event->count > 0) {
        return(TRUE);
    }
    if (gtk_gl_area_make_current(GTK_GL_AREA(widget))) {
        game->Draw();
        gtk_gl_area_swapbuffers (GTK_GL_AREA(widget));
    }
    return (TRUE);
}

gint glarea_reshape (GtkWidget* widget, GdkEventConfigure* event)
{
    int w = widget->allocation.width;
    int h = widget->allocation.height;
    g_print ("Reshape Event\n");
    if (gtk_gl_area_make_current (GTK_GL_AREA(widget))) {
        glViewport (0, 0, w, h);
        SetProjectionMatrix(w, h);
        SetModelviewMatrix();
    }
    return (TRUE);
}

gint glarea_init (GtkWidget* widget)
{
    g_print ("Realize Event\n");
    if (gtk_gl_area_make_current (GTK_GL_AREA(widget))) {
        srand(time(NULL));
        game = new Game();
        move_timer = g_timeout_add(120, timeout_moving_cb, widget);
        draw_timer = g_timeout_add(120/COUNT_FRAMES, timeout_draving_cb, widget);
    }
    return TRUE;
}

gint glarea_destroy (GtkWidget* widget)
{
    g_print ("GTK GL Area Destroy Event\n");

    g_source_remove(move_timer);
    g_source_remove(draw_timer);

    delete game;

    return TRUE;
}

gint key_pressed (GtkWidget *widget, GdkEvent  *event, gpointer user_data)
{
    switch (((GdkEventKey*)event)->keyval) {
        case GDK_KEY_Up: {
            game->SetDirection(DOWN);
            break;
        }
        case GDK_KEY_Down: {
            game->SetDirection(UP);
            break;
        }
        case GDK_KEY_Left: {
            game->SetDirection(LEFT);
            break;
        }
        case GDK_KEY_Right: {
            game->SetDirection(RIGHT);
            break;
        }
        case GDK_KEY_Pause: {
            game->Pause();
            break;
        }
        case GDK_KEY_Return: {
            game->Start();
            break;
        }
        case GDK_KEY_Escape: {
            game->New();
            break;
        }
    }
    return TRUE;
}

gboolean timeout_draving_cb(gpointer data)
{
    glarea_draw (GTK_WIDGET(data), NULL);
    return TRUE;
}

gboolean timeout_moving_cb(gpointer data)
{
    game->Move();
    return TRUE;
}

void SetProjectionMatrix(GLsizei width, GLsizei height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,1,-100);
}

void SetModelviewMatrix(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static GtkItemFactoryEntry menu_items[] = {
  { "/_Игра",               NULL,         NULL,           0, "<Branch>" },
  { "/Игра/_Новая игра",    "<control>N", NULL,           0, "<Item>" },
  { "/Игра/_Пауза",         "Pause",      NULL,           0, "<Item>" },
  { "/Игра/разд1",          NULL,         NULL,           0, "<Separator>" },
  { "/Игра/Результаты",     NULL,         NULL,           0, "<Item>" },
  { "/Игра/Закончить игру", NULL,         NULL,           0, "<Item>" },
  { "/Игра/разд2",          NULL,         NULL,           0, "<Separator>" },
  { "/Игра/Выход",          "<control>Q", gtk_main_quit,  0, "<Item>" },
  { "/_Правка",             NULL,         NULL,           0, "<Branch>" },
  { "/Правка/Параметры",    NULL,         NULL,           1, "<Item>" },
  { "/_Справка",            NULL,         NULL,           0, "<Branch>" },
  { "/Справка/_О программе",NULL,         NULL,           0, "<Item>" },
};
static gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

GtkWidget *get_menubar_menu( GtkWidget  *window)
{
    GtkItemFactory *item_factory;
    GtkAccelGroup *accel_group;
    /* Создаём группу акселераторов (shortcut keys) */
    accel_group = gtk_accel_group_new ();
    /* Создаём ItemFactory (строку меню) */
    item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>",
                                         accel_group);
    /* Эта функция генерирует пункты меню. Передает item factory,
     номер пункта в массиве, массив непосредственно, а также любые
     данные обратных вызовов для пунктов меню. */
    gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);
    /* Прикрепляем новую группу акселераторов к окну. */
    gtk_window_add_accel_group (GTK_WINDOW (window), accel_group);
    /* Возвращаем фактически созданную производством пунктов (item factory) панель меню. */
    return gtk_item_factory_get_widget (item_factory, "<main>");
}


// ---------------------------main()----------------------------

int main(int argc, char** argv)
{
	GtkWidget* window;
    GtkWidget* box_main;
    GtkWidget* menubar;
    GtkWidget* glarea;
    int attrlist[] = {
            GDK_GL_RGBA,
            GDK_GL_DOUBLEBUFFER,
            GDK_GL_DEPTH_SIZE, 2,
            GDK_GL_NONE
        };
    gtk_init (&argc, &argv);
    if(gdk_gl_query() == FALSE) {
        g_print("OpenGL not supported!\n");
        return (1);
    }

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window), "Shnake");
    gtk_quit_add_destroy (1, GTK_OBJECT(window));
    gtk_signal_connect (GTK_OBJECT(window), "delete_event",  G_CALLBACK(gtk_main_quit),  NULL);
    gtk_signal_connect (GTK_OBJECT (window), "destroy",   G_CALLBACK(gtk_main_quit),  NULL);
    gtk_container_set_border_width (GTK_CONTAINER(window), 5);
    gtk_widget_show (window);

    box_main = gtk_vbox_new (FALSE, 10);
    gtk_container_add (GTK_CONTAINER(window), box_main);
    gtk_widget_show (box_main);

    menubar = get_menubar_menu(window);
    gtk_box_pack_start (GTK_BOX (box_main), menubar,FALSE, TRUE, 0);
    gtk_widget_show (menubar);

    glarea = gtk_gl_area_new(attrlist);
    gtk_widget_set_events(GTK_WIDGET(glarea),
                          GDK_EXPOSURE_MASK|
                          GDK_BUTTON_PRESS_MASK);
    gtk_signal_connect (GTK_OBJECT(glarea), "button_press_event", G_CALLBACK(glarea_button_press),  NULL);
    gtk_signal_connect (GTK_OBJECT(glarea), "expose_event",  G_CALLBACK(glarea_draw),   NULL);
    gtk_signal_connect (GTK_OBJECT(glarea), "configure_event", G_CALLBACK(glarea_reshape),  NULL);
    gtk_signal_connect (GTK_OBJECT(glarea), "realize",  G_CALLBACK(glarea_init),   NULL);
    gtk_signal_connect (GTK_OBJECT(glarea), "destroy",  G_CALLBACK (glarea_destroy),  NULL);
    gtk_signal_connect (GTK_OBJECT(window), "key-press-event",  G_CALLBACK (key_pressed),  NULL);
    gtk_widget_set_usize(GTK_WIDGET(glarea), 600, 600);
    gtk_box_pack_start (GTK_BOX(box_main), glarea,      FALSE, TRUE, 0);
    gtk_widget_show (glarea);

    gtk_widget_show_all(window);

    gtk_main ();

    return (0);
}
