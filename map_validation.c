/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:45:21 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:51:23 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_position(t_game *game, int *player_x, int *player_y)
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
				*player_x = x;
				*player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

char	**copy_map(t_game *game)
{
	char	**map_copy;
	int		y;
	int		i;

	map_copy = malloc(sizeof(char *) * game->map_height);
	if (!map_copy)
		return (NULL);
	y = 0;
	while (y < game->map_height)
	{
		map_copy[y] = malloc(sizeof(char) * (game->map_width + 1));
		if (!map_copy[y])
		{
			i = 0;
			while (i < y)
				free(map_copy[i++]);
			free(map_copy);
			return (NULL);
		}
		ft_strlcpy(map_copy[y], game->map[y], game->map_width);
		y++;
	}
	return (map_copy);
}

void	count_elements(t_game *game, int *players, int *exits,
		int *collectibles)
{
	int		y;
	int		x;
	char	tile;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			tile = game->map[y][x];
			if (tile == 'P')
				(*players)++;
			else if (tile == 'E')
				(*exits)++;
			else if (tile == 'C')
				(*collectibles)++;
			x++;
		}
		y++;
	}
}

int	validate_paths(t_game *game)
{
	char			**map_copy;
	t_flood_params	params;
	int				collectibles_found;
	int				exit_found;

	collectibles_found = 0;
	exit_found = 0;
	map_copy = copy_map(game);
	if (!map_copy)
	{
		ft_printf("Error\nMemory allocation failed\n");
		return (0);
	}
	params.map = map_copy;
	params.collectibles_found = collectibles_found;
	params.exit_found = exit_found;
	params.map_width = game->map_width;
	return (run_flood_fill(game, &params));
}

int	validate_map(t_game *game)
{
	ft_printf("🔍 Validating map...\n");
	if (!check_valid_characters(game))
		return (0);
	if (!check_map_elements(game))
		return (0);
	if (!check_map_rectangular(game))
		return (0);
	if (!check_walls_enclosed(game))
	{
		ft_printf("Error\nMap must be surrounded by walls\n");
		return (0);
	}
	if (!validate_paths(game))
		return (0);
	ft_printf("✅ Map validation passed!\n");
	ft_printf("📊 Found: 1 player, 1 exit, %d collectibles\n",
		game->total_collectibles);
	return (1);
}
