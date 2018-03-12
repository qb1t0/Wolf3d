#include "includes/w3d.h"

/*
**  Function wolf_texture_choose():
**  - Choose which image for texture printing should be used
**  int type:
**  if == (0) => walls drawing
**  if == (1) => floor drawing
**  if == (2) => ceiling drawing
**
*/
int	wolf_texture_choose(t_ray *r, t_mlx *m, int type)
{
    int **map;

    map = m->map;
    if (type == 1)
        return (0);
    else if (type == 2)
        return (4);
    else if (map[r->mapx][r->mapy] && !r->side && r->rdirx > 0)
        return (2);
    else if (map[r->mapx][r->mapy] && !r->side && r->rdirx < 0)
        return (3);
    else if (map[r->mapx][r->mapy] && r->side && r->rdiry < 0)
        return (8);
    else if (map[r->mapx][r->mapy] && r->side && r->rdiry > 0)
        return (6);
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
    m->_fps = ft_itoa((int)(1.0 / (m->g.curtime- m->g.oldtime)) + 40); //;)))
    m->_score = ft_itoa(m->score);
    m->g.mspeed = (m->g.curtime - m->g.oldtime) * 5.0 * m->speed; // move speed (squares/sec)
    m->g.rspeed = (m->g.curtime - m->g.oldtime) * 4.5;            // rotation speed (radians/sec)
    if (m->fps > 0)
    {
        mlx_string_put(m->mlx, m->win, 150, 50, 0xffffff, "FPS:");
        mlx_string_put(m->mlx, m->win, 220, 50, 0xffffff, (m->_fps));
        mlx_string_put(m->mlx, m->win, 150, 90, 0xffffff, "SCORE:");
        mlx_string_put(m->mlx, m->win, 220, 90, 0xffffff, m->_score);
    }
    else
        mlx_string_put(m->mlx, m->win, 30, 50, 0xffffff, "Press [F] to show FPS and score");
    // free allocated memory by itoa():
    ft_strdel(&m->_score);
    ft_strdel(&m->_fps);
}

/*
** Function wolf_draw_texture():
** - texturing calculations
**
*/
void    wolf_draw_texture(t_mlx *m, t_ray *r, int start, int end)
{
    int    d;
    int    tnum;
    int    texy;
    int    xtex; //x coordinate on the texture

    xtex = (int)(r->wallx * (double)TWIDTH);
    if ((!r->side  && r->rdirx > 0) || (r->side == 1 && r->rdiry < 0))
        xtex = TWIDTH - xtex - 1;
    tnum = wolf_texture_choose(r, m, 0);
    while (start < end)
    {
        /*
        ** Setting colors(RGB) for each pixel in 4 bytes of f->im(char *)
        **  r->x  := x-axis coordinate
        **  start := y-axis coordinate * f->sl
        **  RGBA(4 bits x 4 blocks) color
        */
        d = start * 256 - HEIGHT * 128 + r->lheight * 128;
        texy = ((d * THEIGHT)  / r->lheight) / 256;
        m->im[r->x * m->bpp / 8 + start * m->sl] = m->get_txt[tnum][256 * texy + xtex * 4];
        m->im[r->x * m->bpp / 8 + start * m->sl + 1] = m->get_txt[tnum][256 * texy + xtex * 4 + 1];
        m->im[r->x * m->bpp / 8 + start * m->sl + 2] = m->get_txt[tnum][256 * texy + xtex * 4 + 2];
        m->im[r->x * m->bpp / 8 + start * m->sl + 3] = m->get_txt[tnum][256 * texy + xtex * 4 + 3];
        start++;
    }
}

void    wolf_draw_floor(t_mlx *m, t_ray *r, int y, int type)
{
    int tnum;
    int tx; //texture x coordinate
    int ty; //texture y coordinate

    tx = r->tfloorx;
    ty = r->tfloory;
    tnum = wolf_texture_choose(r, m, type);
    m->im[r->x * m->bpp / 8 + y * m->sl] = m->get_txt[tnum][256 * ty + tx * 4];
    m->im[r->x * m->bpp / 8 + y * m->sl + 1] = m->get_txt[tnum][256 * ty + tx * 4 + 1];
    m->im[r->x * m->bpp / 8 + y * m->sl + 2] = m->get_txt[tnum][256 * ty + tx * 4 + 2];
    m->im[r->x * m->bpp / 8 + y * m->sl + 3] = m->get_txt[tnum][256 * ty + tx * 4 + 3];
}

void    wolf_calc_floor(t_mlx *m, t_ray *r, int start, int end)
{
    double weight;
    double pdist;   //player distance
    double cdist;   //current distance

    pdist = 0;
    if (!r->side)
    {
        r->fxwall = r->rdirx > 0 ? r->mapx : r->mapx + 1.0;
        r->fywall = r->mapy + r->wallx;
    }
    else
    {
        r->fywall = r->rdiry > 0 ? r->mapy : r->mapy + 1.0;
        r->fxwall = r->mapx + r->wallx;
    }
    (end < 0) ? end = HEIGHT - 1 : 0;
    while (++end < HEIGHT)
    {
        cdist = HEIGHT / (2.0 * end - HEIGHT);
        weight = (cdist - pdist) / (r->wdist - pdist);
        r->cfloorx = weight * r->fxwall + (1.0 - weight) * r->rposx;
        r->cfloory = weight * r->fywall + (1.0 - weight) * r->rposy;
        r->tfloorx = (int)(r->cfloorx * 64) % 64;
        r->tfloory = (int)(r->cfloory * 64) % 64;
        wolf_draw_floor(m, r, end, 1); //floor draw
        wolf_draw_floor(m, r, HEIGHT - end, 2); //ceiling draw
    }
}