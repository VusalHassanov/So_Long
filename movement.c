/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:55:13 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 03:21:07 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	try_move_player(t_game *game, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_x >= game->map_width * TILE_SIZE || new_y < 0
		|| new_y >= game->map_height * TILE_SIZE)
		return (0);
	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (game->map[map_y][map_x] == '1')
		return (0);
	if (game->map[map_y][map_x] != 'E')
		game->locked = 0;
	if (game->map[map_y][map_x] == 'C')
		handle_collectible(game, map_x, map_y);
	else if (game->map[map_y][map_x] == 'E')
		return (handle_exit(game));
	game->player_x = new_x;
	game->player_y = new_y;
	game->move_count++;
	ft_printf("🚶 Player moved to (%d, %d) - Move #%d\n",
		game->player_x, game->player_y, game->move_count);
	return (1);
}

void	movement(t_game *game, int *new_x, int *new_y)
{
	if (game->key_w)
		*new_y -= TILE_SIZE;
	else if (game->key_s)
		*new_y += TILE_SIZE;
	else if (game->key_a)
	{
		*new_x -= TILE_SIZE;
		game->player_left = 0;
	}
	else if (game->key_d)
	{
		*new_x += TILE_SIZE;
		game->player_left = 1;
	}
}

void	process_movement(t_game *game)
{
	int	new_x;
	int	new_y;
	int	moved;

	if (game->last_move < MOVE_DELAY)
	{
		game->last_move++;
		return ;
	}
	moved = 0;
	new_x = game->player_x;
	new_y = game->player_y;
	movement(game, &new_x, &new_y);
	if (new_x != game->player_x || new_y != game->player_y)
	{
		if (try_move_player(game, new_x, new_y))
		{
			moved = 1;
			game->last_move = 0;
		}
	}
	if (moved)
		render_game(game);
}

int	game_loop(t_game *game)
{
	process_movement(game);
	return (0);
}
