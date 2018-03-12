#include "includes/w3d.h"

/*
** Function wolf_move_ad():
**  -To rotate, if the left(A) or right(D) arrow is pressed,
**  the direction vector & plane vector are rotated by using
**  the formulas of multiplication with the rotation matrix.
*/

void        wolf_move_ad(t_mlx *m, int type)
{
    int **map;

    map = m->map;
//    system("afplay ../music/_steps.mp3 &");
    if (type == 0)  //(A)
    {
        if (!map[(int)(m->g.x_player - m->g.x_plane * m->g.mspeed)]\
        [(int)(m->g.y_player)])
            m->g.x_player -= m->g.x_plane * m->g.mspeed;
        if (!map[(int)(m->g.x_player)][(int)(m->g.y_player - m->g.y_plane * m->g.mspeed)])
            m->g.y_player -= m->g.y_plane * m->g.mspeed;
    }
    else //if type == 2(D)
    {
        if (!map[(int)(m->g.x_player + m->g.x_plane * m->g.mspeed)][(int)(m->g.y_player)])
            m->g.x_player += m->g.x_plane * m->g.mspeed;
        if (!map[(int)(m->g.x_player)][(int)(m->g.y_player + m->g.y_plane * m->g.mspeed)])
            m->g.y_player += m->g.y_plane * m->g.mspeed;
    }
}

/*
** Function wolf_move_as():
**  -To rotate, if the forward(W) or back(S) arrow is pressed,
**  the direction vector & plane vector are rotated by using
**  the formulas of multiplication with the rotation matrix.
*/

void        wolf_move_ws(t_mlx *m, int type)
{
    int **map;

    map = m->map;
//    system("afplay ../music/_steps.mp3 &");
    if (type == 13) //(W)
    {
        if (!map[(int)(m->g.x_player + m->g.x_direct * m->g.mspeed)]\
        [(int)(m->g.y_player)])
            m->g.x_player += m->g.x_direct * m->g.mspeed;
        if (!map[(int)(m->g.x_player)][(int)(m->g.y_player + m->g.y_direct * m->g.mspeed)])
            m->g.y_player += m->g.y_direct * m->g.mspeed;
    }
    else    //if type == 1(S)
    {
        if (!map[(int)(m->g.x_player - m->g.x_direct * m->g.mspeed)]\
        [(int)(m->g.y_player)])
            m->g.x_player -= m->g.x_direct * m->g.mspeed;
        if (!map[(int)(m->g.x_player)][(int)(m->g.y_player - m->g.y_direct * m->g.mspeed)])
            m->g.y_player -= m->g.y_direct * m->g.mspeed;
    }
}


/*
** Function wolf_move_as():
**  - To turning around, if mouse was moved left/right in the game
**  Calls from wolf_load_game() func, using mlx_hook with (6, 64)
**  x,y - current mouse position
*/

int    wolf_mouse_expose(int x, int y, t_mlx *m)
{

    double oldd;
    double oldp;

    if (m->game != 1 || x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
        return (0);
//    mlx_do_sync(m->mlx);
//    mlx_clear_window(m->mlx, m->win);                                   // clear previous image
    oldd = m->g.x_direct;
    oldp = m->g.x_plane;
    //turning to the right
    if (x > m->exp_x)
    {
        m->g.x_direct = m->g.x_direct * cos(-m->g.rspeed) -  m->g.y_direct * sin(-m->g.rspeed);
        m->g.y_direct = oldd * sin(-m->g.rspeed) + m->g.y_direct * cos(-m->g.rspeed);
        m->g.x_plane = m->g.x_plane * cos(-m->g.rspeed) - m->g.y_plane * sin(-m->g.rspeed);
        m->g.y_plane = oldp * sin(-m->g.rspeed) + m->g.y_plane * cos(-m->g.rspeed);
    }
    if (x < m->exp_x) //turning to the left
    {
        m->g.x_direct = m->g.x_direct * cos(m->g.rspeed) - m->g.y_direct * sin(m->g.rspeed);
        m->g.y_direct = oldd * sin(m->g.rspeed) + m->g.y_direct * cos(m->g.rspeed);
        m->g.x_plane = m->g.x_plane * cos(m->g.rspeed) - m->g.y_plane * sin(m->g.rspeed);
        m->g.y_plane = oldp * sin(m->g.rspeed) + m->g.y_plane * cos(m->g.rspeed);
    }
    m->exp_x = x;
//    wolf_load_game(m, 0);
    return (0);
}
