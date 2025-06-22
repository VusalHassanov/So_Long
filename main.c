/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:49:34 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:35:13 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	start_game_loop(t_game *game)
{
	render_game(game);
	ft_printf("🎮 Controls:\n");
	ft_printf("   - Hold WASD or Arrow keys to move continuously\n");
	ft_printf("   - Press ESC to close\n");
	ft_printf("\n");
	ft_printf("🔄 Starting event loop...\n");
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_printf("🚀 Starting So Long with images...\n");
	if (argc != 2)
	{
		ft_printf("❌ Usage: %s <map_file.ber>\n", argv[0]);
		return (1);
	}
	ft_memset(&game, 0, sizeof(t_game));
	if (!setup_map_and_validation(&game, argv[1]))
		return (1);
	game.move_count = 0;
	game.total_collectibles = count_collectibles(&game);
	ft_printf("📊 Total collectibles in map: %d\n", game.total_collectibles);
	if (!setup_mlx_and_images(&game))
		return (1);
	if (!create_window(&game))
		return (1);
	find_player_start_position(&game);
	setup_event_hooks(&game);
	start_game_loop(&game);
	return (0);
}
