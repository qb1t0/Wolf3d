#include "includes/w3d.h"

/*
**  Creating menu window
*/

void    wolf_load_menu(t_mlx *m)
{
    int a,b;

    a = 1906;
    b = 1072;
    //m->img = mlx_new_image(m->win, WIDTH, HEIGHT);
//    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/rm.xpm", &a, &b); //Todo: Sould be an XPM converted image
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    //mlx_xpm_to_image(m->mlx, lol, &a, &b);
//    mlx_destroy_image(m->mlx, m->img);
//    mlx_do_sync(m->mlx);
}

/*
** Setting default game values
*/

void    wolf_load_default(t_map *g)
{
    g->oldtime = 0;
    g->curtime = 0;
    g->x_plane = 0;
    g->y_plane = 0.66;
    g->y_direct = 0;
    g->x_direct = -1;
    g->x_player = 22;
    g->y_player = 12;
}

int main (int ac, char **av)
{
    t_map g;
    t_mlx m;

    if (ac != 1) exit(ft_printf(COL_GREEN USAGE COL_EOC));              // handles argument error

    m.sl = 0;                                                           //  \|
    m.bpp = 0;                                                          //   |  new window initializing
    m.mlx = mlx_init();                                                 //   |  by the default values
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d, (c)ysalata"); //  /|

    wolf_load_menu(&m);                                                 // creates game launch menu
    wolf_load_default(&g);
    mlx_mouse_hook(m.win, wolf_onmouse, &m);                            //  \|
    mlx_hook(m.win, 2, 5, wolf_onbutton, &m);                           //   |  mlx loop and hooks functions
    mlx_loop(m.mlx);                                                    //  /|
}