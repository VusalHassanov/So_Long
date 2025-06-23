/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:27:03 by vhasanov          #+#    #+#             */
/*   Updated: 2025/02/19 16:38:55 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*ft_read_to_buffer(int fd, char *old_str)
{
	char	*new_str;
	int		byte_read;

	new_str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_str)
		return (NULL);
	byte_read = 1;
	while (!(ft_strchr(old_str, '\n')) && byte_read != 0)
	{
		byte_read = read(fd, new_str, BUFFER_SIZE);
		if (byte_read == -1 || (byte_read == 0 && !old_str))
		{
			free(new_str);
			free(old_str);
			return (NULL);
		}
		new_str[byte_read] = '\0';
		if (old_str == NULL)
			old_str = ft_strjoin("", new_str);
		else
			old_str = ft_strjoin(old_str, new_str);
	}
	free(new_str);
	return (old_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	size_t		line_size;
	size_t		buffer_size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_read_to_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line_size = ft_len(buffer, '\n');
	line = ft_linedup(buffer, line_size);
	buffer_size = ft_len(buffer, '\0');
	buffer = ft_bufdup(buffer, buffer_size, line_size);
	if (buffer && buffer[0] == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	// Open the file you want to read
// 	fd = open("try.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Failed to open file");
// 		return (1);
// 	}
// 	// Read and print each line of the file
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line); // Don't forget to free the memory after using the line
// 	}
// 	// Close the file descriptor when done
// 	close(fd);
// 	return (0);
// }
