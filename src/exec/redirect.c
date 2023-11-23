/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:37:28 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/23 14:45:36 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(t_cmd *c_table);
int	open_outfile(t_cmd *c_table);

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