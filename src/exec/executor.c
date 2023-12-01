/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/01 19:18:02 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		executor(t_cmd *c_table, char **envp);
void	handle_write_pipe(t_cmd *c_table, int *pipefd);
int		execute_command(t_cmd *current_cmd, char **envp);

void	putstr_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_cmd	*c_table;
	t_cmd	*new;
	t_cmd	*new2;
	char	*input;

	ac = 0;
	av = NULL;
	c_table = malloc(sizeof (t_cmd));
	c_table->cmd = "cat";
	c_table->infile = NULL;
	c_table->outfile = NULL;
	c_table->read_pipe = 0;
	c_table->write_pipe = 1;
	c_table->heredoc = "end";
	// c_table->next = NULL;
	new = malloc(sizeof (t_cmd));
	new->cmd = "grep s";
	new->infile = NULL;
	new->outfile = "outfile";
	new->read_pipe = 1;
	new->write_pipe = 0;
	c_table->next = new;
	// new->next = NULL;
	new2 = malloc(sizeof (t_cmd));
	new2->cmd = "ls";
	new2->infile = NULL;
	new2->outfile = NULL;
	new2->read_pipe = 1;
	new2->write_pipe = 0;
	c_table->next->next = new2;
	new2->next = NULL;
	// c_table = malloc(sizeof (t_cmd));
	// c_table->cmd = "grep s";
	// c_table->infile = "infile";
	// c_table->outfile = "outfile";
	// c_table->read_pipe = 0;
	// c_table->write_pipe = 0;
	// c_table->next = NULL;
	executor(c_table, envp);
	executor(c_table, envp);
	executor(c_table, envp);
	executor(c_table, envp);
	return (0);
}

int	executor(t_cmd *c_table, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	while (c_table != NULL)
	{
		if (c_table->write_pipe == 1)
		{
			if (pipe(pipefd) == -1)
				return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			redirect(c_table, pipefd);
			execute_command(c_table, envp);
		}
		handle_write_pipe(c_table, pipefd);
		if (c_table->heredoc != NULL)
			waitpid(pid, 0, 0);
		c_table = c_table->next;
	}
	waitpid(pid, 0, 0);
	return (0);
}

int	execute_command(t_cmd *current_cmd, char **envp)
{
	char	*path;
	char	**split;

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

void	handle_write_pipe(t_cmd *c_table, int *pipefd)
{
	if (c_table->write_pipe == 1)
	{
		if (c_table->next->read_pipe == 1)
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
