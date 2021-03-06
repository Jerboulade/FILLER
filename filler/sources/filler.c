/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarere <jecarere@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:48:57 by jecarere          #+#    #+#             */
/*   Updated: 2020/03/11 17:55:40 by jecarere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

void	end_game(t_game *game)
{
	ft_strdel(&game->map.new_map);
	ft_strdel(&game->map.old_map);
	ft_putnbr(0);
	ft_putchar(' ');
	ft_putnbr(0);
	ft_putchar('\n');
	exit(0);
}

void	reset(t_game *game, int end)
{
	game->pc.li = 0;
	game->pc.col = 0;
	game->pc.size = 0;
	ft_strdel(&game->pc.piece);
	ft_intdel(&game->pc.blok);
	ft_frintab(game->pc.place, game->pc.n_place + 1);
	game->pc.n_blok = 0;
	game->pl.n_blok = 0;
	ft_intdel(&game->pl.blok);
	game->op.n_last = 0;
	ft_intdel(&game->op.last);
	if (end)
		end_game(game);
	game->lap++;
	game->top_dist = 0;
	game->top_surround = 0;
	game->top_i = 0;
}

int		start_game(t_game *game)
{
	if (!(get_players(game)))
		reset(game, 1);
	while (19)
	{
		if (!(get_map(game, -1, 0)))
			reset(game, 1);
		if (!(get_piece(game, -1, 0)))
			reset(game, 1);
		if (!(parse_map(game, -1, -1)))
			reset(game, 1);
		if (game->lap)
			compare_map(game);
		if (!(parse_piece(game)))
			reset(game, 1);
		if (!(get_placement(game, game->pl.blok, game->pl.n_blok, -1)))
			reset(game, 1);
		put_piece(game);
		reset(game, 0);
	}
	return (1);
}

int		main(void)
{
	t_game game;

	init_game(&game);
	start_game(&game);
	return (0);
}
