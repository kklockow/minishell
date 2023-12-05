/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_same_token_sequences.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:58:14 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/05 12:24:52 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	validate_token_order(t_data *data, t_type token, int *error);

void	check_same_token_sequences(t_parser *parser)
{
	int		error_accured;
	t_data	*tmp_datat;

	error_accured = false;
	tmp_datat = parser->lexer->head;
	while (tmp_datat->next != NULL && error_accured == false)
	{
		validate_token_order(tmp_datat, PIPE, &error_accured);
		validate_token_order(tmp_datat, LESS, &error_accured);
		validate_token_order(tmp_datat, GREATER, &error_accured);
		validate_token_order(tmp_datat, DOUBLE_LESS, &error_accured);
		validate_token_order(tmp_datat, DOUBLE_GREAT, &error_accured);
		tmp_datat = tmp_datat->next;
	}
	return ;
}

static void	validate_token_order(t_data *data, t_type token, int *error)
{
	if (data->type == token && data->next->type == token)
		return ((*error = true), print_syntax_error(data));
	return ;
}

