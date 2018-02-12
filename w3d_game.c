#include "includes/w3d.h"

/*
** Function wolf_cal_tex():
 * - texturing calculations
**
*/
void    wolf_cal_tex(t_mlx *m, t_ray *r, int start, int end, int lheight, int x)
{
    int    tnum;
    int    xtex; //x coordinate on the texture
    double xwall;//where exactly the wall was hit

//    tnum = map[r->mapx][r->mapy] - 1; //1 subtracted from it so that texture 0 can be used!
    xwall = r->side ? r->rposx + r->wdist * r->rdirx : r->rposy + r->wdist * r->rdiry;
    xwall -= floor((xwall));
    xtex = (int)(xwall * (double)TWIDTH);
    if ((!r->side  && r->rdirx > 0) || (r->side == 1 && r->rdiry < 0))
        xtex = TWIDTH - xtex - 1;
    tnum = wolf_pixel_draw(r);
//    mlx_put_image_to_window(m->mlx, m->win, m->pic_txt[1], 700, 700);
    while (start < end)
    {
        int d = start * 256 - HEIGHT * 128 + lheight * 128;
        int texY = ((d * THEIGHT) / lheight) / 256;
//        char c = m->get_txt[tnum][THEIGHT * texY + xtex];
        m->im[x * m->bpp / 8 + start * m->sl] = m->get_txt[tnum][256 * texY + xtex * 4];
        m->im[x * m->bpp / 8 + start * m->sl + 1] = m->get_txt[tnum][256 * texY + xtex * 4 + 1];
        m->im[x * m->bpp / 8 + start * m->sl + 2] = m->get_txt[tnum][256 * texY + xtex * 4 + 2];
        m->im[x * m->bpp / 8 + start * m->sl + 3] = m->get_txt[tnum][256 * texY + xtex * 4 + 3];
        start++;
    }

//    for(int y = drawStart; y <drawEnd; y++)
//    {
//        int d = y * 256 - h * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
//        // TODO: avoid the division to speed this up
//        int texY = ((d * texHeight) / lineHeight) / 256;
//        Uint32 color = texture[texNum][texHeight * texY + texX];
//        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//        if(side == 1) color = (color >> 1) & 8355711;
//        buffer[y][x] = color;
//    }
//    m->pic_txt[4] = mlx_xpm_file_to_image(m->mlx, "../pictures/lol.xpm", &m->width, &m->height);
//    m->get_txt[4] = mlx_get_data_addr(m->pic_txt[4], &m->bpp, &m->sl, &m->end);
//    mlx_put_image_to_window(m->mlx, m->win, m->pic_txt[4], 0, 0);
//    mlx_destroy_image(m->mlx, m->img);
}

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
    if (r->edraw >= HEIGHT || r->edraw + 1 >= HEIGHT)
        r->edraw = HEIGHT - 1;
    wolf_cal_tex(m, r, r->sdraw, r->edraw, lheight, x);
//    wolf_bresenhem(m, r, x, 0);
    //printf(COL_MAGENTA"x:[%d] start:[%d] end:[%d]\n"COL_EOC, x, r->sdraw, r->edraw);
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
        r->mapx += r->stepx;
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

//    mlx_do_sync(m->mlx);
//    mlx_clear_window(m->mlx, m->win);                                   // clear previous image
    m->img = mlx_new_image(m->win, WIDTH, HEIGHT+1);                    // creating new image
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);        // gets data addr
    while (x < WIDTH) {
        r = wolf_define_ray(&m->g, x);                                  // ray-casting calculates
        wolf_define_dside(&r);                                          // step calculates
        if (!r.side)                                                    // distance projected on cam direction calculates
            r.wdist = (r.mapx - r.rposx + (1 - r.stepx) / 2) / r.rdirx;
        else
            r.wdist = (r.mapy - r.rposy + (1 - r.stepy) / 2) / r.rdiry;
        wolf_load_image(m, &r, x);                                      // step drawing calls from here
//    if (x < WIDTH)                                                    // recursive exit condition
//        return (wolf_load_game(m, ++x));
        x++;
    }
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    wolf_draw_info(m);                                              // drawing game info-menu here
    return (0xDEAD);                                                // fun useless return
}