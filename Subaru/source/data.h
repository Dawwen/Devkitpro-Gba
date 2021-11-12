#ifndef DATA_H
#define DATA_H

#include "toolbox.h"

struct s_sprite_data {
    int X;
    int Y;
    int atlas_length;
    int ani_length;
    int palet_length;
    uint16 data[];
} __attribute__((__packed__));

typedef struct s_sprite_data t_sprite_data;

#endif