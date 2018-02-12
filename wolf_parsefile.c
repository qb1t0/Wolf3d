#include "includes/w3d.h"
#include "fcntl.h"

#define SIZE_ERROR "Invalid map: map size nxn, \n\t where 5 <= n <= 50\n"
#define WALL_ERROR "Invalid map: walls around the edges require\n"
#define PLYR_ERROR "Invalid map: only 1 player on map require"
#define SYMB_ERROR "Invalid map: map can cosist only 1,0 or p"


void    wolf_parse_map(int len, int fd, char *buf)
{
    int i;
    int k;
    int player;

    k = 1;
    player = 0;
    while (get_next_line(fd, &buf) > 0)
    {
        i = -1;
        while (buf[++i])
            if (buf[i] != '1' && buf[i] != '0')
            {
                if (buf[i] != 'p')
                    exit(printf(COL_LRED SYMB_ERROR COL_EOC));
                if (player)
                    exit(printf(COL_LRED PLYR_ERROR COL_EOC));
                
                player = 1;
            }
        k++;
    }
    if (k != len)
        exit (printf(COL_LRED SIZE_ERROR COL_EOC));
}

/*
** Function wolf_map_open
** opens file with map and launch parse map function
*/

void    wolf_map_open(char *name)
{
    int i;
    int fd;
    char *buf;

    if (!name || !(fd = open(name, O_RDONLY)))
        exit(printf(COL_LRED"Open map error\n"COL_EOC));
    if (get_next_line(fd, &buf) <= 0)
        exit(printf(COL_LRED"Read map error\n"COL_EOC));
    i = -1;
    while (buf[++i])
        if (buf[i] != '1')
            exit (printf(COL_LRED WALL_ERROR COL_EOC));
    if (i < 5)
        exit (printf(COL_LRED SIZE_ERROR COL_EOC));
    close(fd) ? fd = open(name, O_RDONLY) : 0;
    wolf_parse_map(i, fd, buf);
}