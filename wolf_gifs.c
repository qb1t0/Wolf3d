#include "includes/w3d.h"

/*
** Function wolf_menugifs_init();
**  - Fills arrays menu GIF's for needed by the mlx functions
*/

void   wolf_menugifs_init(t_mlx *m, int frames)
{
    char *s;

    m->g1frame = 0;
    m->g2frame = 0;
    m->g3frame = 0;
    m->g4frame = 0;
    m->g5frame = 0;
    wolf_gamegifs_init(m, -1);
    while (++frames < GIF1_LEN) //girls
    {
        s = wolf_create_name(frames, MGIF1_PATH);
        m->gif1_toim[frames] = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
        m->gif1_addr[frames] = mlx_get_data_addr(m->gif1_toim[frames], &m->bpp, &m->sl, &m->end);
        ft_strdel(&s);
    }
    frames = -1;
    while (++frames < GIF4_LEN) //rick
    {
        s = wolf_create_name(frames, MGIF4_PATH);
        m->gif4_toim[frames] = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
        m->gif4_addr[frames] = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
        ft_strdel(&s);
    }
    m->aim_toim = mlx_xpm_file_to_image(m->mlx, CROSS_PATH, &m->width, &m->height);
    m->aim_addr = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
}

/*
** Function wolf_menugifs_init();
**  - Fills arrays game GIF's for needed by the mlx functions
*/

void    wolf_gamegifs_init(t_mlx *m, int frames)
{
    char *s;

    while (++frames < GIF2_LEN) //snoop
    {
        s = wolf_create_name(frames, MGIF2_PATH);
        m->gif2_toim[frames] = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
        m->gif2_addr[frames] = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
        ft_strdel(&s);
    }
    frames = -1;
    while (++frames < GIF3_LEN) //dog
    {
        s = wolf_create_name(frames, MGIF3_PATH);
        m->gif3_toim[frames] = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
        m->gif3_addr[frames] = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
        ft_strdel(&s);
    }
    frames = -1;
    while (++frames < GIF5_LEN) //gun
    {
        s = wolf_create_name(frames, MGIF5_PATH);
        m->gif5_toim[frames] = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
        m->gif5_addr[frames] = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
        ft_strdel(&s);
    }
}

/*
** Function wolf_check_gifframe():
**  - Loops GIF frames
*/

void    wolf_check_gifframe(t_mlx *m)
{
    if (m->g1frame >= GIF1_LEN)
        m->g1frame = 0;
    if (m->g2frame >= GIF2_LEN)
        m->g2frame = 0;
    if (m->g3frame >= GIF3_LEN)
        m->g3frame = 0;
    if (m->g4frame >= GIF4_LEN)
        m->g4frame = 0;
    if (m->g5frame >= GIF5_LEN)
        m->g5frame = 0;
    return ;
}

/*
** Fucntion wolf_gifs_draw():
**  - Puts GIF's frames to mlx image
**  - (type) ? put game gif's : put menu gif's
*/
void    wolf_gifs_draw(int type, t_mlx *m)
{
    wolf_check_gifframe(m);
    if (type <= 0)
    {
        mlx_put_image_to_window(m->mlx, m->win, m->gif1_toim[(int) m->g1frame], 320, 700);
        mlx_put_image_to_window(m->mlx, m->win, m->gif1_toim[(int) m->g1frame], 780, 700);
        if (!type)
            mlx_put_image_to_window(m->mlx, m->win, m->gif4_toim[(int) m->g4frame], 50, 150);
        m->g1frame += 0.4;
        m->g4frame += 0.4;
    }
    else
    {
        mlx_put_image_to_window(m->mlx, m->win, m->gif2_toim[(int) m->g2frame], 100, 590);
        mlx_put_image_to_window(m->mlx, m->win, m->gif2_toim[(int) m->g2frame], 900, 590);
        mlx_put_image_to_window(m->mlx, m->win, m->gif5_toim[(int) m->g5frame], 500, 460);
        if (m->fps > 0)
            mlx_put_image_to_window(m->mlx, m->win, m->gif3_toim[(int) m->g3frame], 40, 15);
        mlx_put_image_to_window(m->mlx, m->win, m->aim_toim, 450, 350);
        m->g2frame += 1;
        m->g3frame += 0.75;
        if (m->g5frame)
            m->g5frame += 0.4;
    }
    mlx_destroy_image(m->mlx, m->img);
}