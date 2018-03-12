#include "includes/w3d.h"

void    wolf_load_intro(t_mlx *m)
{
    m->introframe = 0;
    system("afplay ../music/_intro.mp3 &");
    wolf_intro_here(m);
}

void    wolf_intro_here(t_mlx *m)
{
    char *s;

    s = wolf_create_name((int)m->introframe, INTRO_PATH);
    m->img = mlx_xpm_file_to_image(m->mlx, s, &m->width, &m->height);
    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 120);
    mlx_destroy_image(m->mlx, m->img);
    ft_strdel(&s);
    m->introframe += 0.3;
}