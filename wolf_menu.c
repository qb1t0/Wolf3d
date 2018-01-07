#include "includes/w3d.h"

/*
** Function wolf_settings_add():
**  - Puts data fields in settings sub-menu
*/

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

/*
** Function wolf_load_submenu():
**  - Opening sub-menu with settings
**  - if type == 3 then load "Control panel" menu window
**  else load "Settings" menu window
*/

void    wolf_load_submenu(t_mlx *m, int type)
{
    m->type = type; //redefining global type in structure
    if (type == 3)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/control.xpm", &m->width, &m->height);
    else
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/setings.xpm", &m->width, &m->height);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
    if (type == 2)
        wolf_settings_add(m);
}

/*
** Function wolf_load_menu():
**  - Loading main menu window
**  - if type == 0 then load menu without "Resume game" button
**  - else load menu with "Resume game" button
*/

void    wolf_load_menu(t_mlx *m)
{
    mlx_clear_window(m->mlx, m->win); //clear previous image
    if (m->type == 1)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuon.xpm", &m->width, &m->height);
    else if (!m->type)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuoff.xpm", &m->width, &m->height);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
}

