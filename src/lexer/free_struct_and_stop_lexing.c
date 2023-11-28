/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_and_stop_lexing.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:59:52 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/28 11:29:56 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	stop_process(t_process *process);
static void	free_data_struct(t_data **data);
static void	save_free(void **ptr);

void	free_struct_and_stop_lexing(t_lexer **lexer)
{
	stop_process(&(*lexer)->process);
	free_data_struct(&(*lexer)->head);
}

static void	stop_process(t_process *process)
{
	process->time_to_lex = false;
	process->time_to_exec = false;
	process->time_to_pars = false;
}

static void	free_data_struct(t_data **data)
{
	t_data *tmp_data;

	while ((*data) != NULL)
	{
		tmp_data = (*data)->next;
		save_free((void*) &(*data)->str);
		save_free((void *)data);
		(*data) = tmp_data;
	}
}

static void	save_free(void **ptr)
{
	if (*ptr != 0)
		free(*ptr);
	*ptr = NULL;
}
