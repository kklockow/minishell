/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_quote_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:15:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/30 13:56:58 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_closing_quote(char quote, t_lexer *lexer, int *end_of_quote);
static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type);
static void	quote_error();

int	find_quote_pair(t_lexer *lexer)
{
	int	end_of_quote;

	if (lexer->process. time_to_lex == false)
		return (false);
	if (lexer->input[lexer->pos] == '\"')
	{
		find_closing_quote('\"', lexer, &end_of_quote);
		if (end_of_quote == -1)
			return (quote_error(), free_struct_and_stop_lexing(&lexer), false);
		if (add_token_node(lexer) == false)
			return (false);
		set_up_data_struct(lexer, end_of_quote, '\"');
	}
	if (lexer->input[lexer->pos] == '\'')
	{
		find_closing_quote('\'', lexer, &end_of_quote);
		if (end_of_quote == -1)
			return (quote_error(), free_struct_and_stop_lexing(&lexer), false);
		if (add_token_node(lexer) == false)
			return (false);
		set_up_data_struct(lexer, end_of_quote, '\'');
	}
	return (0);
}

static void	find_closing_quote(char quote, t_lexer *lexer, int *end_of_quote)
{
	int		i;
	int		found_closing_quote;

	i = lexer->pos;
	found_closing_quote = false;
	*end_of_quote = -1;
	while (found_closing_quote == false && lexer->input[i])
	{
		if (lexer->input[i + 1] == quote)
		{
			found_closing_quote = true;
			*end_of_quote = i - lexer->pos;
		}
		i++;
	}
}

static void	set_up_data_struct(t_lexer *lexer, int token_len, char token_type)
{
	t_data	*last_data;
	int		pos_after_token;

	pos_after_token = lexer->pos + token_len + 2;
	last_data = lexer->head;
	last_data = go_to_last_lexer_node(lexer->head);
	last_data->token_len = token_len;
	last_data->next = NULL;
	last_data->str = ft_substr(lexer->input,
			(lexer->pos + 1), (token_len));
	if (lexer->input[pos_after_token] == ' ')
		last_data->space = true;
	else
		last_data->space = false;
	if (token_type == '\'')
		last_data->type = SINGLE_QUOTE;
	else
		last_data->type = DOUBLE_QUOTE;
	lexer->pos = pos_after_token;
}

static void	quote_error()
{
	ft_putstr_fd("Error: no closing Quote found\n", 2);
}
