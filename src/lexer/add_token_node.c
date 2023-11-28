/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:24:26 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/28 11:36:31 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_token_node_back(t_lexer *lexer, t_data *new);

int	add_token_node(t_lexer *lexer)
{
	t_data	*new;

	new = malloc(sizeof(t_data));
	if (new == NULL)
		return (perror(""), free_struct_and_stop_lexing(&lexer), false);
	ft_bzero(new, sizeof(t_data));
	add_token_node_back(lexer, new);
	return (true);
}

static void	add_token_node_back(t_lexer *lexer, t_data *new)
{
	t_data	*last;

	if (lexer->head != NULL)
	{
		last = go_to_last_lexer_node(lexer->head);
		if (last)
			last->next = new;
	}
	else
		lexer->head = new;
}
