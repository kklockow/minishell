/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:26:16 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/01 18:13:59 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_newline_delimiter(char *delimiter);
int			fill_here_doc(char *delimiter, int *pipefd);
char		*ft_strjoin_add_newline(char *s1, char *s2);

int	here_doc_handling(char *delimiter)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (fill_here_doc(delimiter, pipefd) == -1)
			return (-1);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, 0, 0);
	return (pipefd[0]);
}

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
		if (ft_strncmp(delimiter, line, ft_strlen(delimiter)) == 0)
			break ;
		here_doc_str = ft_strjoin_add_newline(here_doc_str, line);
	}
	free(line);
	i = 0;
	putstr_error(here_doc_str);
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
