/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izanoni <izanoni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:46:34 by izanoni           #+#    #+#             */
/*   Updated: 2023/06/20 18:35:10 by izanoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_read(int fd, char *str);
char	*ft_current_line(char *str);
char	*ft_get_rest(char *str);

char	*get_next_line(int fd)
{
	static char	*all_lines[1024];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	all_lines[fd] = ft_get_read(fd, all_lines[fd]);
	if (all_lines[fd] == NULL)
		return (NULL);
	current_line = ft_current_line(all_lines[fd]);
	all_lines[fd] = ft_get_rest(all_lines[fd]);
	return (current_line);
}

char	*ft_get_read(int fd, char *str)
{
	char	*line;
	char	*temp;
	ssize_t	line_len;

	line = ft_calloc ((BUFFER_SIZE + 1), sizeof(char));
	if (line == NULL)
		return (NULL);
	line_len = 1;
	while (ft_strchr (str, '\n') == NULL && line_len != 0)
	{
		line_len = read (fd, line, BUFFER_SIZE);
		if (line_len < 0)
		{
			free (str);
			free (line);
			return (NULL);
		}
		line[line_len] = '\0';
		temp = ft_strjoin (str, line);
		free (str);
		str = temp;
	}
	free (line);
	return (str);
}

char	*ft_current_line(char *str)
{
	char	*current_line;
	int		count;

	count = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	count++;
	current_line = ft_calloc ((count + 1), sizeof(char));
	while (count > 0)
	{
		count--;
		current_line[count] = str[count];
	}
	return (current_line);
}

char	*ft_get_rest(char	*str)
{
	size_t		count;
	size_t		rest_count;
	size_t		len_rest;
	char		*rest;

	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\0')
	{
		free(str);
		return (NULL);
	}
	len_rest = (ft_strlen(str)) - count;
	rest = ft_calloc((len_rest + 1), sizeof(char));
	if (rest == NULL)
		return (NULL);
	count++;
	rest_count = 0;
	while (str[count] != '\0')
		rest[rest_count++] = str[count++];
	free (str);
	return (rest);
}
