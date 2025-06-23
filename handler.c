/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:50:08 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 02:29:35 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_collectibles(t_game *game)
{
	int	remaining;
	int	y;
	int	x;

	remaining = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'C')
				remaining++;
			x++;
		}
		y++;
	}
	return (remaining);
}

int	handle_collectible(t_game *game, int map_x, int map_y)
{
	int	remaining_collectibles;

	ft_printf("💎 Found collectible, changing map...\n");
	game->map[map_y][map_x] = '0';
	remaining_collectibles = count_collectibles(game);
	ft_printf("💎 Collectible collected! %d remaining\n",
		remaining_collectibles);
	return (1);
}

int	handle_exit(t_game *game)
{
	int	remaining_collectibles;

	remaining_collectibles = count_collectibles(game);
	if (remaining_collectibles == 0)
	{
		ft_printf("🎉 Congratulations! You collected all items and escaped!\n");
		ft_printf("🚪 You win! Game completed in %d moves!\n",
			game->move_count + 1);
		close_window(game);
		return (1);
	}
	if (!game->locked)
	{
		ft_printf("🚫 Door is locked! Collect all "
			"%d remaining collectibles first!\n", remaining_collectibles);
	}
	game->locked = 1;
	return (0);
}

void	calculate_offsets(t_game *game, int *center_x, int *center_y)
{
	*center_x = (TILE_SIZE - game->img_width) / 2;
	*center_y = (TILE_SIZE - game->img_height) / 2;
}
