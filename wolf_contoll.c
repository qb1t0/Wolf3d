#include "includes/w3d.h"

/*
** Function wolf_move_ad():
**  -To rotate, if the left(A) or right(D) arrow is pressed,
**  the direction vector & plane vector are rotated by using
**  the formulas of multiplication with the rotation matrix.
*/

void        wolf_move_ad(t_mlx *m, int type)
{
    double oldd;
    double oldp;


    oldd = m->g.x_direct;
    oldp = m->g.x_plane;
    if (type == 0)  //(A)
    {
        m->g.x_direct = m->g.x_direct * cos(m->g.rspeed) - m->g.y_direct * sin(m->g.rspeed);
        m->g.y_direct = oldd * sin(m->g.rspeed) + m->g.y_direct * cos(m->g.rspeed);
        m->g.x_plane = m->g.x_plane * cos(m->g.rspeed) - m->g.y_plane * sin(m->g.rspeed);
        m->g.y_plane = oldp * sin(m->g.rspeed) + m->g.y_player * cos(m->g.rspeed);
    }
    else //if type == 2(D)
    {
        m->g.x_direct = m->g.x_direct * cos(-m->g.rspeed) - m->g.y_direct * sin(-m->g.rspeed);
        m->g.y_direct = oldd * sin(-m->g.rspeed) + m->g.y_direct * cos(-m->g.rspeed);
        m->g.x_plane = m->g.x_plane * cos(-m->g.rspeed) - m->g.y_plane * sin(-m->g.rspeed);
        m->g.y_plane = oldp * sin(-m->g.rspeed) + m->g.y_player * cos(-m->g.rspeed);
    }
}

void        wolf_move_ws(t_mlx *m, int type)
{

}