/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/13 13:24:30 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char		*input;
	t_lexer		*lexer;
	t_process	process;
	t_cmd		*command;
	t_shell		*shell;

	(void) ac;
	(void) av;
	input = NULL;
	shell = malloc(sizeof (t_shell));
	shell->envp = init_env(envp);
	while (1)
	{
		get_input(&input, &process);
		setup_structs(&command, &lexer, &process, input);
		lexing(lexer);
		command_table(lexer, command);
		free(input);
		executor_main(command, shell);
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
