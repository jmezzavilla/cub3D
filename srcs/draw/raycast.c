#include "cub3d.h"

double	get_wall_x(t_game *game)
{
	double	wall_X;

    if (game->raycast.side == 0) 
        wall_X = (game->player->pos->y ) + game->raycast.perpWallDist * game->raycast.dir->y;
    else           
        wall_X = (game->player->pos->x  )+ game->raycast.perpWallDist * game->raycast.dir->x;
    wall_X -= floor((wall_X));
	return (wall_X);
}

void	draw_wall(int x, int drawStart, int drawEnd, t_game *game)
{
	int	i;
    double wall_X;
    int texX;

	i = drawStart;
    //texturing calculations
    //int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

    //calculate value of wall_X
    wall_X = get_wall_x(game); //where exactly the wall was hit   

    //x coordinate on the texture
    texX = (int)(wall_X * BLOCK_PIXEL);
    if(game->raycast.side == 0 && game->raycast.dir->x > 0) 
        texX = BLOCK_PIXEL - texX - 1;
    if(game->raycast.side == 1 && game->raycast.dir->y < 0) 
        texX = BLOCK_PIXEL - texX - 1;
        // How much to increase the texture coordinate per screen pixel
    double step = 1.0 * BLOCK_PIXEL / game->raycast.lineHeight;
    // Starting texture coordinate
    double texPos = (drawStart - WIN_HEIGHT/ 2 + game->raycast.lineHeight / 2) * step;
    while (i < drawEnd)
    {
    // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (BLOCK_PIXEL - 1);
        texPos += step;
        put_pixel(&game->image_buffer, x, i, get_pixel_color(&game->scene->text_ea, texX, texY));
		i++;
    }
}

void	paint_floor(int color, int x, int d_end, t_game *game)
{
	int	i;

	i = d_end;
	if (d_end >= WIN_HEIGHT)
		return ;
	while (i < WIN_HEIGHT)
	{
		put_pixel(&game->image_buffer, x, i, color);
		i++;
	}
}

void	paint_ceiling(int color, int x, int d_start, t_game *game)
{
	int	i;

	i = 0;
	if (d_start <= 0)
		return ;
	while (i < d_start)
	{
		put_pixel(&game->image_buffer, x, i, color);
		i++;
	}
}
void draw_raycast(int x, t_game *game)
{
    //Calculate height of line to draw on screen
    if (game->raycast.perpWallDist > 0)
        game->raycast.lineHeight = (int)(WIN_HEIGHT / game->raycast.perpWallDist);
    else 
        game->raycast.lineHeight = (int)WIN_HEIGHT;

    //calculate lowest and highest pixel to fill in current stripe
    int drawStart = -game->raycast.lineHeight / 2 + WIN_HEIGHT  / 2;
    if(drawStart < 0)
        drawStart = 0;
    int drawEnd = game->raycast.lineHeight / 2 + WIN_HEIGHT  / 2;
    if(drawEnd >= WIN_HEIGHT )
        drawEnd = WIN_HEIGHT - 1;

    draw_wall(x, drawStart, drawEnd, game);
    paint_floor(game->scene->color_f.code_rgb, x, drawEnd, game);
    paint_ceiling(game->scene->color_c.code_rgb, x, drawStart, game);
}

void calc_steps(t_game *game)
{
    if(game->raycast.dir->x < 0)
    {
        game->raycast.stepX = -1;
        game->raycast.sideDist->x = ((game->player->pos->x) - game->raycast.map->x) * game->raycast.deltaDist->x;
    }
    else
    {
        game->raycast.stepX = 1;
        game->raycast.sideDist->x = (game->raycast.map->x + 1 - (game->player->pos->x)) * game->raycast.deltaDist->x;
    }

    if(game->raycast.dir->y < 0)
    {
        game->raycast.stepY = -1;
        game->raycast.sideDist->y = ((game->player->pos->y ) - game->raycast.map->y) * game->raycast.deltaDist->y;
    }
    else
    {
        game->raycast.stepY = 1;
        game->raycast.sideDist->y = (game->raycast.map->y + 1 - (game->player->pos->y )) * game->raycast.deltaDist->y;
    }
    /*
    //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
    */
}

void dda(t_game *game)
{
    int hit = 0; //was there a wall hit?

    while(hit == 0)
    {
        if(game->raycast.sideDist->x < game->raycast.sideDist->y)
        {
            game->raycast.sideDist->x += game->raycast.deltaDist->x;
            game->raycast.map->x += game->raycast.stepX;
            game->raycast.side = 0;
        }
        else
        {
            game->raycast.sideDist->y += game->raycast.deltaDist->y;
            game->raycast.map->y += game->raycast.stepY;
            game->raycast.side = 1;
        }
        if(game->raycast.map->x >= 0 && game->raycast.map->x < WIN_WIDTH &&
            game->raycast.map->y >= 0 && game->raycast.map->y < WIN_HEIGHT &&
            game->map[(int)game->raycast.map->y][(int)game->raycast.map->x] == '1')
                hit = 1;
    }

    /*
    int hit = 0; //was there a wall hit?
    //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      } 
      */
}

void init_ray(t_game *game, int x)
{
    double cameraX = 2 * x / (double) WIN_WIDTH- 1;
    game->raycast.dir->x = game->player->dir->x + game->player->plane->x * cameraX;
    game->raycast.dir->y = game->player->dir->y + game->player->plane->y * cameraX;
    /*
    //calculate ray position and direction
      double cameraX = 2 * x / double(w) - 1; //x-coordinate in camera space
      double rayDirX = dirX + planeX * cameraX;
      double rayDirY = dirY + planeY * cameraX;
    */

    game->raycast.map->x = (int)game->player->pos->x ;
    game->raycast.map->y = (int)game->player->pos->y ;

    if(game->raycast.dir->x == 0)
        game->raycast.deltaDist->x = 1e30;
    else
        game->raycast.deltaDist->x = fabs(1 / game->raycast.dir->x);
    
    if(game->raycast.dir->y == 0)
        game->raycast.deltaDist->y = 1e30;
    else
        game->raycast.deltaDist->y = fabs(1 / game->raycast.dir->y);
    
    /* game->raycast.hit = 0;
       //which box of the map we're in
    int mapX = int(posX);
    int mapY = int(posY);

    //length of ray from current position to next x or y-side
    double sideDistX;
    double sideDistY;

    //length of ray from one x or y-side to next x or y-side
    double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
    double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);
    double perpWallDist;

    //what direction to step in x or y-direction (either +1 or -1)
    int stepX;
    int stepY;

    int hit = 0; //was there a wall hit?
    int side; //was a NS or a EW wall hit?
    */
}

void	raycast(t_game *game)
{
    int x = 0;

    while (x < WIN_WIDTH)
    {
        init_ray(game, x);
        calc_steps(game);
        dda(game);
        if(game->raycast.side == 0)
            game->raycast.perpWallDist = (game->raycast.sideDist->x - game->raycast.deltaDist->x);
        else
            game->raycast.perpWallDist = (game->raycast.sideDist->y - game->raycast.deltaDist->y);
        /*//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);
        */
       draw_raycast(x,game);
        x++;
    }
    
}