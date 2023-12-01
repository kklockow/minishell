/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:37:28 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/01 17:39:42 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(t_cmd *c_table);
int	open_outfile(t_cmd *c_table);

int	redirect(t_cmd *c_table, int *pipefd)
{
	int	fd_in;
	int	fd_out;

	if (c_table->read_pipe != 1)
	{
		fd_in = open_infile(c_table);
		if (fd_in == -1)
			return (-1);
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (c_table->write_pipe == 1)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		fd_out = open_outfile(c_table);
		if (fd_out == -1)
			return (-1);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (0);
}

int	open_infile(t_cmd *c_table)
{
	int	fd;

	fd = 0;
	if (c_table->heredoc != NULL)
		fd = here_doc_handling(c_table->heredoc);
	else
		fd = open(c_table->infile, O_RDONLY, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

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
