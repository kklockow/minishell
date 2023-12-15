/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater_and_smaler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:36 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/14 17:14:01 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_double_greater_or_smaler(t_lexer *lexer, int sign);
static void	fill_node(char sign, t_lexer *lexer);
static void detect_sign(t_lexer *lexer, char sign);
static void	update_lexer(t_lexer *lexer);

int	double_greater_and_smaler(t_lexer *lexer)
{
	if (lexer->shell->process->time_to_lex == false || lexer->set_token == true)
		return (false);
	detect_sign(lexer, '>');
	detect_sign(lexer, '<');
	return (true);
}

static void detect_sign(t_lexer *lexer, char sign)
{
	if (is_double_greater_or_smaler(lexer, sign) == true)
	{
		if (add_token_node(lexer) == false)
			return ; //free
		fill_node(sign, lexer);
		update_lexer(lexer);
	}
}

static int	is_double_greater_or_smaler(t_lexer *lexer, int sign)
{
	if (lexer->input[lexer->pos] == sign &&
		lexer->input[lexer->pos + 1] == sign)
		return (true);
	return (false);
}
static void	fill_node(char sign, t_lexer *lexer)
{
	t_data	*data;

	data = go_to_last_lexer_node(lexer->head);
	if (sign == '>')
	{
		data->str = ft_strdup(">>");
		data->type = DOUBLE_GREAT;
	}
	else if (sign == '<')
	{
		data->str = ft_strdup("<<");
		data->type = DOUBLE_LESS;
	}
	if (lexer->input[lexer->pos + 2] == ' ')
		data->space = true;
	else
		data->space = false;
	data->token_len = 2;
	data->next = NULL;
}

static void	update_lexer(t_lexer *lexer)
{
	lexer->set_token = true;
	lexer->pos += 2;
}
