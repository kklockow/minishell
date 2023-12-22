/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:26:16 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/21 17:56:56 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			fill_here_doc(char *delimiter, int *pipefd);
char		*ft_strjoin_add_newline(char *s1, char *s2);

//This function sets up a pipe, forks a child process, and fills the pipe with
//user input until a specified delimiter is encountered. The parent process
//waits for the child process to finish, closes the write end of the pipe, and
//returns the read end of the pipe.

int	here_doc_handling(char *delimiter)
{
	// pid_t	pid;
	int		pipefd[2];

	signal(SIGINT, SIG_DFL);
	if (pipe(pipefd) == -1)
		return (-1);
	// pid = fork();
	// if (pid < 0)
	// 	return (-1);
	// if (pid == 0)
	// {
	if (fill_here_doc(delimiter, pipefd) == -1)
		exit(-1);
		// exit(0);
	// }
	// waitpid(pid, 0, 0);
	close(pipefd[1]);
	return (pipefd[0]);
}

//  * This function reads lines from the user and appends them to a string until
//  * the specified delimiter is encountered. It then writes the concatenated
//  * string to a pipe.

int	fill_here_doc(char *delimiter, int *pipefd)
{
	char	*line;
	char	*here_doc_str;
	int		i;

	here_doc_str = malloc(sizeof (char) * 1);
	here_doc_str[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		here_doc_str = ft_strjoin_add_newline(here_doc_str, line);
	}
	free(line);
	i = 0;
	while (here_doc_str[i])
	{
		write(pipefd[1], &here_doc_str[i], 1);
		i++;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	free(here_doc_str);
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
