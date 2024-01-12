/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 16:09:54 by kklockow         ###   ########.fr       */
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
		unlink(".heredoc");
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
