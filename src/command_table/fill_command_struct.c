/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:26:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/12 15:48:13 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_command(t_cmd *command, t_data *data);
static void	check_for_pipe(t_cmd **command, t_data **data, t_parser *parser);
static void	detect_redirect(t_cmd *command, t_data **data);

void	fill_command_struct(t_parser *parser)
{
	t_data *data;
	t_cmd *command;
	t_cmd *test_print;

	data = parser->lexer->head;
	command = parser->command;
	test_print = parser->command;
	while (data != NULL && parser->error_accured == false)
	{
		check_for_pipe(&command, &data, parser);
		detect_redirect(command, &data);
		fill_command(command, data);
		data = data->next;
	}
	while (test_print != NULL)
	{
		printf("\ncommand: %s\n", test_print->cmd);
		printf("heredoc: %s\n", test_print->heredoc);
		printf("infile: %s\n", test_print->infile);
		printf("outfile: %s\n", test_print->outfile);
		test_print = test_print->next;
	}
}


static void	check_for_pipe(t_cmd **command, t_data **data, t_parser *parser)
{
	if ((*data)->type != PIPE)
		return ;
	(*command)->write_pipe = true;
	command_node_add_back(command, parser);
	(*command)->read_pipe = true;
	*data = (*data)->next;
}

static void	fill_command(t_cmd *command, t_data *data)
{
	command->cmd = ft_strjoin_mod(command->cmd, data->str);
}

static void	detect_redirect(t_cmd *command, t_data **data)
{
	if (is_redirect(*data) == false)
		return ;
	else if ((*data)->type == DOUBLE_LESS)
		command->heredoc = ft_strdup((*data)->next->str);
	else if ((*data)->type == DOUBLE_GREAT)
		command->append = true;
	else if ((*data)->type == GREATER)
		command->outfile = ft_strdup((*data)->next->str);
	else if ((*data)->type == LESS)
		command->infile = ft_strdup((*data)->next->str);
	*data = (*data)->next;

}
