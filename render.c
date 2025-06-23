/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:34:36 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:40:33 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	render_tile(t_game *game, int x, int y, char tile)
{
	int	center_offset_x;
	int	center_offset_y;

	calculate_offsets(game, &center_offset_x, &center_offset_y);
	if (tile == '0' || tile == 'P' || tile == 'C' || tile == 'E')
		draw_image(game, game->img_floor, x * TILE_SIZE + center_offset_x, y
			* TILE_SIZE + center_offset_y);
	if (tile == '1')
		draw_image(game, game->img_wall, x * TILE_SIZE + center_offset_x, y
			* TILE_SIZE + center_offset_y);
	else if (tile == 'C')
		draw_image(game, game->img_collectible, x * TILE_SIZE + center_offset_x,
			y * TILE_SIZE + center_offset_y);
	else if (tile == 'E')
		draw_image(game, game->img_exit, x * TILE_SIZE + center_offset_x, y
			* TILE_SIZE + center_offset_y);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			render_tile(game, x, y, game->map[y][x]);
			x++;
		}
		y++;
	}
}

void	render_player(t_game *game)
{
	int	player_center_x;
	int	player_center_y;

	calculate_offsets(game, &player_center_x, &player_center_y);
	if (game->player_left)
	{
		draw_image(game, game->img_player_left, game->player_x
			+ player_center_x, game->player_y + player_center_y);
	}
	else
	{
		draw_image(game, game->img_player_right, game->player_x
			+ player_center_x, game->player_y + player_center_y);
	}
}

void	render_game(t_game *game)
{
	render_map(game);
	render_player(game);
}

void	draw_image(t_game *game, void *img, int x, int y)
{
	if (img)
		mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);
}
