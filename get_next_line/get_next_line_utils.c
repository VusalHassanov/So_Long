/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhasanov <vhasanov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:27:12 by vhasanov          #+#    #+#             */
/*   Updated: 2025/02/19 05:50:49 by vhasanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(char *str, char c)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (c == '\n')
	{
		while (str[i] != '\0' && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
	}
	else
	{
		while (str[i] != '\0')
			i++;
	}
	return (i);
}

char	*ft_linedup(char *str, size_t size)
{
	size_t	i;
	char	*new_str;

	if (str == NULL || size == 0)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_bufdup(char *str, size_t str_size, size_t line_size)
{
	size_t	i;
	char	*new_str;

	if (!str)
		return (NULL);
	new_str = (char *)malloc(sizeof(char) * (str_size - line_size + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[line_size])
	{
		new_str[i] = str[line_size];
		i++;
		line_size++;
	}
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	s3 = (char *)malloc(sizeof(char) * (ft_len(s1, '\0') + ft_len(s2, '\0')
				+ 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s3[i] = s2[j];
		j++;
		i++;
	}
	s3[i] = '\0';
	if (s1 && s1[0] != '\0')
		free(s1);
	return (s3);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (c == '\0')
		return ((char *)&s[ft_len(s, '\0')]);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
