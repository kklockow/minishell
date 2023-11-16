/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/16 18:24:00 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	executor(t_cmd *c_table, char **envp);
int	redirect(t_cmd *c_table);
int	open_infile(t_cmd *c_table);
int	open_outfile(t_cmd *c_table);

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
			printf("COMMAND\n");
			current_cmd = current_cmd->next;
		}
	}
	waitpid(pid, 0, 0);
	return (0);
}

int	redirect(t_cmd *c_table)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_infile(c_table);
	fd_out = open_outfile(c_table);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	return (0);
}

int	open_infile(t_cmd *c_table)
{
	int	fd;

	if (c_table->heredoc == 1)
		printf("heredoc\n");
	else
		fd = open(c_table->infile, O_RDONLY, 0644);
	if (fd == -1)
		return (1);
	return (fd);
}

int	open_outfile(t_cmd *c_table)
{
	int	fd;

	if (c_table->append == 1)
		fd = open(c_table->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(c_table->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (1);
	return (fd);
}
