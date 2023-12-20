/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/20 15:48:13 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_coordinate coordinate;

	catch_signals(&coordinate);
	input_check(ac, av, &coordinate);
	while (coordinate.run_loop == true)
	{
		get_input(&coordinate);
		setup_structs(&coordinate,envp);
		lexing(coordinate.parser->lexer, &coordinate.process);
		command_table(coordinate.parser, &coordinate.process);
		executor_main(coordinate.parser, &coordinate.process);
		// free(input);
	}
	return (coordinate.shell->exit_code);
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
