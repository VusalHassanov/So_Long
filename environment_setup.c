/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:05:10 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:31:07 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game_pointers(t_game *game)
{
	game->img_player_left = NULL;
	game->img_player_right = NULL;
	game->img_wall = NULL;
	game->img_floor = NULL;
	game->img_collectible = NULL;
	game->img_exit = NULL;
}

int	setup_map_and_validation(t_game *game, char *filename)
{
	if (!read_map(game, filename))
	{
		ft_printf("❌ Error: Failed to load map %s\n", filename);
		return (0);
	}
	ft_printf("📁 Map loaded: %dx%d tiles\n", game->map_width, game->map_height);
	if (!validate_map(game))
	{
		ft_printf("❌ Invalid map file\n");
		free_map(game->map, game->map_height);
		return (0);
	}
	return (1);
}

int	setup_mlx_and_images(t_game *game)
{
	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
	{
		ft_printf("❌ Error: Failed to init MiniLibX\n");
		free_map(game->map, game->map_height);
		return (0);
	}
	ft_printf("✅ MiniLibX init success\n");
	if (!load_all_images(game))
	{
		ft_printf("❌ Error: Failed to load images\n");
		cleanup_game(game);
		return (0);
	}
	return (1);
}

int	window_check(t_game *game, int screen_width, int screen_height)
{
	if (game->width > screen_width || game->height > screen_height)
	{
		ft_printf("❌ Error: Window too large for screen\n");
		ft_printf("💡 Window: %dx%d, Screen: %dx%d\n",
			game->width,
			game->height,
			screen_width,
			screen_height);
		cleanup_game(game);
		return (1);
	}
	return (0);
}

int	create_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	game->width = game->map_width * TILE_SIZE;
	game->height = game->map_height * TILE_SIZE;
	mlx_get_screen_size(game->mlx_ptr, &screen_width, &screen_height);
	ft_printf("📐 Calculated window size: %dx%d pixels\n", game->width,
		game->height);
	ft_printf("🖥️  Screen size: %dx%d pixels\n", screen_width, screen_height);
	if (window_check(game, screen_width, screen_height))
		return (0);
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width, game->height,
			"So Long - Hold WASD/Arrows to move, ESC to quit");
	if (!game->win_ptr)
	{
		ft_printf("❌ Error: Failed to create window\n");
		cleanup_game(game);
		return (0);
	}
	ft_printf("✅ Window created successfully (%dx%d)\n", game->width,
		game->height);
	return (1);
}
