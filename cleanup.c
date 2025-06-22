/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:40:56 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 01:56:38 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game *game)
{
	ft_printf("🗑️  Destroying images...\n");
	if (game->img_player_right)
		mlx_destroy_image(game->mlx_ptr, game->img_player_right);
	if (game->img_player_left)
		mlx_destroy_image(game->mlx_ptr, game->img_player_left);
	if (game->img_wall)
		mlx_destroy_image(game->mlx_ptr, game->img_wall);
	if (game->img_floor)
		mlx_destroy_image(game->mlx_ptr, game->img_floor);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx_ptr, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx_ptr, game->img_exit);
}

void	free_map(char **map, int height)
{
	int	y;

	if (!map)
		return ;
	y = 0;
	while (y < height && map[y])
	{
		free(map[y]);
		y++;
	}
	free(map);
}

void	cleanup_game(t_game *game)
{
	ft_printf("🧹 Cleaning up game resources...\n");
	destroy_images(game);
	if (game->map)
	{
		free_map(game->map, game->map_height);
		game->map = NULL;
	}
	if (game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	if (game->mlx_ptr)
	{
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
	}
}

int	close_window(t_game *game)
{
	ft_printf("🚪 Closing window...\n");
	cleanup_game(game);
	ft_printf("👋 Goodbye!\n");
	exit(0);
}
