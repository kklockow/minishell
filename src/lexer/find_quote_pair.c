/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_quote_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:15:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/27 19:25:44 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_closing_quote(char quote, t_lexer *lexer, int *end_of_quote)
static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type);

int	find_quote_pair(t_lexer *lexer)
{
	int	end_of_quote;

	if (lexer->input[lexer->pos] == '\"')
	{
		find_closing_quote('\"', lexer, &end_of_quote);
	}
	if (lexer->input[lexer->pos] == '\'')
	{
		find_closing_quote('\'', lexer, &end_of_quote);
			return (false);
	}
	return (0);
}

static void	find_closing_quote(char quote, t_lexer *lexer, int *end_of_quote)
{
	int		i;
	int		found_closing_quote;

	i = lexer->pos + 1;
	found_closing_quote = false;
	while (found_closing_quote == false && lexer->input[i])
	{
		if (lexer->input[i] == quote)
		{
			found_closing_quote = true;
			*end_of_quote = i - lexer->pos;
		}
		i++;
	}
	if (found_closing_quote == false)
		return (-1); //free
	return (true);
}

static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type)
{
	t_data	*last_data;
	int		pos_after_token;

	pos_after_token = lexer->pos + token_len + 1;
	last_data = lexer->head;
	go_to_last_lexer_node(last_data);
	last_data->token_len = token_len - 1;
	last_data->next = NULL;
	last_data->str = ft_substr(lexer->input,
			(lexer->pos + 1), (lexer->pos + token_len - 1));
	if (lexer->input[pos_after_token] == ' ')
		last_data->space = true;
	else
		last_data->space = false;
	if (token_type == '\'')
		last_data->type = SINGLE_QUOTE;
	else
		last_data->type = DOUBLE_QUOTE;
}
