#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

# define N 4                // threads number
# define HEIGHT 1440        // window height
# define WIDTH 2560         // window width
# define USAGE "[usage]:\t./wolf3d"

/*
**  Struct s_mlx uses for collecting data from mlx functions
**  Variables needed by the mlx library functions
**  void		    *mlx;   // mlx process pointer
**  void		    *win;   // mlx->window pointer
**  void		    *img;   // mlx->image pointer
**  char		    *im;    // mlx->image pixel array
**  int			    bpp;    // mlx->bits per pixel
**  int             end;    // mlx->endian type
**  int			    sl;     // mlx->sl
**  int             c;      // color variable
**  int             mus;    // music variable ( ? on : off)
**  int             part;   // 1/4 part of window for threads
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
}                   t_mlx;

/*
** Function wolf_pixel_draw():
** Puts pixel m->color(int, RGBA) in pixel array m->im(char *)
*/

void	wolf_pixel_draw(t_mlx *f, int x, int y, int c);

/*
** Functions wolf_onbutton(), wolf_onmouse():
** Those functions processes intercepts of all mouse- || button- events.
*/

int     wolf_onbutton(int button, t_mlx *m);
int     wolf_onmouse(int b, int x, int y, t_mlx *m);

/*
** Function wolf_load_menu():
** Creates starting page in new widow with game menu.
*/

void    wolf_load_menu(t_mlx *m);

#endif //WOLF3D