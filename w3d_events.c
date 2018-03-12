#include "includes/w3d.h"

/*
**  Function  wolf_menu_hook():
**  - Processes buttons in "Main menu" window
*/

void    wolf_menu_hook(int x, int y, t_mlx *m)
{
    if (y > 475 && y < 500 && x > 45 && x < 215)        // new game
    {
        m->game = 1;
        m->type = 4;
        system("killall afplay &>/dev/null"); //stops the music playing
        system("afplay ../music/_wer1.mp3 &");
        wolf_load_default(m);
    }
    else if (y > 520 && y < 550 && x > 45 && x < 277)   // resume game
    {
        if (m->type == 1)
            m->game = 1;
        m->type = 4;
    }
    else if (y > 570 && y < 600 && x > 45 && x < 310)   // control panel
        m->type = 3;
    else if (y > 616 && y < 642 && x > 45 && x < 217)   // settings
        m->type = 2;
    else if (y > 665 && y < 690 && x > 45 && x < 130)   // exit
        wolf_exit_game(42);
}

/*
** Function  wolf_submenu_buttons():
**  - Processes buttons in "Settings" menu
*/

int     wolf_submenu_buttons(int x, int y, t_mlx *m)
{
    if (y > 352 && y < 369 && x > 366 && x < 385)
    {
        system("sh ../music/pause.sh");
        m->mus = 1;
    }
    else if (y > 352 && y < 369 && x > 401 && x < 427)
    {
        m->mus = 0;
        system("sh ../music/pause.sh");
    }

    else if (y > 433 && y < 445 && x > 490 && x < 500)
        m->speed > 1 ? m->speed-- : 0;
    else if (y > 433 && y < 445 && x > 560 && x < 572)
        m->speed < 4 ? m->speed++ : 0;
    else
        return (0);
    return (1);
}

/*
** Function  wolf_submenu_hook():
**  - Meets the events on "Settings" && "Control panel" windows
** Variables:
**  - $this.window = (m->type == 2) ? settings : control_panel;
**  - x,y = mouse click position with coordinates x,y.
*/

void    wolf_submenu_hook(int x, int y, t_mlx *m)
{
    if ((y > 142 && y < 172 && x > 132 && x < 160) ||
            (y > 806 && y < 879 && x > 546 && x < 777))
    {
        m->type = m->game == -1 ? 1 : 0;
//        wolf_load_menu(m);
    }
    if (m->type == 2 && wolf_submenu_buttons(x, y, m))
        wolf_load_submenu(m, 2);
}

/*
** Function wolf_onbutton():
**  - Meets the button events(in-game mode priority)
**  - Buttons: 0  - A (move left)
**             2  - D (move right)
**             1  - S (move back)
**             3  - F (show FPS)
**             13 - W (move forward)
**             14 - E (game pause)
**             35 - P (take screenshot)
**             53 - ESC (exit)
*/

int     wolf_onbutton(int button, t_mlx *m)
{
    //mlx_clear_window(m->mlx, m->win); //clear previous image
    if (button == 53)                           //ESC   - exit
        wolf_exit_game(1);
    else if (button == 35)                      //P     - screenshot
        system("screencapture -c -W -P ../screen.png");
    else if (m->game == 1)
    {
        if (button == 13 || button == 1)        // W & S- move forward/back
            wolf_move_ws(m, button);
        else if (button == 0 || button == 2)    // A & D- move lef/right
            wolf_move_ad(m, button);
        else if (button == 14)                  //E     - pause, loading menu
        {
            m->game = -1;
            m->type = 1;
        }
        else if (button == 3)
            m->fps *= -1;
    }
    else
        return (0);
//    mlx_clear_window(m->mlx, m->win); //clear previous image
//    mlx_do_sync(m->mlx);
//    m->img = mlx_new_image(m->win, WIDTH, HEIGHT + 1);
//    m->im = mlx_get_data_addr(m->img, &m->bpp, &m->sl, &m->end);
//    wolf_load_game(m, 0);
//    mlx_put_image_to_window(m->mlx, m->win, m->img, 0, 0);
    return (1);
}

/*
** m.type variations:
**     0: menu window with turned OFF "Resume" (default0)
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
//    mlx_do_sync(m->mlx);
//    mlx_clear_window(m->mlx, m->win);                                   // clear previous image
//      debug features
//    printf(COL_LBLUE"mouse: \n\t\tkey: %d, x: %d, y: %d\n"COL_EOC, b, x, y);
    //main functional code here
    if (m->type == 0 || m->type == 1)       // main menu type (game was started or not)
        wolf_menu_hook(x, y, m);
    else if (m->type == 2 || m->type == 3)  // in-submenu mode
        wolf_submenu_hook(x, y, m);
    else if (m->type == 4)                  // in-game mode
    {
        system("afplay ../music/_shoot.mp3 &");
        m->score++;
        m->g5frame += 0.1;
    }
    return (1);
}