#include "includes/w3d.h"

/*
** Function wolf_load_image():
** - calculate the height of the line, that has to be drawn on screen
 * - call drawing algorithm
*/
//Todo: write drawing func call here(to bresenhem)

void    wolf_load_image(t_mlx *m, t_ray *r, int x)
{
    int lheight;    //line height

    lheight = (int)(HEIGHT / r->wdist);
    r->sdraw = -lheight / 2 + HEIGHT / 2;
    r->edraw = lheight / 2 + HEIGHT / 2;
    if (r->sdraw < 0)
        r->sdraw = 0;
    if (r->edraw >= HEIGHT)
        r->edraw = HEIGHT - 1;
    wolf_bresenhem(m, r, x, 0);
    ++r->edraw;
    if (r->edraw >= HEIGHT || r->edraw < 0)
        r->edraw = HEIGHT - 1;
}

/*
** Function wolf_dda():
** - sideDistX and sideDistY get incremented with deltaDistX with
** every jump in their direction, and mapX and mapY get incremented
** with stepX and stepY respectively.
** - jump to next map square, OR in x-direction, OR in y-direction
** - check if ray has hit a wall
*/

int    wolf_dda(t_ray *r)
{
    if (r->dsidex < r->dsidey)
    {
        r->side = 0;
        r->mapy += r->stepx;
        r->dsidex += r->_distx;
    }
    else
    {
        r->dsidey += r->_disty;
        r->mapy += r->stepy;
        r->side = 1;
    }
    map[r->mapx][r->mapy] > 0 ? r->hit = 1 : 0;
    return (r->hit == 0 ? wolf_dda(r) : 1);
}

/*
** Function wolf_define_dside():
** - dsideX/dsideY (distance) initial
** - step calculate
*/

void    wolf_define_dside(t_ray *r)
{
    if (r->rdirx < 0)
    {
        r->stepx = -1;
        r->dsidex = (r->rposx - r->mapx) * r->_distx;
    }
    else
    {
        r->stepx = 1;
        r->dsidex = (r->mapx + 1.0 - r->rposx) * r->_distx;
    }
    if (r->rdiry < 0)
    {
        r->stepy = -1;
        r->dsidey = (r->rposy - r->mapy) * r->_disty;
    }
    else
    {
        r->stepy = 1;
        r->dsidey = (r->mapy + 1.0 - r->rposy) * r->_disty;
    }
    wolf_dda(r);
}

/*
** Function wolf_define_ray():
** - raycasting variables defining
*/

t_ray   wolf_define_ray(t_map *g, int x)
{
    t_ray   r;

    //was there a wall hit?
    r.hit = 0;

    //calculate ray position and direction
    r.xcam = 2 * x / (double)WIDTH - 1;
    r.rposx = g->x_player;
    r.rposy = g->y_player;
    r.rdirx = g->x_direct + g->x_plane * r.xcam;
    r.rdiry = g->y_direct + g->y_plane * r.xcam;

    //which box of the map we're in
    r.mapx = (int)r.rposx;
    r.mapy = (int)r.rposy;

    //length of ray from one x or y-side to next x or y-side
    r._distx = sqrt(1 + (r.rdiry * r.rdiry) / (r.rdirx * r.rdirx));
    r._disty = sqrt(1 + (r.rdirx * r.rdirx) / (r.rdiry * r.rdiry));

    return (r);
}

/*
** Function wolf_load_game():
**  - Calculating and printing game function
*/

int    wolf_load_game(t_mlx *m, int x)
{
    t_ray r;

    r = wolf_define_ray(&m->g, x);                                  // ray-casting calculates
    wolf_define_dside(&r);                                          // step calculates
    if (r.side)                                                     // distance projected on cam direction calculates
        r.wdist = (r.mapx - r.rposx + (1 - r.stepx) / 2) / r.rdirx;
    else
        r.wdist = (r.mapy - r.rposy + (1 - r.stepy) / 2) / r.rdiry;
    wolf_load_image(m, &r, x);                                      // step drawing calls from here
    if (x < 1200)                                                   // recursive exit condition
        return (wolf_load_game(m, ++x));
    wolf_draw_info(m);                                              // drawing game info-menu here
    return (0xDEAD);                                                // fun useless return
}