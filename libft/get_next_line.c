/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnepfumb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 08:39:40 by mnepfumb          #+#    #+#             */
/*   Updated: 2017/11/20 11:00:54 by mnepfumb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_read(int const fd, char **line)
{
	char	*buff;
	char	*holder;
	int		bytes_read;

	if (!(buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (-1);
	bytes_read = read(fd, buff, BUFF_SIZE);
	if (bytes_read > 0)
	{
		buff[bytes_read] = '\0';
		holder = ft_strjoin(*line, buff);
		free(*line);
		*line = holder;
	}
	free(buff);
	return (bytes_read);
}

int				get_next_line(const int fd, char **line)
{
	static char	*line_read = NULL;
	char		*holder;
	int			bytes_read;

	if ((!line_read && !(line_read = (char *)malloc(sizeof(*line_read))))
			|| !line || fd < 0 || BUFF_SIZE < 0)
		return (-1);
	holder = ft_strchr(line_read, '\n');
	while (holder == NULL)
	{
		bytes_read = ft_read(fd, &line_read);
		if (bytes_read == 0)
		{
			if (ft_strlen(line_read) == 0)
				return (0);
			line_read = ft_strjoin((line_read), "\n");
		}
		if (bytes_read < 0)
			return (-1);
		else
			holder = ft_strchr(line_read, '\n');
	}
	*line = ft_strsub(line_read, 0, ft_strlen(line_read) - ft_strlen(holder));
	line_read = ft_strdup(holder + 1);
	return (1);
}
