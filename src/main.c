/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:04 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/15 13:12:27 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*input;
	t_struct tokens;

	create token 

	while (1)
	{
		input = readline("minishell> ");
		if (input)
			add_history(input);
		else
			return (1);
		if (ft_strcmp(input, "exit") == 0)
			break ;
		first_token = lexer(input);
		parser()
		free(input);
	}
	free(input);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	init_shell(....)
	if (start_loop(...) == NULL)
		error
	free
}
