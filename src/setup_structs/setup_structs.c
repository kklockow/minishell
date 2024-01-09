/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:47:13 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 18:17:56 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_process(t_coordinate *coordinate);
static void	allocate_structs(t_coordinate *coordinate);
static void	set_structs(t_coordinate *coordinate);
static void	make_structs_global(t_coordinate *coordinate);

void	setup_structs(t_coordinate *coordinate)
{
	set_process(coordinate);
	if (coordinate->process.time_to_setup == false)
		coordinate->process.time_to_lex = false;
	allocate_structs(coordinate);
	set_structs(coordinate);
	make_structs_global(coordinate);
}

static void	set_process(t_coordinate *coordinate)
{
	coordinate->process.time_to_lex = true;
	coordinate->process.time_to_pars = false;
	coordinate->process.time_to_exec = false;
}

static void	allocate_structs(t_coordinate *coordinate)
{
	coordinate->parser = ft_calloc(1, sizeof(t_parser));
	if (coordinate->parser == NULL)
		return (stop_loop(coordinate), stop_process(&coordinate->process));
	coordinate->parser->lexer = ft_calloc(1, sizeof(t_lexer));
	if (coordinate->parser->lexer == NULL)
		return (stop_loop(coordinate), stop_process(&coordinate->process));
	coordinate->parser->command = ft_calloc(1, sizeof(t_cmd));
	if (coordinate->parser->command == NULL)
		return (stop_loop(coordinate), stop_process(&coordinate->process));
}

static void	set_structs(t_coordinate *coordinate)
{
	coordinate->parser->error_accured = false;
	coordinate->parser->shell = coordinate->shell;
	coordinate->parser->shell->process = &coordinate->process;
	coordinate->parser->lexer->shell = coordinate->shell;
	coordinate->parser->lexer->input = coordinate->input;
	coordinate->process.run_loop = &coordinate->run_loop;
	coordinate->command = coordinate->parser->command;
}

static void	make_structs_global(t_coordinate *coordinate)
{
	t_shell		**tmp_shell;
	t_cmd		**tmp_command;

	tmp_shell = get_shell_struct();
	*tmp_shell = coordinate->shell;
	tmp_command = get_command_struct();
	*tmp_command = coordinate->parser->command;
}
