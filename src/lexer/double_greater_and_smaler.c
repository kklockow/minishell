/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater_and_smaler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:36 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/28 10:44:39 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_node(t_data *data, int token, t_lexer *lexer);

int	double_greater_and_smaler(t_lexer *lexer)
{
	int		i;
	char	*input;
	t_data	*last_node;

	if (lexer->process.time_to_lex == false)
		return (false);
	i = lexer->pos;
	input = lexer->input;
	if (input[i] == '>' && input[i + 1] == '>')
	{
		if (add_token_node(lexer) == false)
			return (false);
		last_node = go_to_last_lexer_node(lexer->head);
		fill_node(last_node, DOUBLE_GREAT, lexer);
	}
	if (input[i] == '<' && input[i + 1] == '<')
	{
		if (add_token_node(lexer) == false)
			return (false);
		last_node = go_to_last_lexer_node(lexer->head);
		fill_node(last_node, DOUBLE_LESS, lexer);
	}
	return (true);
}

static void	fill_node(t_data *data, int token, t_lexer *lexer)
{
	if (token == DOUBLE_GREAT)
	{
		data->str = ft_strdup(">>");
		data->type = DOUBLE_GREAT;
	}
	if (token == DOUBLE_LESS)
	{
		data->str = ft_strdup("<<");
		data->type = DOUBLE_LESS;
	}
	if (lexer->input[lexer->pos + 1] == ' ')
		data->space = true;
	else
		data->space = false;

	data->token_len = 2;
	data->next = NULL;
}

