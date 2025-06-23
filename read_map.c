/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 02:42:22 by vhasanov          #+#    #+#             */
/*   Updated: 2025/06/22 05:11:55 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

int	find_height(char *filename)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (close(fd), 0);
		}
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), lines);
}

static int	process_line(t_game *game, char *line, int *lines)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	game->map[*lines] = line;
	if (*lines == 0)
		game->map_width = ft_strlen(line);
	(*lines)++;
	return (1);
}

static int	init_map(t_game *game, char *filename)
{
	int	height;

	height = find_height(filename);
	if (height == 0)
	{
		ft_printf("Error\nMap file is empty or contains only blank lines\n");
		return (0);
	}
	game->map = malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (0);
	game->map_height = height;
	return (1);
}

int	read_map(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	int		lines;

	if (!init_map(game, filename))
		return (0);
	fd = open(filename, O_RDONLY);
	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!is_empty_line(line))
			process_line(game, line, &lines);
		else
			free(line);
		line = get_next_line(fd);
	}
	game->map[lines] = NULL;
	close(fd);
	return (1);
}
