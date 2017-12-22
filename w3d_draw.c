#include "includes/w3d.h"

/*
** Setting colors(RGB) for each pixel in 4 bytes of f->im(char *)
**  f := mlx struct
**  x := x-axis coordinate * f->bpp / 8
**  y := y-axis coordinate * f->sl
**  c := RGBA(4 bits x 4 blocks) color
*/

void	wolf_pixel_draw(t_mlx *f, int x, int y, int c)
{
    f->im[x + y] = (char) (c);
    f->im[x + y + 1] = (char) (c >> 8);
    f->im[x + y + 2] = (char)(c >> 16);
}