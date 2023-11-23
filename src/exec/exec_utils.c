/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:56:29 by kklockow          #+#    #+#             */
/*   Updated: 2023/11/23 14:59:15 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_envp(char **envp, char *str, int *pipefd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return ;
		i++;
	}
	write(STDERR_FILENO, "env: ", 5);
	i = 0;
	while (str[i])
	{
		write (STDERR_FILENO, &str[i], 1);
		i++;
	}
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	close (pipefd[0]);
	close (pipefd[1]);
	exit (0);
}

char	**get_possible_paths(char **envp)
{
	t_gpp	gpp;

	gpp.i = 0;
	while (envp[gpp.i] != NULL)
	{
		if (ft_strncmp(envp[gpp.i], "PATH", 4) == 0)
			break ;
		gpp.i++;
	}
	gpp.temp = malloc(sizeof(char) * (ft_strlen(envp[gpp.i]) - 4));
	if (!gpp.temp)
		return (0);
	gpp.j = 5;
	gpp.k = 0;
	while (envp[gpp.i][gpp.j])
	{
		gpp.temp[gpp.k] = envp[gpp.i][gpp.j];
		gpp.j++;
		gpp.k++;
	}
	gpp.possible_paths = ft_split(gpp.temp, ':');
	free(gpp.temp);
	return (gpp.possible_paths);
}

char	*get_path(char *cmd, char **envp, int *pipefd)
{
	char	**possible_paths;
	char	*path;
	char	*temp;
	int		i;

	check_envp(envp, cmd, pipefd);
	possible_paths = get_possible_paths(envp);
	if (!possible_paths)
		return (0);
	i = 0;
	while (possible_paths[i])
	{
		temp = ft_strjoin(possible_paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK | X_OK) != 0)
			i++;
		else
			return (path);
		free(path);
	}
	return (0);
}

void	free_matrix(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
	{
		free(to_free[i]);
		i++;
	}
	free (to_free[i]);
}
