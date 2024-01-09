/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:21 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 13:03:06 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_token_is_heredoc(t_data *data);

void	heredoc_argument(t_data *data, t_cmd *command)
{
	if (data->type == WORD && next_token_is_heredoc(data) == true)
		command->heredoc_as_argument = true;
}

static int	next_token_is_heredoc(t_data *data)
{
	if (data != NULL && data->next != NULL && data->next->type == DOUBLE_LESS)
		return (true);
	return (false);
}
