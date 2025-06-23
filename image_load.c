/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_load.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:22:46 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/21 19:36:33 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*load_image(t_game *game, char *path, int *width, int *height)
{
	void	*img_ptr;

	ft_printf("🖼️  Loading image: %s\n", path);
	img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, width, height);
	if (!img_ptr)
	{
		ft_printf("❌ Error: Failed to load image %s\n", path);
		return (NULL);
	}
	ft_printf("✅ Image loaded successfully (%dx%d)\n", *width, *height);
	return (img_ptr);
}

int	load_game_sprites(t_game *game)
{
	game->img_player_right = load_image(game, "images/right_player.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_player_right)
		return (0);
	game->img_player_left = load_image(game, "images/left_player.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_player_left)
		return (0);
	game->img_collectible = load_image(game, "images/collectible.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_collectible)
		return (0);
	game->img_exit = load_image(game, "images/exit.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_exit)
		return (0);
	return (1);
}

int	load_environment_sprites(t_game *game)
{
	game->img_floor = load_image(game, "images/floor.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_floor)
		return (0);
	game->img_wall = load_image(game, "images/wall.xpm",
			&game->img_width, &game->img_height);
	if (!game->img_wall)
		return (0);
	return (1);
}

int	load_all_images(t_game *game)
{
	ft_printf("📁 Loading all images...\n");
	if (!load_game_sprites(game))
		return (0);
	if (!load_environment_sprites(game))
		return (0);
	ft_printf("✅ All images loaded successfully!\n");
	return (1);
}
