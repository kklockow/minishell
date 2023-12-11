/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_roules_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 15:01:48 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/11 15:21:34 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_first_token_pipe(t_parser *parser);
static void	pipe_surrounding_check(t_data *data, int *error_accured);

void	pipe_roules_check(t_parser *parser)
{
	t_data *data;

	data = parser->lexer->head;
	is_first_token_pipe(parser);
	while (data != NULL && parser->error_accured == false)
	{
		if (data->next != NULL && data->next->type == PIPE)
			pipe_surrounding_check(data, &parser->error_accured);
//		if (data->type == PIPE && data->next == NULL)
//			return (parser->error_accured = true, print_syntax_error(data));
		data = data->next;
	}
}

static int is_first_token_pipe(t_parser *parser)
{
	if (parser->lexer->head == NULL)
		return false;
	if (parser->lexer->head->type == PIPE)
	{
		print_syntax_error(parser->lexer->head);
		parser->error_accured = true;
		return (true);
	}
	return (false);
}

static void	pipe_surrounding_check(t_data *data, int *error_accured)
{
	if (is_redirect(data) == true)
		return (*error_accured = true, print_syntax_error(data));
	else if (data->next->next == NULL && data->next->type == PIPE)
		return (*error_accured = true, print_syntax_error(data));
	else if (data->next->next != NULL && data->next->next->type == PIPE)
		return (*error_accured = true, print_syntax_error(data));
}
