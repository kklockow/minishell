/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/20 17:19:05 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	int				exit_code;
	t_coordinate	coordinate;

	catch_signals(&coordinate);
	input_check(ac, av, &coordinate);
	first_setup(&coordinate, envp);
	while (coordinate.run_loop == true)
	{
		get_input(&coordinate);
		setup_structs(&coordinate);
		lexing(coordinate.parser->lexer, &coordinate.process);
		command_table(coordinate.parser, &coordinate.process);
		free_lexer_struct(&coordinate.parser->lexer);
		parser_free(&coordinate.parser);
		executor_main(coordinate.command, coordinate.shell);
		free_command_struct(&coordinate.command);
	}
	exit_code = coordinate.shell->exit_code;
	shell_struct_free(&coordinate.shell);
	return (exit_code);
}

/*
int	main(int ac, char **av, char **envp)
{
	init_shell(....)
	if (start_loop(...) == NULL)
		error
	free
}
*/
