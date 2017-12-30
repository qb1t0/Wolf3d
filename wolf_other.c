#include "includes/w3d.h"

void    wolf_settings_add(t_mlx *m)
{
    if (m->mus)
    {
        mlx_string_put(m->mlx, m->win, 365, 347, 0xFFFFFF, "ON");
        mlx_string_put(m->mlx, m->win, 400, 347, 0x929fad, "OFF");
    }
    else
    {
        mlx_string_put(m->mlx, m->win, 365, 347, 0x929fad, "ON");
        mlx_string_put(m->mlx, m->win, 400, 347, 0xFFFFFF, "OFF");
    }
    if (m->speed == 1)
    {
        mlx_string_put(m->mlx, m->win, 490, 425, 0xFFFFFF, "-  x1  +");
        mlx_string_put(m->mlx, m->win, 500, 440, 0x7f0000, "(hard)");
    }
    else if (m->speed == 2)
    {
        mlx_string_put(m->mlx, m->win, 490, 425, 0xFFFFFF, "-  x2  +");
        mlx_string_put(m->mlx, m->win, 489, 440, 0xffc04c, "(normal)");
    }
    else
    {
        mlx_string_put(m->mlx, m->win, 490, 425, 0xFFFFFF, "-  x3  +");
        mlx_string_put(m->mlx, m->win, 500, 440, 0xcc840, "(easy)");
    }
}