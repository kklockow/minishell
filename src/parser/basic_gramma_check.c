/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_gramma_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 08:58:14 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/04 13:51:43 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_token_order(t_data *data, t_type token);

int	basic_gramma_check(t_lexer *lexer)
{
	t_data	*tmp_datat;

	tmp_datat = lexer->head;
	while (tmp_datat->next != NULL)
	{
		validate_token_order(tmp_datat, PIPE);
		validate_token_order(tmp_datat, LESS);
		validate_token_order(tmp_datat, GREATER);
		validate_token_order(tmp_datat, DOUBLE_LESS);
		validate_token_order(tmp_datat, DOUBLE_GREAT);
		tmp_datat = tmp_datat->next;
	}
	return (true);
}

static int	validate_token_order(t_data *data, t_type token)
{
	if (data->type == token && data->next->type == token)
		return (printf("syntax error near unexpected token `%s%s'", data->str, data->str), false);
	return (true);
}

