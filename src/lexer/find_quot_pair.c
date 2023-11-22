/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_quot_pair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:15:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/22 17:19:10 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_closing_quot(char quot, t_lexer *lexer);
static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type);

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
	int		token_len;
	int		found_closing_quot;

	i = lexer->pos;
	token_len = 0;
	found_closing_quot = false;
	while (lexer->input[i] != quot && lexer->input[i])
	{
		i++;
		if (lexer->input[i] == quot && lexer->input[i])
		{
			found_closing_quot = true;
			token_len = i - lexer->pos;
		}
	}
	if (found_closing_quot == false)
		return (false); //free
	if (add_token_node(lexer) == false)
		return (false); //free
	set_up_data_struct(lexer, token_len, quot);
	return (true);
}
static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type)
{
	t_data	*last_data;
	int		pos_after_token;

	pos_after_token = lexer->pos + token_len + 1;
	last_data = lexer->head;
	go_to_last_lexer_node(last_data);
	last_data->token_len = token_len;
	last_data->next = NULL;
	last_data->str =
		ft_substr(lexer->input, lexer->pos, lexer->pos + token_len);
	if (lexer->input[pos_after_token] == ' ')
		last_data->space = true;
	else
		last_data->space = false;
	if (token_type == '\'')
		last_data->type = SINGLE_QUOTE;
	else
		last_data->type = DOUBLE_QUOTE;
}
