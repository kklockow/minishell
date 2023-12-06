/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/06 15:33:43 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		executor_with_pipes(t_cmd *c_table, char **envp);
void	handle_pipe(t_cmd *c_table, int *pipefd);
int		execute_command(t_cmd *current_cmd, char **envp);
int		executor_main(t_cmd *c_table, char **envp);
int		executor_no_pipes(t_cmd *c_table, char **envp);

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
	t_cmd	*new3;
	char	*input;
	int		i;
	char	**shell_envp;

	ac = 0;
	av = NULL;
	c_table = malloc(sizeof (t_cmd));
	c_table->cmd = "echo hallo sahne";
	c_table->infile = NULL;
	c_table->outfile = NULL;
	c_table->read_pipe = 0;
	c_table->write_pipe = 0;
	c_table->heredoc = NULL;
	c_table->next = NULL;
	// new = malloc(sizeof (t_cmd));
	// new->cmd = "grep bee";
	// new->infile = NULL;
	// new->outfile = NULL;
	// new->read_pipe = 1;
	// new->write_pipe = 1;
	// c_table->next = new;
	// new->next = NULL;
	// new2 = malloc(sizeof (t_cmd));
	// new2->cmd = "wc";
	// new2->infile = NULL;
	// new2->outfile = "outfile";
	// new2->read_pipe = 1;
	// new2->write_pipe = 0;
	// new2->append = 1;
	// c_table->next->next = new2;
	// new2->next = NULL;
	// new3 = malloc(sizeof (t_cmd));
	// new3->cmd = "ls";
	// new3->infile = NULL;
	// new3->outfile = NULL;
	// new3->read_pipe = 0;
	// new3->write_pipe = 0;
	// c_table->next->next->next = new3;
	// new3->next = NULL;
	// c_table = malloc(sizeof (t_cmd));
	// c_table->cmd = "grep s";
	// c_table->infile = "infile";
	// c_table->outfile = "outfile";
	// c_table->read_pipe = 0;
	// c_table->write_pipe = 0;
	// c_table->next = NULL;

	shell_envp = init_env(envp);
	// shell_envp = envp;
	i = 1;
	while (i < 5)
	{
		executor_main(c_table, shell_envp);
		printf("\nfinished %i\n\n\n", i);
		i++;
	}
	return (0);
}

int	executor_main(t_cmd *c_table, char **envp)
{
	if (c_table->next == NULL)
		executor_no_pipes(c_table, envp);
	else
		executor_with_pipes(c_table, envp);
	return (0);
}

int	executor_no_pipes(t_cmd *c_table, char **envp)
{
	pid_t	pid;

	if (check_builtin(c_table, envp) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			redirect(c_table, NULL);
			execute_command(c_table, envp);
		}
		if (c_table->heredoc != NULL)
			waitpid(pid, 0, 0);
		waitpid(pid, 0, 0);
	}
	else
		handle_builtin(c_table, envp);
	return (0);
}

int	executor_with_pipes(t_cmd *c_table, char **envp)
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
		handle_pipe(c_table, pipefd);
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

	handle_builtin(current_cmd, envp);
	split = ft_split(current_cmd->cmd, ' ');
	if (access(split[0], F_OK | X_OK) != 0)
		path = get_path(split[0], envp);
	else
		path = split[0];
	execve(path, split, envp);
	free(path);
	free_matrix(split);
	exit (1);
}

void	handle_pipe(t_cmd *c_table, int *pipefd)
{
	if (c_table->write_pipe == 1)
	{
		if (c_table->next->read_pipe == 1)
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}
