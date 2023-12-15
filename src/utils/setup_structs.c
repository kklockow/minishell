/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:47:13 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 11:33:17 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_process(t_coordinate *coordinate);
static void	allocate_structs(t_coordinate *coordinate);
static void	first_set_up(t_coordinate *coordinate, char **envp);
static void	set_structs(t_coordinate *coordinate);

void	setup_structs(t_coordinate *coordinate, char **envp)
{
	if (coordinate->process.time_to_setup == false)
		return ;
	set_process(coordinate);
	first_set_up(coordinate, envp);
	allocate_structs(coordinate);
	set_structs(coordinate);
	return ;
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
	coordinate->parser->lexer = ft_calloc(1, sizeof(t_lexer));
	coordinate->parser->command = ft_calloc(1, sizeof(t_cmd));
}

static void	first_set_up(t_coordinate *coordinate, char **envp)
{
	if (coordinate->first_set_up == false)
		return ;
	coordinate->shell = ft_calloc(1, sizeof(t_shell));
	if (coordinate->shell == NULL)
		return ;//stop
	coordinate->shell->envp = init_env(envp);
	coordinate->first_set_up = false;
}

static void	set_structs(t_coordinate *coordinate)
{
	coordinate->parser->error_accured = false;
	coordinate->parser->shell = coordinate->shell;
	coordinate->parser->shell->process = &coordinate->process;
	coordinate->parser->lexer->shell = coordinate->shell;
	coordinate->parser->lexer->input = coordinate->input;
}
