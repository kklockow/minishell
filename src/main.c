/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/17 14:38:42 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_coordinate coordinate;

	(void) av;
	if (ac != 1)
	{
		ft_putstr_fd("ERROR: minishell takes no input parameter" , 2);
		return (false);
	}
	coordinate.first_set_up = true;
	while (1)
	{
		get_input(&coordinate);
		setup_structs(&coordinate,envp);
		lexing(coordinate.parser->lexer);
		command_table(coordinate.parser);
		executor_main(coordinate.parser->command, coordinate.shell);
		// free(input);
	}
	return (0);
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
