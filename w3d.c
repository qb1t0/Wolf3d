#include "includes/w3d.h"



/*
** Opening settings menu
*/

void    wolf_load_settings(t_mlx *m, int type)
{
    int a,b;

    a = 1280;
    b = 960;
    mlx_clear_window(m->mlx, m->win); //clear previous image
    if (type)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/control.xpm", &a, &b);
    else
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/setings.xpm", &a, &b);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_do_sync(m->mlx);
}

/*
**  Creating menu window
*/

void    wolf_load_menu(t_mlx *m)
{
    int a,b;

    a = 1280;
    b = 960;
    if (m->game)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuon.xpm", &a, &b);
    else
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuoff.xpm", &a, &b);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    //mlx_xpm_to_image(m->mlx, lol, &a, &b);
    //mlx_destroy_image(m->mlx, m->img);
    mlx_do_sync(m->mlx);
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
    //todO: run main algorithm from here
}

int main (int ac, char **av)
{
    t_map g;
    t_mlx m;

    if (ac != 1) exit(ft_printf(COL_GREEN USAGE COL_EOC));              // handles argument error

    m.type = 0;
    m.game = 0;                                                         // in-game mode: OFF
    m.mus = 0;                                                          // music default: ON
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