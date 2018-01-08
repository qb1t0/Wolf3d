#include "includes/w3d.h"
//http://lodev.org/cgtutor/raycasting.html

/*
** Function wolf_load_default():
**  - Setting default game values and running the game window
*/

void    wolf_load_default(t_mlx *m)
{
    t_map   g;

//    mlx_clear_window(m->mlx, m->win);                               // clear previous image
//    m->img = mlx_new_image(m->win, WIDTH, HEIGHT + 1);              // creating new image
//    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);    // gets data addr
    g.score = 0;                                                    // player default score
    g.oldtime = 0;                                                  // previous frame time
    g.curtime = 0;                                                  // current frame time
    g.x_plane = 0;                                                  // default camera x-plane
    g.y_plane = 0.66;                                               // default camera y-plane
    g.y_direct = 0;                                                 // default direct x-vector
    g.x_direct = -1;                                                // default direct y-vector
    g.x_player = 22;                                                // default start x-position
    g.y_player = 12;                                                // default start y-position
    m->g = g;                                                       // saving struct data in m->g
    wolf_load_game(m, 0);                                           // starts new game
}


/*
** Main program function here
** - Declaring main mlx struct: t_mlx *m
** - Loads default data in structure values && start game
** - Starting mlx hooks and loops
*/

int main (int ac, char **av)
{
    t_mlx m;

    if (ac != 1) exit(ft_printf(COL_GREEN USAGE COL_EOC));              //  handles argument error
    m.mus = 1;                                                          //  default music: on
    m.bpp = 0;
    m.sl = 0;
    m.type = 0;                                                         //  default window: menu
    m.game = 0;                                                         //  default in-game mode: off
    m.speed = 0;                                                        //  default speed: x0 (game complexity : hard)
    m.width = WIDTH;                                                    //  saving window width
    m.height = HEIGHT;                                                  //  saving window height
    m.mlx = mlx_init();                                                 //  mlx initializing
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d, (c)ysalata"); //  creating new mlx_window
    wolf_load_menu(&m);                                                 //  loading game launch menu
    mlx_mouse_hook(m.win, wolf_onmouse, &m);                            //  mlx_hook for mouse events
    mlx_hook(m.win, 2, 5, wolf_onbutton, &m);                           //  mlx_hook for keyboard events
    mlx_loop(m.mlx);                                                    //  mlx_loop for infinite window loop
}