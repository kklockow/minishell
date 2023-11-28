/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_single_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:25:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/28 10:43:55 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_node(t_lexer *lexer, char token);
static void	get_token(char token, t_data *data);

int	get_single_tokens(t_lexer *lexer, char token)
{
	if (lexer->input[lexer->pos] != token
		|| lexer->process.time_to_lex == false)
		return (false);
	if (add_token_node(lexer) == false)
		return (false);
	fill_node(lexer, token);
	return (true);
}

static void	fill_node(t_lexer *lexer, char token)
{
	t_data	*fill_node;

	fill_node = go_to_last_lexer_node(lexer->head);
	get_token(token, fill_node);
	fill_node->next = NULL;
	fill_node->token_len = 1;
	lexer->pos++;
}

static void	get_token(char token, t_data *data)
{
	if (token == '>')
		data->type = GREATER;
	else if (token == '<')
		data->type = LESS;
	else if (token == '|')
		data->type = PIPE;
}
