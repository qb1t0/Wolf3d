#include "includes/w3d.h"


/*
** Function wolf_exit_game():
**  - Ending music playing
**  - Uses exit() to end the program
*/

void    wolf_exit_game(int code)
{
    if (!code)
        return ;
    system("killall afplay &>/dev/null"); //stops the music playing
    exit(42);
}

/*
** Function wolf_create_name():
**  - Creates path for an image
**  - Takes int n as image index and folder path
*/
char    *wolf_create_name(int n, char *path)
{
    char *s;

    s = (char *)malloc(40); // memory allocating for new string
    strcpy(s, path);        // 1. copy path to folder with or pictures
    strcat(s, ft_itoa(n));  // 2. concatinates path string with image index
    return (s);             // new very nice string returns ^ ___ ^
}

/*
** Function wolf_load_default():
**  - Setting default game values and running the game window
*/

void    wolf_load_default(t_mlx *m)
{
    int     i;
    t_map   g;
    char    *path;

    i = -1;
    g.oldtime = 0;                                                  // previous frame time
    g.curtime = 0;                                                  // current frame time
    g.x_plane = -0.2;                                               // default camera x-plane
    g.y_plane = 1;                                                  // default camera y-plane
    g.y_direct = 0;                                                 // default direct x-vector
    g.x_direct = -0.4;                                              // default direct y-vector
    g.x_player = m->xplayer + 0.5;                                  // default start x-position
    g.y_player = m->yplayer + 0.5;                                  // default start y-position
    m->g = g;                                                       // saving struct data in m->g
    m->fps = 1;                                                     // defining fps counter
    m->exp_x = WIDTH / 2;                                           // default player aim
    while (++i <= 8)                                                // init walls
    {
        path = wolf_create_name(i, WALLS_PATH);
        m->pic_txt[i] = mlx_xpm_file_to_image(m->mlx, path, &m->width, &m->height);
        m->get_txt[i] = mlx_get_data_addr(m->pic_txt[i], &m->bpp, &m->sl, &m->end);
        ft_strdel(&path);
    }
}


int wolf_main_loop(t_mlx *m)
{
    mlx_do_sync(m->mlx);
    mlx_clear_window(m->mlx, m->win);

    if ((int)m->introframe <= 44)
        wolf_intro_here(m);
    else if (m->game == 1)
        wolf_load_game(m, 0);
    else if (m->type == 0 || m->type == 1)
        wolf_load_menu(m);
    else if (m->type == 2 || m->type == 3)
        wolf_load_submenu(m, m->type);
}

/*
** Main program function here
** - Declaring main mlx struct: t_mlx *m
** - Loads default data in structure values && start game
** - Starting mlx hooks and loops
*/

int main(int ac, char **av)
{
    t_mlx m;
    if (ac != 2) exit(ft_printf(COL_GREEN USAGE COL_EOC));             //  handles argument error
    m.map = wolf_map_open(av[1], &m);
    m.mus = 1;                                                          //  default music: on
    m.bpp = 0;
    m.sl = 0;
    m.type = 0;                                                         //  default window: menu
    m.game = 0;                                                         //  default in-game mode: off
    m.speed = 3;                                                        //  default speed: x0 (game complexity : hard)
    m.width = WIDTH;                                                    //  saving window width
    m.height = HEIGHT;                                                  //  saving window height
    m.mlx = mlx_init();                                                 //  mlx initializing
    m.win = mlx_new_window(m.mlx, WIDTH, HEIGHT, "wolf3d, (c)ysalata"); //  creating new mlx_window
    wolf_load_intro(&m);
    wolf_menugifs_init(&m, -1);
    mlx_mouse_hook(m.win, wolf_onmouse, &m);                            //  mlx_hook for mouse events
    mlx_hook(m.win, 6, 64, wolf_mouse_expose, &m);                      //  mlx_hook for mouse events
    mlx_hook(m.win, 2, 5, wolf_onbutton, &m);                           //  mlx_hook for keyboard events
    mlx_loop_hook(m.mlx, wolf_main_loop, &m);
    mlx_loop(m.mlx);                                                    //  mlx_loop for infinite window loop
}