#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "defs.h"

class Config {
    private:
        static Config *_self;
        bool load;
    protected:
        Config();
        ~Config();
        void LoadConfig(const gchar*);
    public:
        static Config *Instance();
        void FreeInst();
        void SaveConfig(const gchar*);

        // [display]
        double cell_width;
        double radius;
        double radius_start;
        guint step_time;

        // [clear]
        double *clean_color_fill;
        double *clean_color_border;

        // [tail]
        double *tail_color_fill;
        double *tail_color_border;

        // [point]
        double *point_color_fill;
        double *point_color_border;

        // [over]
        double *over_color_fill;
        double *over_color_border;
};

#endif // CONFIG_H_INCLUDED
