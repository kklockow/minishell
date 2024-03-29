/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_roules_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:01:48 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 17:14:04 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_token_pipe(t_parser *parser);
static void	pipe_surrounding_check(t_data *data, int *error_accured);

void	pipe_roules_check(t_parser *parser)
{
	t_data	*data;

	data = parser->lexer->head;
	is_first_token_pipe(parser);
	while (data != NULL && parser->error_accured == false)
	{
		if (data->next != NULL && data->next->type == PIPE)
			pipe_surrounding_check(data, &parser->error_accured);
		data = data->next;
	}
	if (parser->error_accured == true)
		set_error_code(parser->shell, 258);
}

static int	is_first_token_pipe(t_parser *parser)
{
	if (parser->lexer->head == NULL)
		return (false);
	if (parser->lexer->head->type == PIPE)
	{
		set_error_code(parser->shell, 258);
		syntax_error_print(parser->lexer->head);
		parser->error_accured = true;
		return (true);
	}
	return (false);
}

static void	pipe_surrounding_check(t_data *data, int *error_accured)
{
	if (is_redirect(data) == true)
		return (*error_accured = true, syntax_error_print(data));
	else if (data->next->next == NULL && data->next->type == PIPE)
		return (*error_accured = true, syntax_error_print(data));
	else if (data->next->next != NULL && data->next->next->type == PIPE)
		return (*error_accured = true, syntax_error_print(data));
}
