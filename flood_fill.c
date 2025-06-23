/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:10:31 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:48:41 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_start_position(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x = x * TILE_SIZE;
				game->player_y = y * TILE_SIZE;
				ft_printf("🚶 Player starting position: (%d, %d)\n",
					game->player_x, game->player_y);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	flood_fill(t_flood_params *params, int x, int y, int map_height)
{
	if (x < 0 || y < 0 || x >= params->map_width || y >= map_height)
		return ;
	if (params->map[y][x] == '1' || params->map[y][x] == 'V')
		return ;
	if (params->map[y][x] == 'C')
		params->collectibles_found++;
	else if (params->map[y][x] == 'E')
		params->exit_found++;
	params->map[y][x] = 'V';
	flood_fill(params, x + 1, y, map_height);
	flood_fill(params, x - 1, y, map_height);
	flood_fill(params, x, y + 1, map_height);
	flood_fill(params, x, y - 1, map_height);
}

int	run_flood_fill(t_game *game, t_flood_params *params)
{
	int	player_x;
	int	player_y;
	int	is_valid;

	player_x = -1;
	player_y = -1;
	find_player_position(game, &player_x, &player_y);
	if (player_x == -1)
	{
		ft_printf("Error\nPlayer position not found\n");
		free_map(params->map, game->map_height);
		return (0);
	}
	flood_fill(params, player_x, player_y, game->map_height);
	is_valid = check_flood_results(game, params);
	free_map(params->map, game->map_height);
	return (is_valid);
}

int	check_flood_results(t_game *game, t_flood_params *params)
{
	int	collectibles_found;
	int	exit_found;

	collectibles_found = params->collectibles_found;
	exit_found = params->exit_found;
	if (collectibles_found != game->total_collectibles)
	{
		ft_printf("Error\nNot all collectibles are reachable"
			"(%d/%d reachable)\n",
			collectibles_found, game->total_collectibles);
		return (0);
	}
	if (exit_found != 1)
	{
		ft_printf("Error\nExit is not reachable\n");
		return (0);
	}
	return (1);
}
