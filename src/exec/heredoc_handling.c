/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:26:16 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/11 16:42:26 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			fill_here_doc(char *delimiter, int heredoc);
char		*ft_strjoin_add_newline(char *s1, char *s2);

//This function sets up a pipe, forks a child process, and fills the pipe with
//user input until a specified delimiter is encountered. The parent process
//waits for the child process to finish, closes the write end of the pipe, and
//returns the read end of the pipe.

int	here_doc_handling(char *delimiter)
{
	int		heredoc;

	handle_signal_in_child();
	heredoc = open(".heredoc", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fill_here_doc(delimiter, heredoc) == -1)
		exit(-1);
	heredoc = open(".heredoc", O_RDONLY, 0644);
	return (heredoc);
}

//  * This function reads lines from the user and appends them to a string until
//  * the specified delimiter is encountered. It then writes the concatenated
//  * string to a pipe.

int	fill_here_doc(char *delimiter, int heredoc)
{
	char	*line;
	int		i;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(delimiter, line, ft_strlen(delimiter) + 1) == 0)
			break ;
		i = 0;
		while (line[i])
		{
			write(heredoc, &line[i], 1);
			i++;
		}
		write(heredoc, "\n", 1);
		free(line);
	}
	close(heredoc);
	return (0);
}

//This function concatenates two strings and adds a newline character at the
//end of the resulting string. It allocates memory for the new string, copies
//the content of the input strings, adds a newline character, and sets the null
//terminator at the end.

char	*ft_strjoin_add_newline(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	j = 0;
	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		dst[i] = s2[j];
		j++;
		i++;
	}
	dst[i] = '\n';
	dst[i + 1] = '\0';
	free(s1);
	free(s2);
	return (dst);
}
