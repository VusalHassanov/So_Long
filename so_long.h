/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 02:49:56 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:50:36 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./get_next_line/get_next_line.h"
#include "./lib_ft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# define TILE_SIZE 64
# define ESC_KEY 65307
# define DESTROY_NOTIFY 17
# define MOVE_DELAY 1000

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
	void	*img_wall;
	void	*img_floor;
	void	*img_player_right;
	void	*img_player_left;
	void	*img_collectible;
	void	*img_exit;
	int		player_x;
	int		player_y;
	int		player_left;
	int		img_width;
	int		img_height;
	char	**map;
	int		map_width;
	int		map_height;
	int		move_count;
	int		total_collectibles;
	int		key_w;
	int		key_a;
	int		key_s;
	int		key_d;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		last_move;
	int		locked;
}			t_game;

typedef struct s_flood_params
{
	char	**map;
	int		collectibles_found;
	int		exit_found;
	int		map_width;
}			t_flood_params;

int			read_map(t_game *game, char *filename);
int			find_height(char *filename);
int			validate_map(t_game *game);
void		find_player_position(t_game *game, int *player_x, int *player_y);
char		**copy_map(t_game *game);
int			check_walls_enclosed(t_game *game);
int			check_map_elements(t_game *game);
int			check_map_rectangular(t_game *game);
int			validate_paths(t_game *game);
void		error_exit(t_game *game, char *message);
int			is_empty_line(char *line);
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
int			game_loop(t_game *game);
void		process_movement(t_game *game);
int			try_move_player(t_game *game, int new_x, int new_y);
void		*load_image(t_game *game, char *path, int *width, int *height);
int			load_game_sprites(t_game *game);
int			load_environment_sprites(t_game *game);
int			load_all_images(t_game *game);
void		render_tile(t_game *game, int x, int y, char tile);
void		render_map(t_game *game);
void		render_player(t_game *game);
void		render_game(t_game *game);
void		draw_image(t_game *game, void *img, int x, int y);
void		destroy_images(t_game *game);
void		free_map(char **map, int height);
void		cleanup_game(t_game *game);
int			close_window(t_game *game);
int			count_collectibles(t_game *game);
int			handle_collectible(t_game *game, int map_x, int map_y);
int			handle_exit(t_game *game);
void		movement(t_game *game, int *new_x, int *new_y);
int			setup_map_and_validation(t_game *game, char *filename);
int			setup_mlx_and_images(t_game *game);
int			create_window(t_game *game);
void		calculate_offsets(t_game *game, int *center_x, int *center_y);
int			expose_hook(t_game *game);
void		setup_event_hooks(t_game *game);
void		flood_fill(t_flood_params *params, int x, int y, int map_height);
int			run_flood_fill(t_game *game, t_flood_params *params);
int			check_flood_results(t_game *game, t_flood_params *params);
int			check_valid_characters(t_game *game);
void		count_elements(t_game *game, int *players, int *exits,
				int *collectibles);
void		find_player_start_position(t_game *game);

#endif