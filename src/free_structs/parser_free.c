/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:38:55 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 14:09:47 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_command_struct(t_cmd **command);

void	parser_free(t_parser **parser)
{
	free_command_struct(&(*parser)->command);
	(*parser)->shell = NULL;
	save_free((void **) parser);
}

static void	free_command_struct(t_cmd **command)
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
