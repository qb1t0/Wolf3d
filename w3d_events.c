#include "includes/w3d.h"

void    wolf_menu_hook(int x, int y, t_mlx *m)
{
    if (y > 475 && y < 500 && x > 45 && x < 215)        // new game
    {
        m->game = 1;
        m->type = 4;
        wolf_load_default(m);
    }
    else if (y > 520 && y < 550 && x > 45 && x < 277)   // resume game
        (m->type == 1) ? wolf_load_game(m) : 0;
    else if (y > 570 && y < 600 && x > 45 && x < 310)   // control panel
        wolf_load_settings(m, 3);
    else if (y > 616 && y < 642 && x > 45 && x < 217)   // settings
        wolf_load_settings(m, 2);
    else if (y > 665 && y < 690 && x > 45 && x < 130)   // exit
        exit(1);
}

/*
** Function  wolf_settings_buttons():
**  - Processes buttons in "Settings" menu
*/

int     wolf_settings_buttons(int x, int y, t_mlx *m)
{
    if (y > 352 && y < 369 && x > 366 && x < 385)
        m->mus = 1;
    else if (y > 352 && y < 369 && x > 401 && x < 427)
        m->mus = 0;
    else if (y > 433 && y < 445 && x > 490 && x < 500)
        m->speed > 1 ? m->speed-- : 0;
    else if (y > 433 && y < 445 && x > 560 && x < 572)
        m->speed < 4 ? m->speed++ : 0;
    else
        return (0);
    return (1);
}

/*
** Function  wolf_settings_hook():
**  - Meets the events on "Settings" && "Control panel" windows
** Variables:
**  - $this.window = (m->type == 2) ? settings : control_panel;
**  - x,y = mouse click position with coordinates x,y.
*/

void    wolf_settings_hook(int x, int y, t_mlx *m)
{
    if ((y > 142 && y < 172 && x > 132 && x < 160) ||
            (y > 806 && y < 879 && x > 546 && x < 777))
    {
        m->type = m->game ? 1 : 0;
        wolf_load_menu(m);
    }
    if (m->type == 2 && wolf_settings_buttons(x, y, m))
        wolf_load_settings(m, 2);
}

int     wolf_onbutton(int button, t_mlx *m)
{
    //mlx_clear_window(m->mlx, m->win); //clear previous image
        //debug features
        printf(COL_GREEN"button:\n\t\tkey: %d\n"COL_EOC, button);
    if (button == 53)
        exit(53);
    if (m->game)
    {

    }
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
    if (b != 1)                             // if !left mouse click event
        return (0);
    //mlx_clear_window(m->mlx, m->win); //clear previous image

        //debug features
        printf(COL_LBLUE"mouse: \n\t\tkey: %d, x: %d, y: %d\n"COL_EOC, b, x, y);
    //main functional code here
    if (m->type == 0 || m->type == 1)       // main menu type (game was started or not)
        wolf_menu_hook(x, y, m);
    else if (m->type == 2 || m->type == 3)  // in-submenu mode
        wolf_settings_hook(x, y, m);
    else if (m->type == 4)                  // in-game mode
        ;
    return (1);
}