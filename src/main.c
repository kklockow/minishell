/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/12 14:08:10 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char		*input;
	t_lexer		*lexer;
	t_process	process;
	t_cmd		*command;

	(void) ac;
	(void) av;
	input = NULL;
	while (1)
	{
		get_input(&input, &process);
		setup_structs(&command, &lexer, &process, input);
		lexing(lexer);
		command_table(lexer, command);
//		if (ft_strcmp(input, "exit") == 0)
//			break ;
//		first_token = lexer(input);
//		parser()
		free(input);
		//reset_process
	}
	free(input);
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
