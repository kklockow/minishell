/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 15:56:43 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 17:10:53 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	next_token_pipe(t_data *data);
static int	end_of_command(t_data *data);
static int	space_after_token(t_data *data);

int	add_space_check(t_data *data)
{
	if (next_token_pipe(data) == false && end_of_command(data) == false
		&& space_after_token(data) == true)
		return (true);
	return (false);
}

static int	next_token_pipe(t_data *data)
{
	if (data != NULL && data->next != NULL && data->next->type == PIPE)
		return (true);
	return (false);
}

static int	end_of_command(t_data *data)
{
	if (data != NULL && data->next == NULL)
		return (true);
	return (false);
}

static int	space_after_token(t_data *data)
{
	if (data != NULL && data->space == true)
		return (true);
	return (false);
}
