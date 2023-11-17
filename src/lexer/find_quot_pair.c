/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_quot_pair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:15:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/17 15:27:58 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_closing_quot(char quot, t_lexer *lexer);
static void	set_node();

int find_quot_pair(t_lexer *lexer)
{
	if (lexer->input[lexer->pos] == '\"')
	{
		if (find_closing_quot('\'', lexer) == false)
			return (false);
	}
	if (lexer->input[lexer->pos] == '\'')
	{
		if (find_closing_quot('\"', lexer) == false)
			return (false);
	}
	return (0);
}

static int	find_closing_quot(char quot, t_lexer *lexer)
{
	int		i;
	int		found_closing_quot;

	i = lexer->pos;
	found_closing_quot = false;
	while (lexer->input[i] != quot )
	{
		i++;
		if (lexer->input[i] == quot)
			found_closing_quot = true;
	}
	if (found_closing_quot == false)
		return (free_struct(), false);
	if (allocate_node() == false)
		return (false);
	
	return (false);
}

static int set_node()
{
	
}

static int	allocate_node(t_lexer *lexer)
{
	lexer->head = malloc(sizeof(t_lexer));
	if (lexer->head == NULL)
		return (free_struct(), fasle);
	
}
