/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_rules_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:55:22 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 17:15:17 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	next_token_check(t_data *next, t_parser *parser);
static int	valide_token_after_redirect(t_data *data);
//static int	net_token_pipe_and_word(t_data *data);

void	redirect_roules_check(t_parser *parser)
{
	t_data	*data;

	if (parser->error_accured == true)
		return ;
	data = parser->lexer->head;
	while (data != NULL && parser->error_accured == false)
	{
		if (is_redirect(data) == true)
			next_token_check(data, parser);
		data = data->next;
	}
}

static void	next_token_check(t_data *data, t_parser *parser)
{
	if (data->next == NULL)
	{
		parser->error_accured = true;
		set_error_code(parser->shell, 258);
		syntax_error_print(data);
		return ;
	}
	else if (valide_token_after_redirect(data->next) == true)
		return ;
	else
	{
		parser->error_accured = true;
		set_error_code(parser->shell, 258);
		syntax_error_print(data);
	}
}
/*
   else if (net_token_pipe_and_word(data) == true)
   return ;
   */

static int	valide_token_after_redirect(t_data *data)
{
	if (data->type == WORD || data->type == DOUBLE_QUOTE
		|| data->type == SINGLE_QUOTE)
		return (true);
	return (false);
}
