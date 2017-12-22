#include "includes/w3d.h"

int     wolf_onbutton(int button, t_mlx *m)
{
    mlx_clear_window(m->mlx, m->win); //clear previous image
    //debug features
    printf(COL_GREEN"button:\n\t\tkey: %d\n"COL_EOC, button);
    if (button == 53)
        exit(53);
    //TodO: write button events here
    return (1);
}

int     wolf_onmouse(int b, int x, int y, t_mlx *m)
{
    mlx_clear_window(m->mlx, m->win); //clear previous image
    //debug features
    printf(COL_LBLUE"mouse: \n\t\tkey: %d, x: %d, y: %d\n"COL_EOC, b, x, y);
    //TodO: write mouse events here
    return (1);
}