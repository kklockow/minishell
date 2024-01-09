/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:21 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 11:03:11 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_is_cat(t_data *data);
static int	next_token_is_heredoc(t_data *data);
static int	cat_with_flag(t_data *data);
static int	cat_flag(t_data *data);

void	heredoc_argument(t_data *data, t_cmd *command)
{
	if (next_token_is_heredoc(data) == true && data->type == WORD
			&& word_is_cat(data) == true)
		command->heredoc_as_argument = true;

}

static int	next_token_is_heredoc(t_data *data)
{
	if (data != NULL && data->next != NULL && data->next->type == DOUBLE_LESS)
		return (true);
	else if (data->next != NULL && data->next != NULL
			&& cat_with_flag(data) == true && data->next->next != NULL
			&& data->next->next->type == DOUBLE_LESS)
		return (true);
	return (false);
}

static int	word_is_cat(t_data *data)
{
	if (ft_strncmp(data->str, "cat", 3) == false && ft_strlen(data->str) == 3)
		return (true);
	return (false);
}

static int	cat_with_flag(t_data *data)
{
	if (word_is_cat(data) == true && cat_flag(data) == true)
		return (true);
	return (false);
}

static int	cat_flag(t_data *data)
{
	if (data != NULL && data->next != NULL && data->next->type == WORD
		&& data->next->str[0] == '-' && ft_strlen(data->next->str) == 2)
		return (true);
	return (false);
}
