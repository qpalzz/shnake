#include "config.h"

Config *Config::_self = NULL;

Config::Config()
{
    g_print("Config::Config()\n");
    LoadConfig(CONFIG_NAME);
}

Config::~Config()
{
    g_print("Config::~Config\n");
}

Config *Config::Instance()
{
    if(!_self) _self = new Config();
    return _self;
}

void Config::FreeInst()
{
    delete this;
    _self=NULL;
}

void Config::SaveConfig(const gchar *filename)
{
    if (load) {
        GError *error;
        gchar *str_data;
        gsize len;

        GKeyFile *file = g_key_file_new();
        g_key_file_set_double(file,"display","cell_width",cell_width);
        g_key_file_set_double(file,"display","radius",radius);
        g_key_file_set_double(file,"display","radius_start",radius_start);
        g_key_file_set_integer(file,"display","step_time",(gint)step_time);

        g_key_file_set_double_list(file,"clean","color_fill",clean_color_fill,4);
        g_key_file_set_double_list(file,"clean","color_border",clean_color_border,4);

        g_key_file_set_double_list(file,"tail","color_fill",tail_color_fill,4);
        g_key_file_set_double_list(file,"tail","color_border",tail_color_border,4);

        g_key_file_set_double_list(file,"point","color_fill",point_color_fill,4);
        g_key_file_set_double_list(file,"point","color_border",point_color_border,4);

        g_key_file_set_double_list(file,"over","color_fill",over_color_fill,4);
        g_key_file_set_double_list(file,"over","color_border",over_color_border,4);

        str_data = g_key_file_to_data(file, &len, &error);

        g_file_set_contents(filename, str_data, len, NULL);
        g_free (str_data);
        g_key_file_free(file);
    }
}

void Config::LoadConfig(const gchar *filename)
{
    GError *error;
    gsize len = 4;

    GKeyFile *file = g_key_file_new();
    g_key_file_load_from_file(file,filename,G_KEY_FILE_KEEP_COMMENTS,&error);

    cell_width = g_key_file_get_double(file,"display","cell_width",&error);
    radius = g_key_file_get_double(file,"display","radius",&error);
    radius_start = g_key_file_get_double(file,"display","radius_start",&error);
    step_time = (guint)g_key_file_get_integer(file,"display","step_time",&error);

    clean_color_fill = g_key_file_get_double_list(file,"clean","color_fill",&len,&error);
    clean_color_border = g_key_file_get_double_list(file,"clean","color_border",&len,&error);

    tail_color_fill = g_key_file_get_double_list(file,"tail","color_fill",&len,&error);
    tail_color_border = g_key_file_get_double_list(file,"tail","color_border",&len,&error);

    point_color_fill = g_key_file_get_double_list(file,"point","color_fill",&len,&error);
    point_color_border = g_key_file_get_double_list(file,"point","color_border",&len,&error);

    over_color_fill = g_key_file_get_double_list(file,"over","color_fill",&len,&error);
    over_color_border = g_key_file_get_double_list(file,"over","color_border",&len,&error);
}
