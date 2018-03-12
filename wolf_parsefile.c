#include "includes/w3d.h"
#include "fcntl.h"

/*
** Function  wolf_check_player():
** - Writes an existing player coordinates into the main structure
*/
void    wolf_check_player(t_mlx *m, int player, int i, int j)
{
    if (player != 1)
        exit (printf(COL_LRED PLYR_ERROR COL_EOC));
    if (i != -42 && j != -42)
    {
        m->yplayer = i;
        m->xplayer = j;
    }
}


/*
** Function wolf_check_line()
** - Check input map line for correct wall placement
** - Places player if it was founded
** len  := line number
** len := max line length
** mass := our map
** buf  := input map line
*/

void    wolf_check_line(const char *buf, int ***mass, int line, int len)
{
    int i;
    int **l;

    l = *mass;
    i = -1;
    //if first or last line wall acquired
    if (line == 0 || line == len - 1)
    {
        while (buf[++i] && i < len)
            //if not 1 == wall error
            if (buf[i] != '1')
                exit(printf(COL_LRED WALL_ERROR COL_EOC));
    }
    else if (l[line][0] != 1 || l[line][len - 1] != 1)
        //if no wall at first and last position
        exit(printf(COL_LRED WALL_ERROR COL_EOC));
    else
        while (buf[++i] && i < len)
            //if player was founded write him as 2
            if (buf[i] == 'p')
                l[line][i] = 0;
    //if our line len != max line length == map size error
    if (i != len)
        exit (printf(COL_LRED SIZE_ERROR COL_EOC));
}

/*
** Function **wolf_create_map() creates an int mass for map
** Allocates memory for len x len size & return it
** len := map line max length
*/
int     **wolf_create_map(int len)
{
    int     i;
    int     **lol;

    i = -1;
    lol = (int **)malloc((size_t)8 * len);
    while (++i <= len)
        lol[i] = (int *)malloc((size_t)8 * len);
    return (lol);
}

/*
** Function wolf_parse_map() parses input file & writes map
** - Using gnl for read file lines
** - Checks for using < 1 || 0 || p > in da map symbols
*/

void    wolf_parse_map(int len, int fd, t_mlx *m, int ***mass)
{
    int i;
    int k;
    char *buf;
    int player;
    int **l;

    k = 0;
    l = *mass;
    player = 0;
    while (get_next_line(fd, &buf) > 0)
    {
        i = -1;
        while (buf[++i] && i < len)
            if (buf[i] == '1')
                l[k][i] = 1;
            else if (buf[i] == '0')
                l[k][i] = 0;
            else if (buf[i] == 'p')
                wolf_check_player(m, ++player, k, i);
            else
                exit(printf(COL_LRED SYMB_ERROR COL_EOC));
        wolf_check_line(buf, mass, k, len);
        ++k ? ft_strdel(&buf) : 0;
    }
    if (k != len)
        exit (printf(COL_LRED SIZE_ERROR COL_EOC));
    wolf_check_player(m, player, -42, -42);
}

/*
** Function wolf_map_open
** opens file with map and launch parse map function
*/

int    **wolf_map_open(char *name, t_mlx *m)
{
    int i;
    int fd;
    int **mass;
    char *buf;

    if (!name || !(fd = open(name, O_RDONLY)))
        exit(printf(COL_LRED"Open map error\n"COL_EOC));
    if (get_next_line(fd, &buf) <= 0)
        exit(printf(COL_LRED"Read map error\n"COL_EOC));
    i = -1;
    while (buf[++i])
            ;
    m->size = i;
    if (i < 5 || i > 50)
        exit (printf(COL_LRED SIZE_ERROR COL_EOC));
    while (get_next_line(fd, &buf) > 0)
        ft_strdel(&buf);
    close(fd);
    fd = open(name, O_RDONLY);
    mass = wolf_create_map(i);
    wolf_parse_map(i, fd, m, &mass);
    close(fd);
    return (mass);
}