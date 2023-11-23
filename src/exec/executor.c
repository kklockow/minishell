/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/23 15:53:22 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor(t_cmd *c_table, char **envp);
int	execute_command(t_cmd *current_cmd, char **envp);

int	main(int ac, char **av, char **envp)
{
	t_cmd	*c_table;

	ac = 0;
	av = NULL;
	c_table = malloc(sizeof (t_cmd));
	c_table->cmd = "grep s";
	c_table->infile = "infile";
	c_table->outfile = "outfile";
	c_table->read_pipe = 0;
	c_table->write_pipe = 0;
	c_table->next = NULL;
	executor(c_table, envp);
	return (0);
}

int	executor(t_cmd *c_table, char **envp)
{
	t_cmd	*current_cmd;
	pid_t	pid;

	current_cmd = c_table;
	pid = fork();
	if (pid == 0)
	{
		while (current_cmd != NULL)
		{
			if (redirect(current_cmd) == 1)
				return (1);
			if (execute_command(current_cmd, envp) == 1)
				return (1);
			current_cmd = current_cmd->next;
		}
	}
	waitpid(pid, 0, 0);
	return (0);
}

int	execute_command(t_cmd *current_cmd, char **envp)
{
	char	*path;
	char	**split;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		split = ft_split(current_cmd->cmd, ' ');
		if (access(split[0], F_OK | X_OK) != 0)
			path = get_path(split[0], envp);
		else
			path = split[0];
		execve(path, split, envp);
		free(path);
		free_matrix(split);
		return (1);
	}
	return (0);
}
