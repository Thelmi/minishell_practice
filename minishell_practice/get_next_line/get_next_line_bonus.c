/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thelmy <thelmy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 20:32:22 by thelmy            #+#    #+#             */
/*   Updated: 2024/03/15 16:15:30 by thelmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	get_and_update(char *buffer, char **str)
{
	int	i;

	*str = ft_strjoin(*str, buffer);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		ft_memmove(buffer, buffer + i + 1, ft_strlen(buffer + i + 1, 3) + 1);
	else
		buffer[0] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1u];
	char		*str;
	int			bytes;

	bytes = 1;
	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		if (buffer[fd][0] == '\0')
		{
			bytes = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytes == -1 && free_str(&str))
				return (NULL);
			if (bytes == 0)
				return (str);
			buffer[fd][bytes] = '\0';
		}
		get_and_update(buffer[fd], &str);
	}
	return (str);
}
