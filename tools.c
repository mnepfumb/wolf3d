/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnepfumb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 09:25:22 by mnepfumb          #+#    #+#             */
/*   Updated: 2017/12/11 15:40:00 by mnepfumb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_pixel(t_mlx *mlx, int x, int y, int color)
{
	int				i;
	unsigned int	p;

	i = 0;
	p = x * (mlx->bpp / 8) + y * (mlx->size_line);
	while (i < (mlx->bpp / 8))
	{
		mlx->d[p + i] = color;
		color >>= 8;
		i++;
	}
}

int		ft_player_init(t_mlx *mlx, int j, int i)
{
	while (mlx->map[j])
	{
		i = 0;
		while (mlx->map[j][i])
		{
			if (mlx->map[j][i] == 'X')
			{
				mlx->player.xpos = j;
				mlx->player.ypos = i;
				mlx->player.xdir = -1;
				mlx->player.ydir = 0;
				mlx->player.mvspd = 0.2;
				mlx->player.rtspd = 0.05;
				mlx->player.sprint = 0.0;
				return (0);
			}
			i++;
		}
		j++;
	}
	ft_putendl("error : player not found in map");
	return (0);
}

int		ft_linelen(char *map_content, int k)
{
	int	len;

	len = 0;
	while (map_content[k] != '\n' && map_content[k] != '\0')
	{
		k++;
		len++;
	}
	return (len);
}

int		ft_checkchar(char *map_content)
{
	int	i;

	i = 0;
	while (map_content[i] != '\0')
		i++;
	map_content[i - 1] = '\0';
	i = -1;
	while (map_content[i++])
	{
		if (map_content[i] != '\n' && map_content[i] != '0'
				&& map_content[i] != '1' && map_content[i]
				!= 'X' && map_content[i] != '\0')
		{
			ft_putendl("error: invalid characters in map");
			return (0);
		}
	}
	if (ft_borders(map_content, 0) == -1)
	{
		ft_putendl("error: map must have borders");
		return (0);
	}
	return (0);
}
