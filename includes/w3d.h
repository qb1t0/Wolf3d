#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

# define N 4                /* threads number   */
# define HEIGHT 960         /* window height    */
# define WIDTH 1280         /* window width     */
# define MHEIGHT 24         /* map height       */
# define MWIDTH 24          /* map width        */
# define USAGE "[usage]:\t./wolf3d"

/*
** Game's map representation
** _______________________________________________________________________
**                                                                        ø
**  Each array element equal to wall in game                              ø
** _______________________________________________________________________ø
*/

static short          map[MHEIGHT][MWIDTH] = {
        {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
        {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
        {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
        {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
        {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
        {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
        {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
        {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
        {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
        {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
        {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
        {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
        {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
        {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
        {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
        {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
        {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
        {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
        {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

/*
**  Structure s_ray represents ray-casting variables
** _______________________________________________________________________
**                                                                        ø
**  xcam  +== || X-coordinate on the camera plane,                        ø
**      that the current x-coordinate of the screen represents            ø
**                                                                        ø
**  rposx +==\\                                                           ø
**            || Ray position, (default: equal player position)           ø
**  rposy +==//                                                           ø
**                                                                        ø
**  rdirx +==\\                                                           ø
**            || The direction of the ray. Calculates as:                 ø
**            || The sum of the dir vector, and a part of the             ø
**            || the plane vector.                                        ø
**  rdiry +==//                                                           ø
**                                                                        ø
**  mapx  +==\\                                                           ø
**            || The current square of the map the ray is in.             ø
**  mapy  +==//                                                           ø
** ______________________________________________________________________ ø
*/

typedef struct      s_ray{
    double          xcam;
    double          rposx;
    double          rposy;
    double          rdirx;
    double          rdiry;
    double          distx;
    double          disty;
    double          _distx;
    double          _disty;
    int             mapx;
    int             mapy;
}                   t_ray;

/*
** Structure s_map uses for configuring game variables:
** _______________________________________________________________________
**                                                                        ø
**  x_plane;    +==\\                                                     ø
**                  || The camera plane of the player.                    ø
**  y_plane;    +==//                                                     ø
**                                                                        ø
**  x_player;   +==\\                                                     ø
**                  || Represent the position vector of the player.       ø
**  y_player;   +==//                                                     ø
**                                                                        ø
**  x_direct;   +==\\                                                     ø
**                  || Represent the direction of the player.             ø
**  y_direct;   +==//                                                     ø
**                                                                        ø
**  oldtime;    +==\\                                                     ø
**                  || Used to store the time of the current              ø
**                  || and the previous frame for the FPS counter.        ø
**  curtime;    +==//                                                     ø
** _______________________________________________________________________ø
*/

typedef struct      s_map{
    double          x_player;
    double          y_player;
    double          x_plane;
    double          y_plane;
    double          x_direct;
    double          y_direct;
    float           oldtime;
    float           curtime;
}                   t_map;

/*
**  Structure s_mlx uses for collecting data from mlx functions
**  Variables needed by the mlx library functions
** _______________________________________________________________________
**                                                                        ø
**  *mlx;   +==))   mlx process pointer                                   ø
**  *win;   +==))   mlx->window pointer                                   ø
**  *img;   +==))   mlx->image pointer                                    ø
**  *im;    +==))   mlx->image pixel array                                ø
**  bpp;    +==))   mlx->bits per pixel                                   ø
**  end;    +==))   mlx->endian type                                      ø
**  sl;     +==))   mlx->sl                                               ø
**  c;      +==))   color variable                                        ø
**  mus;    +==))   music variable ( ? on : off)                          ø
**  part;   +==))   1/4 part of window for threads                        ø
**  game;   +==))   if game was started                                   ø
** _______________________________________________________________________ø
*/

typedef struct      s_mlx{
    void		    *mlx;
    void		    *win;
    void		    *img;
    char		    *im;
    int			    bpp;
    int             end;
    int			    sl;
    int             c;
    int             mus;
    int             part;
    int             type;
    int             game;
}                   t_mlx;

/*
** Function wolf_pixel_draw():
** _______________________________________________________________________
**                                                                        ø
** Puts pixel m->color(int, RGBA) in pixel array m->im(char *)            ø
** _______________________________________________________________________ø
*/

void	wolf_pixel_draw(t_mlx *f, int x, int y, int c);

/*
** Functions wolf_onbutton(), wolf_onmouse():
** _______________________________________________________________________
**                                                                        ø
** Those functions processes intercepts of all mouse- || button- events.  ø
** _______________________________________________________________________ø
*/

int     wolf_onbutton(int button, t_mlx *m);
int     wolf_onmouse(int b, int x, int y, t_mlx *m);

/*
** Function wolf_load_menu():
** _______________________________________________________________________
**                                                                        ø
** Creates starting page in new widow with game menu.                     ø
** _______________________________________________________________________ø
*/
void    wolf_load_game(t_mlx *m);
void    wolf_load_menu(t_mlx *m);
void    wolf_load_default(t_map *g);
void    wolf_load_settings(t_mlx *m, int type);

#endif //WOLF3D