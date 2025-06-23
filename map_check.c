/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 03:21:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/21 04:44:22 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls_enclosed(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->map_width)
	{
		if (game->map[0][x] != '1')
			return (0);
		if (game->map[game->map_height - 1][x] != '1')
			return (0);
		x++;
	}
	y = 0;
	while (y < game->map_height)
	{
		if (game->map[y][0] != '1')
			return (0);
		if (game->map[y][game->map_width - 1] != '1')
			return (0);
		y++;
	}
	return (1);
}

int	check_valid_characters(t_game *game)
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
			if (tile != '0' && tile != '1' && tile != 'P'
				&& tile != 'E' && tile != 'C')
			{
				ft_printf("Error\nInvalid character '%c' at position (%d,%d)\n",
					tile, x, y);
				ft_printf("Valid characters are: 0, 1, P, E, C\n");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_elements(t_game *game)
{
	int	players;
	int	exits;
	int	collectibles;

	players = 0;
	exits = 0;
	collectibles = 0;
	count_elements(game, &players, &exits, &collectibles);
	if (players != 1)
	{
		ft_printf("Error\nMap must have exactly 1 player (P)\n");
		return (0);
	}
	if (exits != 1)
	{
		ft_printf("Error\nMap must have exactly 1 exit (E)\n");
		return (0);
	}
	if (collectibles < 1)
	{
		ft_printf("Error\nMap must have at least 1 collectible (C)\n");
		return (0);
	}
	game->total_collectibles = collectibles;
	return (1);
}

int	check_map_rectangular(t_game *game)
{
	int	y;
	int	current_width;

	y = 0;
	ft_printf("🔍 Expected width: %d, Map height: %d\n", game->map_width,
		game->map_height);
	while (y < game->map_height)
	{
		current_width = 0;
		while (game->map[y][current_width])
			current_width++;
		ft_printf("Row %d: actual width = %d\n", y, current_width);
		if (current_width != game->map_width)
		{
			ft_printf("❌ MISMATCH at row %d: width=%d, expected=%d\n", y,
				current_width, game->map_width);
			ft_printf("Row content: '");
			current_width = 0;
			while (game->map[y][current_width])
				ft_printf("%c", game->map[y][current_width++]);
			return (ft_printf("'\n"), 0);
		}
		y++;
	}
	return (1);
}
