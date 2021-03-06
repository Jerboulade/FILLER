/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarere <jecarere@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 18:00:17 by jecarere          #+#    #+#             */
/*   Updated: 2019/10/31 18:00:18 by jecarere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

int	get_piece(t_game *game, int i, int j)
{
	if (get_next_line(0, &game->line) < 0)
		return (0);
	if ((game->strchr = ft_strchr(game->line, ' ')))
		game->pc.li = ft_atoi(game->strchr + 1);
	if ((game->strrchr = ft_strrchr(game->line, ' ')))
		game->pc.col = ft_atoi(game->strrchr + 1);
	if ((game->pc.li <= 0) || (game->pc.col <= 0))
		return (0);
	game->pc.size = game->pc.li * game->pc.col;
	if (!(game->pc.piece = ft_strnew(game->pc.size)))
		return (0);
	ft_strdel(&game->line);
	while (++i < game->pc.li)
	{
		if (get_next_line(0, &game->line) < 0)
			return (0);
		ft_strncpy(game->pc.piece + j, game->line, game->pc.col);
		j += game->pc.col;
		ft_strdel(&game->line);
	}
	return (1);
}

int	create_map(t_game *game)
{
	if ((game->strchr = ft_strchr(game->line, ' ')))
		game->map.li = ft_atoi(game->strchr + 1);
	if ((game->strrchr = ft_strrchr(game->line, ' ')))
		game->map.col = ft_atoi(game->strrchr + 1);
	if ((game->map.li <= 0) || (game->map.col <= 0))
		return (0);
	game->map.size = game->map.li * game->map.col;
	if (!(game->map.new_map = ft_strnew(game->map.size)))
		return (0);
	if (!(game->map.old_map = ft_strnew(game->map.size)))
		return (0);
	return (1);
}

int	get_map(t_game *game, int i, int j)
{
	if (get_next_line(0, &game->line) < 0)
		return (0);
	if ((!game->line) || (!game->lap && !create_map(game)))
	{
		ft_strdel(&game->line);
		return (0);
	}
	else
		ft_strcpy(game->map.old_map, game->map.new_map);
	ft_strdel(&game->line);
	if (get_next_line(0, &game->line) < 0)
		return (0);
	ft_strdel(&game->line);
	while (++i < game->map.li)
	{
		if (get_next_line(0, &game->line) < 0)
			return (0);
		ft_strncpy(game->map.new_map + j, game->line + 4, game->map.col);
		j += game->map.col;
		ft_strdel(&game->line);
	}
	return (1);
}

int	get_players(t_game *game)
{
	game->line = NULL;
	if (get_next_line(0, &game->line) < 0)
		return (0);
	if ((game->strchr = ft_strchr(game->line, 'p')))
		game->pl.player = *(game->strchr + 1);
	if ((game->pl.player != '1') && (game->pl.player != '2'))
	{
		ft_strdel(&game->line);
		return (0);
	}
	game->pl.player = (game->pl.player == '1') ? 'O' : 'X';
	game->op.opponent = (game->pl.player == 'O') ? 'X' : 'O';
	ft_strdel(&game->line);
	return (1);
}
