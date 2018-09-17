/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnepfumb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 09:24:59 by mnepfumb          #+#    #+#             */
/*   Updated: 2017/12/11 15:38:21 by mnepfumb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_start(char *mapname, int *fd)
{
	if (BUFF_SIZE < 1)
	{
		ft_putstr_fd("error: BUFF_SIZE must be greater than 0\n", 2);
		return (0);
	}
	if ((*fd = open(mapname, O_RDONLY)) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (0);
	}
	return (1);
}

static char		*ft_getbuf(char *mapname, int *nbl)
{
	int			fd;
	char		*map_content;
	char		*line;

	map_content = ft_strnew(1);
	if (ft_start(mapname, &fd) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
		map_content = ft_strjoin(ft_strjoin(map_content, line), "\n");
	free(line);
	if (ft_checkchar(map_content) == -1)
		return (NULL);
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno)));
		return (NULL);
	}
	return (map_content);
}

static char		**ft_getmap(char *map_content, int nbl, int j)
{
	int			i;
	int			k;
	char		**map;

	k = 0;
	if (!map_content)
		return (NULL);
	if (!(map = (char **)malloc(sizeof(char *) * nbl)))
		return (NULL);
	while (map_content[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(map[j] = (char *)malloc(sizeof(char) *
						ft_linelen(map_content, k))))
			return (NULL);
		while (map_content[k] != '\n' && map_content[k] != '\0')
			map[j][i++] = map_content[k++];
		map[j][i] = '\0';
		k++;
		j++;
	}
	return (map);
}

static t_mlx	*init_mlx(char *mapname)
{
	t_mlx	*mlx;
	char	*map_content;
	char	*name;

	name = ft_strjoin("wolf3d :", mapname);
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (NULL);
	mlx->nbl = 0;
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, name);
	free(name);
	mlx->d = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line,
			&mlx->endian);
	map_content = ft_getbuf(mapname, &(mlx->nbl));
	if ((mlx->map = ft_getmap(map_content, mlx->nbl, 0)) == NULL)
		return (NULL);
	free(map_content);
	if (ft_player_init(mlx, 0, 0) == -1)
		return (NULL);
	mlx->cam.xplane = 0.0;
	mlx->cam.yplane = 0.6;
	mlx->dh = 2.0;
	return (mlx);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;

	if (argc != 2 || !argv[1])
	{
		ft_putendl("usage: ./wolf3d input_file");
		return (0);
	}
	if ((mlx = init_mlx(argv[1])) != NULL)
	{
		mlx_hook(mlx->win, 17, 0, ft_close, mlx);
		ft_draw(mlx);
		mlx_hook(mlx->win, KEYPRESS, KEYPRESSMASK, key_press, mlx);
		mlx_loop(mlx->mlx);
		mlx_destroy_window(mlx->mlx, mlx->win);
	}
	return (0);
}
