#include "includes/w3d.h"

void    wolf_menu_hook(int x, int y, t_mlx *m)
{
    if (y > 475 && y < 500 && x > 45 && x < 215)        // new game
    {
        m->game = 1;
        wolf_load_default(m);
    }
    else if (y > 520 && y < 550 && x > 45 && x < 277)   // resume game
        (m->type == 1) ? wolf_load_game(m) : 0;
    else if (y > 570 && y < 600 && x > 45 && x < 310)   // control panel
        wolf_load_settings(m, 0);
    else if (y > 616 && y < 642 && x > 45 && x < 217)   // settings
        wolf_load_settings(m, 1);
    else if (y > 665 && y < 690 && x > 45 && x < 130)   // exit
        exit(1);
}

int     wolf_onbutton(int button, t_mlx *m)
{
    //mlx_clear_window(m->mlx, m->win); //clear previous image
    //debug features
    printf(COL_GREEN"button:\n\t\tkey: %d\n"COL_EOC, button);
    if (button == 53)
        exit(53);
    if (m)
    //TodO: write button events here
    return (1);
}

/*
** m.type variations:
**     0: menu window with turned OFF "Resume"
**     1: menu window with turned ON "Resume"
**     2: settings menu window
**     3: control panel menu window
**     4: game
*/

int     wolf_onmouse(int b, int x, int y, t_mlx *m)
{
    //debug features
    if (b != 1)
        return (0);
    //mlx_clear_window(m->mlx, m->win); //clear previous image
    printf(COL_LBLUE"mouse: \n\t\tkey: %d, x: %d, y: %d\n"COL_EOC, b, x, y);
    //TodO: write mouse events here
    if (m->type == 0)                                   // detecting widow type
        wolf_menu_hook(x, y, m);
    else if (m->type == 1)
        ;
    else if (m->type == 2)
        ;
    else if (m->type == 3)
        ;
    else

    return (1);
}