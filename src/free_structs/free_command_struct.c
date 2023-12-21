/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:56:42 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 16:57:35 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_struct(t_cmd **command)
{
	t_cmd	*tmp;

	if (command == NULL)
		return ;
	while (*command != NULL)
	{
		tmp = (*command)->next;
		save_free((void **) &(*command)->cmd);
		save_free((void **) &(*command)->infile);
		save_free((void **) &(*command)->outfile);
		save_free((void **) &(*command)->heredoc);
		save_free((void **) &(*command)->heredoc);
		save_free((void **) command);
		*command = tmp;
	}
	command = NULL;
}
