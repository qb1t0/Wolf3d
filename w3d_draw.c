#include "includes/w3d.h"

/*
** Setting colors(RGB) for each pixel in 4 bytes of f->im(char *)
**  f := mlx struct
**  x := x-axis coordinate * f->bpp / 8
**  y := y-axis coordinate * f->sl
**  c := RGBA(4 bits x 4 blocks) color
*/

void	wolf_pixel_draw(t_mlx *m, t_ray *r, int x, int y)
{
    int c;

    c = 0xFFFFFF;
    if (map[r->mapx][r->mapy] == 1)
        c = 0x05e2f4;
    else if (map[r->mapx][r->mapy] == 2)
        c = 0x00ff5e;
    else if (map[r->mapx][r->mapy] == 3)
        c = 0xffb709;
    m->im[x + y] = (char)(c);
    m->im[x + y + 1] = (char)(c >> 8);
    m->im[x + y + 2] = (char)(c >> 16);
}

/*
** Function wolf_draw_info():
**  - drawing info bar in-game mode, those consist of:
**  a) FPS;
**  b) Score;
*/

void    wolf_draw_info(t_mlx *m)
{
    m->g.oldtime = m->g.curtime;
    m->g.curtime = clock();
    m->g.curtime /= CLOCKS_PER_SEC;
    m->_fps = ft_itoa((1.0 / (m->g.curtime- m->g.oldtime)));
    m->_score = ft_itoa(m->score);
    m->g.mspeed = (m->g.curtime - m->g.oldtime) * 5.0; // move speed (squares/sec)
    m->g.rspeed = (m->g.curtime - m->g.oldtime) * 3.0; // rotation speed (radians/sec)
    mlx_string_put(m->mlx, m->win, 700, 0, 0x000000, "fps:");
    mlx_string_put(m->mlx, m->win, 760, 0, 0x000000, m->_fps);
    mlx_string_put(m->mlx, m->win, 700, 50, 0x000000, "score:");
    mlx_string_put(m->mlx, m->win, 760, 50, 0x000000, m->_score);
    // free allocated memory by itoa():
    ft_strdel(&m->_score);
    ft_strdel(&m->_fps);
}

/*
** Calculating && Initializing delta's for Bresemham's algorithm
*/

void	wolf_delta_init(t_bres *f, int end, int start, int x)
{
    f->dx = 0;
    f->dy = end - start;
    f->incr_x = f->dx > 0 ? 1 : -1;
    f->incr_y = f->dy > 0 ? 1 : -1;
    f->dx = abs(f->dx);
    f->dy = abs(f->dy);
    if (f->dx > f->dy)
    {
        f->_incr_x = f->incr_x;
        f->_incr_y = 0;
        f->dh = f->dx;
        f->de = f->dy;
    }
    else
    {
        f->_incr_x = 0;
        f->_incr_y = f->incr_y;
        f->dh = f->dy;
        f->de = f->dx;
    }
    f->x = x;
    f->y = start;
    f->e = f->dh / 2;
}

/*
** Bresenham's drawing line algorithm implementation:
*/

void	wolf_bresenhem(t_mlx *m, t_ray *r, int x, int layer)
{
    int     k;
    t_bres  a;

    k = -1;
    wolf_delta_init(&a, r->edraw, r->sdraw, x);
    wolf_pixel_draw(m, r, a.x * m->bpp / 8, a.y * m->sl);
    while (++k < a.dh)
    {
        a.e -= a.de;
        if (a.e < 0)
        {
            a.e += a.dh;
            a.x += a.incr_x;
            a.y += a.incr_y;
        }
        else
        {
            a.x += a._incr_x;
            a.y += a._incr_y;
        }
        wolf_pixel_draw(m, r, a.x * m->bpp / 8, a.y * m->sl);
    }
//    a.x = x;
//    a.y = r->edraw;
//    a.dh = r->sdraw - r->edraw;
//    wolf_pixel_draw(m, r, a.x * m->bpp / 8, a.y * m->sl);
//    while (++k < a.dh)
//    {
//        ++a.y;
//        wolf_pixel_draw(m, r, a.x * m->bpp / 8, a.y * m->sl);
//    }
}