/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_command_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:26:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/17 14:49:11 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_command(t_cmd *command, t_data *data);
static void	check_for_pipe(t_cmd **command, t_data **data, t_parser *parser);
static void	detect_redirect(t_cmd *command, t_data **data);
static void	repeat_set_next_save(t_data **data, int repeat);

void	fill_command_struct(t_parser *parser)
{
	t_data *data;
	t_cmd *command;

	data = parser->lexer->head;
	command = parser->command;
	while (data != NULL && parser->error_accured == false)
	{
		detect_redirect(command, &data);
		check_for_pipe(&command, &data, parser);
		fill_command(command, data);
		repeat_set_next_save(&data, 1);
	}
	/*
	t_cmd *test_print;
	test_print = parser->command;
	while (test_print != NULL)
	{
		printf("\ncommand: [%s]\n", test_print->cmd);
		printf("heredoc: [%s]\n", test_print->heredoc);
		printf("infile: [%s]\n", test_print->infile);
		printf("outfile: [%s]\n", test_print->outfile);
		printf("expand: %d\n", test_print->append);
		printf("write: %d\n", test_print->write_pipe);
		printf("read: %d\n", test_print->read_pipe);
		test_print = test_print->next;
	}
	*/
}

static void	check_for_pipe(t_cmd **command, t_data **data, t_parser *parser)
{
	if (*data == NULL || (*data)->type != PIPE)
		return ;
	(*command)->write_pipe = true;
	command_node_add_back(command, parser);
	(*command)->read_pipe = true;
	repeat_set_next_save(data, 1);
}

static void	fill_command(t_cmd *command, t_data *data)
{
	if (data != NULL)
		command->cmd = ft_strjoin_mod(command->cmd, data->str);
	if (add_space_check(data) == true)
		command->cmd = ft_strjoin_mod(command->cmd, " ");
//	printf("token: %s\ncommane space: %d\n", data->str, data->space);
}

static void	detect_redirect(t_cmd *command, t_data **data)
{
	if (is_redirect(*data) == false)
		return ;
	else if ((*data)->type == DOUBLE_LESS)
		command->heredoc = ft_strdup((*data)->next->str);
	else if ((*data)->type == DOUBLE_GREAT)
	{
		command->outfile = ft_strdup((*data)->next->str);
		command->append = true;
	}
	else if ((*data)->type == GREATER)
		command->outfile = ft_strdup((*data)->next->str);
	else if ((*data)->type == LESS)
		command->infile = ft_strdup((*data)->next->str);
	repeat_set_next_save(data, 2);
}

static void	repeat_set_next_save(t_data **data, int repeat)
{
	while (repeat--)
	{
		if ((*data) != NULL)
			*data = (*data)->next;
	}
}
