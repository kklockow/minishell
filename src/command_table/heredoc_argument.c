/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:21 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/07 22:49:19 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_is_cat(t_data *data);
static int	next_token_is_heredoc(t_data *data);

int	heredoc_argument(t_data *data)
{
	if (next_token_is_heredoc(data) == true && word_is_cat(data) == true
			&& data->type == WORD)
		return (true);
	return (false);
}

static int	next_token_is_heredoc(t_data *data)
{
	if (data != NULL && data->next != NULL && data->next->type == DOUBLE_LESS)
		return (true);
	return (false);
}

static int	word_is_cat(t_data *data)
{
	if (ft_strncmp(data->str, "cat", 3) == false && ft_strlen(data->str) == 3)
		return (true);
	return (false);
}
