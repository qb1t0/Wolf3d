#include "includes/w3d.h"
//http://lodev.org/cgtutor/raycasting.html

/*
** Opening settings menu
*/

void    wolf_load_settings(t_mlx *m, int type)
{
    int a,b;

    a = 1280;
    b = 960;
    mlx_clear_window(m->mlx, m->win); //clear previous image
    m->type = type;                   //redefining global type
    if (type == 3)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/control.xpm", &a, &b);
    else
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/setings.xpm", &a, &b);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
    if (type == 2)
        wolf_settings_add(m);

}

/*
**  Creating MAIN STARTING MENU window
*/

void    wolf_load_menu(t_mlx *m)
{
    int a,b;

    b = 960;
    a = 1280;
    if (m->type == 1)
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuon.xpm", &a, &b);
    else
        m->img = mlx_xpm_file_to_image(m->mlx, "../pictures/menuoff.xpm", &a, &b);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    mlx_destroy_image(m->mlx, m->img);
}

/*
** Setting default game values
** P.S: Runs, when New game starts
*/

void    wolf_load_default(t_mlx *m)
{
    t_map   g;

    mlx_clear_window(m->mlx, m->win); //clear previous image
    mlx_do_sync(m->mlx);
    m->img = mlx_new_image(m->win, WIDTH, HEIGHT + 1);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    m->score = 0;
    g.oldtime = 0;                                                  // previous frame time
    g.curtime = 0;                                                  // current frame time
    g.x_plane = 0;                                                  // 2d raycaster of camera plane
    g.y_plane = 0.66;                                               //     -//-
    g.y_direct = 0;                                                 // direct vector
    g.x_direct = -1;                                                //     -//-
    g.x_player = 22;                                                // x start position
    g.y_player = 12;                                                // y start position
    m->g = g;
    wolf_load_game(m, 0);                                               // 0 - starting x-coordinate
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
}


/*
** Main program function here
** - Declaring main mlx struct: t_mlx *m;
** - Loads default data in structure values
*/

int main (int ac, char **av)
{
    t_mlx m;

    if (ac != 1) exit(ft_printf(COL_GREEN USAGE COL_EOC));              // handles argument error
    m.speed = 1;                                                        // player speed (game complexity)
    m.type = 0;                                                         // set window-default type value
    m.game = 0;                                                         // DEFAULT: in-game mode: OFF
    m.mus = 1;                                                          // DEFAULT: music: ON
    m.sl = 0;                                                           //  \|
    m.bpp = 0;                                                          //   |  new window initializing
    m.mlx = mlx_init();                                                 //   |  by the default values
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d, (c)ysalata"); //  /|

    wolf_load_menu(&m);                                                 // creates game launch menu
    mlx_mouse_hook(m.win, wolf_onmouse, &m);                            //  \|
    mlx_hook(m.win, 2, 5, wolf_onbutton, &m);                           //   |  mlx loop and hooks functions
    mlx_loop(m.mlx);                                                    //  /|
}