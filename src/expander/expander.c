/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:54:21 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/08 13:24:40 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	expander(t_shell *shell, t_cmd *c_table);

int	main(int ac, char **av, char **envp)
{
	t_cmd	*c_table;
	t_cmd	*new;
	t_cmd	*new2;
	t_cmd	*new3;
	t_shell	*shell;
	char	*input;
	int		i;
	char	**shell_envp;

	ac = 0;
	av = NULL;
	c_table = malloc(sizeof (t_cmd));
	c_table->cmd = "$new";
	c_table->infile = NULL;
	c_table->outfile = NULL;
	c_table->read_pipe = 0;
	c_table->write_pipe = 0;
	c_table->heredoc = NULL;
	c_table->next = NULL;
	shell = malloc(sizeof (t_shell *));
	shell->envp = init_env(envp);
	expander(shell, c_table);
	printf("%s\n", c_table->cmd);
	return (0);
}

int	expander(t_shell *shell, t_cmd *c_table)
{
	return (0);
}
