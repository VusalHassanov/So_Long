/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:22:01 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:40:48 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	expose_hook(t_game *game)
{
	render_game(game);
	return (0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
	{
		ft_printf("🔴 ESC pressed - closing window\n");
		close_window(game);
	}
	if (keycode == 119 || keycode == 65362)
		game->key_w = 1;
	else if (keycode == 97 || keycode == 65361)
		game->key_a = 1;
	else if (keycode == 115 || keycode == 65364)
		game->key_s = 1;
	else if (keycode == 100 || keycode == 65363)
		game->key_d = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 119 || keycode == 65362)
		game->key_w = 0;
	else if (keycode == 97 || keycode == 65361)
		game->key_a = 0;
	else if (keycode == 115 || keycode == 65364)
		game->key_s = 0;
	else if (keycode == 100 || keycode == 65363)
		game->key_d = 0;
	return (0);
}

void	setup_event_hooks(t_game *game)
{
	mlx_hook(game->win_ptr, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
	mlx_hook(game->win_ptr, DESTROY_NOTIFY, 0, close_window, game);
	mlx_expose_hook(game->win_ptr, expose_hook, game);
	mlx_loop_hook(game->mlx_ptr, game_loop, game);
}
