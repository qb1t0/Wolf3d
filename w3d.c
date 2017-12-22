#include "includes/w3d.h"

void    wolf_load_menu(t_mlx *m)
{
    m->img = mlx_new_image(m->win, WIDTH, HEIGHT);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
    mlx_do_sync(m->mlx);
}

int main (int ac, char **av)
{
    t_mlx m;

    if (ac != 1) exit(ft_printf(COL_GREEN USAGE COL_EOC));              // handles argument error

    m.sl = 0;                                                           //  \.
    m.bpp = 0;                                                          //   |  new window initializing
    m.mlx = mlx_init();                                                 //   |  by the default values
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d, (c)ysalata"); //  /

    wolf_load_menu(&m);                                                 // creates game launch menu

    mlx_mouse_hook(m.win, wolf_onmouse, &m);                            //  \.
    mlx_hook(m.win, 2, 5, wolf_onbutton, &m);                           //   |  mlx loop and hooks functions
    mlx_loop(m.mlx);                                                    //  /
}