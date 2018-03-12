#ifndef WOLF3D_H
# define WOLF3D_H

# include <mlx.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "../libft/ft_printf/ft_printf.h"

# define HEIGHT 960         /* window height        */
# define WIDTH 1280         /* window width         */
# define THEIGHT 64         /* texture height       */
# define TWIDTH 64          /* texture width        */

# define GIF1_LEN 10        /* girls frames numb    */
# define GIF2_LEN 58        /* snoop frames numb    */
# define GIF3_LEN 15        /* doggy frames numb    */
# define GIF4_LEN 28        /* rick frames numb     */
# define GIF5_LEN 10        /* gun frames numb      */

#define SIZE_ERROR "Invalid map: map size must be nxn, \n\t where 5 <= n <= 50\n"
#define WALL_ERROR "Invalid map: walls around the edges require\n"
#define PLYR_ERROR "Invalid map: 1 player on map require"
#define SYMB_ERROR "Invalid map: map can consist only 1, 0 or p"

# define USAGE "[usage]:\t./wolf3d"
# define INTRO_PATH "../pictures/intro/"
# define MGIF1_PATH "../pictures/gifs/gif1/"
# define MGIF2_PATH "../pictures/gifs/gif2/"
# define MGIF3_PATH "../pictures/gifs/gif3/"
# define MGIF4_PATH "../pictures/gifs/gif4/"
# define MGIF5_PATH "../pictures/gifs/gif5/"
# define WALLS_PATH "../pictures/walls/"
# define CROSS_PATH "../pictures/crosshair.xpm"

/*
** _______________________________________________________________________
**                                                                        ø
**  Game's map representation  (EXAMPLE)                                  ø
**
**static short          map[MHEIGHT][MWIDTH] =
**        {
**                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
**                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
**                {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
**                {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
**        };
** _______________________________________________________________________ø
*/

/*
**  Structure s_ray represents ray-casting variables
** _______________________________________________________________________
**                                                                        ø
**  xcam  +== || X-coordinate on the camera plane,                        ø
**      that the current x-coordinate of the screen represents            ø
**                                                                        ø
**  rposx +==\\                                                           ø
**            || Ray position, (default: equal player position)           ø
**  rposy +==//                                                           ø
**                                                                        ø
**  rdirx +==\\                                                           ø
**            || The direction of the ray. Calculates as:                 ø
**            || The sum of the dir vector, and a part of the             ø
**            || the plane vector.                                        ø
**  rdiry +==//                                                           ø
**                                                                        ø
**  mapx  +==\\                                                           ø
**            || The current square of the map the ray is in.             ø
**  mapy  +==//                                                           ø
** ______________________________________________________________________ ø
*/

typedef struct      s_ray{
    double          xcam;
    double          rposx;
    double          rposy;
    double          rdirx;
    double          rdiry;
    double          _distx;
    double          _disty;
    double          dsidex;     //the length of ray from current position to next x or y-side
    double          dsidey;
    double          wdist;      //the length of the ray to the wall.
    int             hit;        //was there a wall hit?
    int             side;       //was a NS or a EW wall hit?
    int             mapx;
    int             mapy;
    double          stepx;      //what direction to step in x or y-direction (either +1 or -1)
    double          stepy;
    double          wallx;      //where exactly the wall was hit
    double          fxwall;
    double          fywall;
    double          cfloorx;    //current floor coordinate n x-axis
    double          cfloory;    //current floor coordinate n y-axis
    int             tfloorx;    //texture x-coordinate
    int             tfloory;    //texture y-coordinate

    int             sdraw;
    int             edraw;
    int             lheight;    //line(wall y-height)
    int             x;
}                   t_ray;

/*
** Structure s_map uses for configuring game variables:
** _______________________________________________________________________
**                                                                        ø
**  x_plane;    +==\\                                                     ø
**                  || The camera plane of the player.                    ø
**  y_plane;    +==//                                                     ø
**                                                                        ø
**  x_player;   +==\\                                                     ø
**                  || Represent the position vector of the player.       ø
**  y_player;   +==//                                                     ø
**                                                                        ø
**  x_direct;   +==\\                                                     ø
**                  || Represent the direction of the player.             ø
**  y_direct;   +==//                                                     ø
**                                                                        ø
**  oldtime;    +==\\                                                     ø
**                  || Used to store the time of the current              ø
**                  || and the previous frame for the FPS counter.        ø
**  curtime;    +==//                                                     ø
** _______________________________________________________________________ø
*/

typedef struct      s_map{
    double          x_player;
    double          y_player;
    double          x_plane;
    double          y_plane;
    double          x_direct;
    double          y_direct;
    float           oldtime;
    float           curtime;
    double          mspeed;
    double          rspeed;
}                   t_map;

/*
**  Structure s_mlx uses for collecting data from mlx functions
**  Variables needed by the mlx library functions
** _______________________________________________________________________
**                                                                        ø
**  exp_x;  +==\\                                                         ø
**              ))  uses for saving mouse position                        ø
**  exp_y;  +==//                                                         ø
**  *mlx;   +==))   mlx process pointer                                   ø
**  *win;   +==))   mlx->window pointer                                   ø
**  *img;   +==))   mlx->image pointer                                    ø
**  *im;    +==))   mlx->image pixel array                                ø
**  bpp;    +==))   mlx->bits per pixel                                   ø
**  end;    +==))   mlx->endian type                                      ø
**  sl;     +==))   mlx->sl                                               ø
**  c;      +==))   color variable                                        ø
**  mus;    +==))   music variable ( ? on : off)                          ø
**  part;   +==))   1/4 part of window for threads                        ø
**  game;   +==))   if game was started                                   ø
**  size;   +==))   map size                                              ø
** _______________________________________________________________________ø
*/

typedef struct      s_mlx{
    float           introframe;
    int             exp_x;
    int             exp_y;
    void		    *mlx;
    void		    *win;
    void		    *img;
    char		    *im;
    int			    bpp;
    int             end;
    int			    sl;
    int             width;
    int             height;
    int             c;
    int             mus;
    int             part;
    int             type;
    int             game;
    double          t;
    double          _t;
    int             fps;
    char            *_fps;
    char            *_score;
    int             score;
    int             speed;
    struct s_map    g;
    char            *get_txt[9];
    void            *pic_txt[9];
    int             size;
    int             **map;
    int             xplayer;
    int             yplayer;

    /////////////////////////// gif for here
    float             g1frame;       // frame counter for girl  (menu)
    float             g2frame;       // frame counter for snoop (menu)
    float             g3frame;       // frame counter for dog   (game)
    float             g4frame;       // frame counter for rick  (menu)
    float             g5frame;       // frame counter for gun   (game)

    //////////////////////////  storing gif arrays here
    void            *gif1_toim[GIF1_LEN];   //for mlx_file_to_image()
    char            *gif1_addr[GIF1_LEN];   //for mlx_get_data_addr()
    void            *gif2_toim[GIF2_LEN];   //for mlx_file_to_image()
    char            *gif2_addr[GIF2_LEN];   //for mlx_get_data_addr()
    void            *gif3_toim[GIF3_LEN];   //for mlx_file_to_image()
    char            *gif3_addr[GIF3_LEN];   //for mlx_get_data_addr()
    void            *gif4_toim[GIF4_LEN];   //for mlx_file_to_image()
    char            *gif4_addr[GIF4_LEN];   //for mlx_get_data_addr()
    void            *gif5_toim[GIF5_LEN];   //for mlx_file_to_image()
    char            *gif5_addr[GIF5_LEN];   //for mlx_get_data_addr()

    //////////////////////////  storing crosshair picture data here
    void            *aim_toim;              //for mlx_file_to_image()
    char            *aim_addr;              //for mlx_get_data_addr()

}                   t_mlx;

/*
** Loading an intro functions:
** _______________________________________________________________________
**                                                                        ø
** void    wolf_load_intro(t_mlx *m);.  ø
** _______________________________________________________________________ø
*/

void    wolf_load_intro(t_mlx *m);
void    wolf_intro_here(t_mlx *m);

/*
** Main program functions:
** _______________________________________________________________________
**                                                                        ø
**  wolf_exit_game()    program exit function                             ø
**  wolf_load_default() loads default game values                         ø
 *  main                main its main, oky? )                             ø
** _______________________________________________________________________ø
*/
void    wolf_exit_game(int code);
int     wolf_main_loop(t_mlx *m);
int     wolf_load_game(t_mlx *m, int x);
void    wolf_load_default(t_mlx *m);
int     main(int ac, char **av);

/*
** Function for map parsing here:
** _______________________________________________________________________
**                                                                        ø
**  wolf_check_player() writes player coordinates in global structure     ø
**  wolf_check_line()   map line parsing and player searching             ø
**  wolf_create_map()   allocates memory for future map array             ø
**  wolf_parse_map()    input file parsing & writes                       ø
**  wolf_check_line() check line for walls and player search              ø
**  wolf_move_ad() moving LEFT/RIGHT                                      ø
**  wolf_mouse_expose turning screen to the LEFT/RIGHT                    ø
** _______________________________________________________________________ø
*/


void    wolf_check_player(t_mlx *m, int player, int i, int j);
void    wolf_check_line(const char *buf, int ***mass, int line, int len);
int     **wolf_create_map(int len);
void    wolf_parse_map(int len, int fd, t_mlx *m, int ***mass);
int     **wolf_map_open(char *name, t_mlx *m);


/*
** Function for game controls:
** _______________________________________________________________________
**                                                                        ø
**  wolf_move_ws() moving BACK/FORWARD                                    ø
**  wolf_move_ad() moving LEFT/RIGHT                                      ø
**  wolf_mouse_expose turning screen to the LEFT/RIGHT                    ø
** _______________________________________________________________________ø
*/

void    wolf_move_ws(t_mlx *m, int type);
void    wolf_move_ad(t_mlx *m, int type);
int     wolf_mouse_expose(int x, int y, t_mlx *m);

/*
** Function wolf_pixel_draw():
** _______________________________________________________________________
**                                                                        ø
** Puts pixel m->color(int, RGBA) in pixel array m->im(char *)            ø
** _______________________________________________________________________ø
*/


void    wolf_calc_walls(t_mlx *m, t_ray *r);
void    wolf_calc_floor(t_mlx *m, t_ray *r, int start, int end);
void    wolf_draw_floor(t_mlx *m, t_ray *r, int y, int type);
void    wolf_draw_texture(t_mlx *m, t_ray *r, int start, int end);
int	    wolf_texture_choose(t_ray *r, t_mlx *m, int type);
void    wolf_draw_info(t_mlx *m);
int     wolf_dda(t_ray *r, t_mlx *m);
void    wolf_define_dside(t_ray *r);
t_ray   wolf_define_ray(t_map *g, int x);


/*
** Functions wolf_onbutton(), wolf_onmouse():
** _______________________________________________________________________
**                                                                        ø
** Those functions processes intercepts of all mouse- || button- events.  ø
** _______________________________________________________________________ø
*/


void    wolf_submenu_hook(int x, int y, t_mlx *m);
int     wolf_submenu_buttons(int x, int y, t_mlx *m);
void    wolf_menu_hook(int x, int y, t_mlx *m);
int     wolf_onbutton(int button, t_mlx *m);
int     wolf_onmouse(int b, int x, int y, t_mlx *m);


/*
** GIF-images loading functions:
** _______________________________________________________________________
**                                                                        ø
** void    wolf_gamegifs_init(t_mlx *m);    init GIF's using in game      ø
** void    wolf_menugifs_init(t_mlx *m);    init GIF's using in menu      ø
** void    wolf_check_gifframe(t_mlx *m);   loops frame iterations        ø
** void    wolf_gifs_draw(int type);        puts GIF's frame to window    ø
** _______________________________________________________________________ø
*/


void    wolf_gamegifs_init(t_mlx *m, int frames);
void    wolf_menugifs_init(t_mlx *m, int frames);
void    wolf_check_gifframe(t_mlx *m);
void    wolf_gifs_draw(int type, t_mlx *m);


/*
** Menu creating functions:
** _______________________________________________________________________
**                                                                        ø
** wolf_l*oad_menu()Creates starting page in new widow with game menu.    ø
** _______________________________________________________________________ø
*/

void    wolf_load_menu(t_mlx *m);
void    wolf_settings_add(t_mlx *m);
char    *wolf_create_name(int n, char *path);
void    wolf_load_submenu(t_mlx *m, int type);

#endif //WOLF3D