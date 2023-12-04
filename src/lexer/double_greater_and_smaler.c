/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_greater_and_smaler.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:09:36 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 16:02:45 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_node(t_data *data, char sign, t_lexer *lexer);
static void detect_sign(t_lexer *lexer, char sign);

int	doenuble_greater_and_smaler(t_lexer *lexer)
{

	if (lexer->process.time_to_lex == false || lexer->set_token == true)
		return (false);
	detect_sign(lexer, '<');
	detect_sign(lexer, '>');
	return (true);
}
static void detect_sign(t_lexer *lexer, char sign)
{
	int		i;
	char	*input;
	t_data	*last_node;

	i = lexer->pos;
	input = lexer->input;
	if (input[i] == sign && input[i + 1] == sign)
	{
		if (add_token_node(lexer) == false)
			return ; //free
		last_node = go_to_last_lexer_node(lexer->head);
		fill_node(last_node, sign, lexer);
		lexer->set_token = true;
	}
}

static void	fill_node(t_data *data, char sign, t_lexer *lexer)
{
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
	if (lexer->input[lexer->pos + 1] == ' ')
		data->space = true;
	else
		data->space = false;
	data->token_len = 2;
	data->next = NULL;
}
