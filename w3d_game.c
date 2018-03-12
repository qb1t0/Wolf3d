#include "includes/w3d.h"

/*
** Function wolf_load_image():
** - calculate the height of the line, that has to be drawn on screen
 * - call drawing algorithm
*/
//Todo: write drawing func call here(to bresenhem)

void    wolf_calc_walls(t_mlx *m, t_ray *r)
{
    // distance projected on cam direction calculates
    if (!r->side)
        r->wdist = (r->mapx - r->rposx + (1 - r->stepx) / 2) / r->rdirx;
    else
        r->wdist = (r->mapy - r->rposy + (1 - r->stepy) / 2) / r->rdiry;
    r->lheight = (int)(HEIGHT / r->wdist);
    r->sdraw = -r->lheight / 2 + HEIGHT / 2;
    r->edraw = r->lheight / 2 + HEIGHT / 2;
    if (r->sdraw < 0)
        r->sdraw = 0;
    if (r->edraw >= HEIGHT || r->edraw + 1 >= HEIGHT)
        r->edraw = HEIGHT - 1;
    if (r->side)
        r->wallx = r->rposx + r->wdist * r->rdirx;
    else
        r->wallx = r->rposy + r->wdist * r->rdiry;
    r->wallx -= floor((r->wallx));
    wolf_draw_texture(m, r, r->sdraw, r->edraw);

        //debug feature
    //printf(COL_MAGENTA"x:[%d] start:[%d] end:[%d]\n"COL_EOC, x, r->sdraw, r->edraw);
}

/*
** Function wolf_dda():
** - sideDistX and sideDistY get incremented with deltaDistX with
** every jump in their direction, and mapX and mapY get incremented
** with stepX and stepY respectively.
** - jump to next map square, OR in x-direction, OR in y-direction
** - check if ray has hit a wall
*/

int    wolf_dda(t_ray *r, t_mlx *m)
{
    if (r->dsidex < r->dsidey)
    {
        r->side = 0;
        r->mapx += r->stepx;
        r->dsidex += r->_distx;
    }
    else
    {
        r->dsidey += r->_disty;
        r->mapy += r->stepy;
        r->side = 1;
    }
    m->map[r->mapx][r->mapy] > 0 ? r->hit = 1 : 0;
    return (r->hit == 0 ? wolf_dda(r, m) : 1);
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
    r.x = x;

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

//    mlx_do_sync(m->mlx);
//    mlx_clear_window(m->mlx, m->win);                                   // clear previous image
    m->img = mlx_new_image(m->win, WIDTH, HEIGHT + 1);                    // creating new image
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);        // gets data addr
    while (x < WIDTH)
    {
        r = wolf_define_ray(&m->g, x);                                  // ray-casting calculates
        wolf_define_dside(&r);                                          // step calculates
        wolf_dda(&r, m);
        wolf_calc_walls(m, &r);                                      // step wall drawing calls from here
        wolf_calc_floor(m, &r, r.sdraw, r.edraw);                       // step floor drawing calls from here
        x++;
    }
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    wolf_draw_info(m);                                              // drawing game info-menu here
    wolf_gifs_draw(1, m);
    return (0xDEAD);                                                // fun useless return
}