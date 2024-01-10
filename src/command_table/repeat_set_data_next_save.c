/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_set_data_next_save.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:57:40 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/10 15:58:37 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_repeat_check(int *repead, t_data *data);
void	get_repeat_times(int *repeat, t_data *data);

void	repeat_set_data_next_save(t_data **data)
{
	int		repeat;

	repeat = 0;
	get_repeat_times(&repeat, *data);
	while (repeat--)
	{
		if ((*data) != NULL)
			*data = (*data)->next;
	}
}

void	get_repeat_times(int *repeat, t_data *data)
{
	if (data->type == PIPE)
		*repeat = 1;
	else if (is_redirect(data) == true)
		redirect_repeat_check(repeat, data);
	else
		*repeat = 1;
}

void	redirect_repeat_check(int *repead, t_data *data)
{
	if (is_redirect(data) == true && data->next != NULL
		&& data->next->type == WORD)
		*repead = 2;
	else
		*repead = 1;
}
