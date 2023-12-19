/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node_add_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:56:50 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/18 16:02:58 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	allocate_command_node(t_cmd **command, int *error_accured);
static void	go_to_last_command_node(t_cmd **command);

void	command_node_add_back(t_cmd **command, t_parser *parser)
{
	t_cmd	*new_command;
	t_cmd	*tmp_parser;

	tmp_parser = *command;
	allocate_command_node(&new_command, &parser->error_accured);
	go_to_last_command_node(&tmp_parser);
	tmp_parser->next = new_command;
	*command = new_command;
}

static void	allocate_command_node(t_cmd **command, int *error_accured)
{
	*command = ft_calloc(1, sizeof(t_cmd));
	if (*command == NULL)
	{
		perror("");
		*error_accured = true;
		return ; //free
	}
}

static void	go_to_last_command_node(t_cmd **command)
{
	t_cmd *current;

	current = *command;
	while (current != NULL)
	{
		if (current->next == NULL)
		{
			*command = current;
			return ;
		}
		current = current->next;
	}
}
