/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/11 16:35:42 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_shell	*shell;
	t_cmd	*c_table;

	ac = 0;
	av = NULL;
	c_table = malloc(sizeof (t_cmd));
	c_table->infile = "infile";
	c_table->outfile = "outfile";
	c_table->read_pipe = 0;
	c_table->write_pipe = 0;
	c_table->heredoc = NULL;
	c_table->next = NULL;
	shell = malloc(sizeof (t_shell));
	shell->envp = init_env(envp);
	while (1)
	{
		input = readline("minishell> ");
		if (input)
			add_history(input);
		else
			return (1);
		c_table->cmd = input;
		executor_main(c_table, shell);

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
