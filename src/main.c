/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/27 18:33:11 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*input;
	t_lexer	*lexer;

	lexer = malloc(sizeof(t_lexer));
	if (lexer == NULL)
		return (false);
	(void) ac;
	(void) av;
	while (1)
	{
		input = readline("minishell> ");
		if (input)
			add_history(input);
		else
			return (1);
		printf("\nINPUT: %s\n", input);
		set_up_lexer_struct(lexer, input);
		lexing(lexer);
//		if (ft_strcmp(input, "exit") == 0)
//			break ;
//		first_token = lexer(input);
//		parser()
		free(input);
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
