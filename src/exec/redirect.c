/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:37:28 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/14 17:55:52 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input(t_cmd *c_table);
int	handle_output(t_cmd *c_table, int *pipefd);
int	open_infile(t_cmd *c_table);
int	open_outfile(t_cmd *c_table);

int	redirect(t_cmd *c_table, int *pipefd)
{
	if (handle_input(c_table) == -1)
		return (-1);
	if (handle_output(c_table, pipefd) == -1)
		return (-1);
	return (0);
}

//  * This function is responsible for handling input redirection for a command
//  * in the command table. If the command does not read from a pipe and has an
//  * input file or a heredoc specified, it opens the input file or creates a
//  * heredoc file descriptor. It then duplicates the file descriptor to the
//  * standard input and closes the file descriptor.

int	handle_input(t_cmd *c_table)
{
	int	fd_in;

	if (c_table->read_pipe == 0
		&& (c_table->infile != NULL || c_table->heredoc != NULL))
	{
		fd_in = open_infile(c_table);
		if (fd_in == -1)
			return (-1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	return (0);
}

//  * This function is responsible for opening the input file or heredoc for a
//  * command in the command table. If the command has a heredoc specified, it
//  * calls a function for handling heredoc content and returns the
//  * file descriptor. Otherwise, it opens the specified input file in
//  * read-only mode and returns the file descriptor.

int	open_infile(t_cmd *c_table)
{
	int	fd;

	fd = 0;
	if (c_table->heredoc != NULL)
		fd = here_doc_handling(c_table->heredoc);
	else
		fd = open(c_table->infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", c_table->infile);
		return (-1);
	}
	return (fd);
}

// This function is responsible for handling output redirection for a command
// in the command table. If the command writes to a pipe, it closes the read
// end of the pipe and duplicates the write end to the standard output. If the
// command has an output file specified, it opens the output file in write-only
// mode and duplicates the file descriptor to the standard output.

int	handle_output(t_cmd *c_table, int *pipefd)
{
	int	fd_out;

	if (c_table->write_pipe == 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (c_table->outfile != NULL)
	{
		fd_out = open_outfile(c_table);
		if (fd_out == -1)
			return (-1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}

//  * This function is responsible for opening the output file for a command
//  * in the command table. If the command has the append flag set, it opens
//  * the file in append mode; otherwise, it opens the file in truncate mode.

int	open_outfile(t_cmd *c_table)
{
	int	fd;

	fd = 1;
	if (c_table->append == 1)
		fd = open(c_table->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		fd = open(c_table->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}
