/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:26:56 by vhasanov          #+#    #+#             */
/*   Updated: 2025/01/29 15:52:01 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

// #define BUFFER_SIZE 10 // You can adjust this value as needed
// #include <fcntl.h>

# include <stdlib.h>
# include <unistd.h>

size_t	ft_len(char *str, char c);
char	*ft_linedup(char *str, size_t size);
char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char	*ft_read_to_buffer(int fd, char *old_str);
char	*ft_bufdup(char *str, size_t str_size, size_t line_size);

#endif