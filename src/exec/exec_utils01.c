/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:56:29 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/10 12:15:51 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_strncmp(const char *s1, const char *s2, size_t n)
// {
// 	size_t			i;
// 	unsigned char	*s1c;
// 	unsigned char	*s2c;

// 	i = 0;
// 	s1c = (unsigned char *)s1;
// 	s2c = (unsigned char *)s2;
// 	while (n > 0 && (s1c[i] != '\0' || s2c[i] != '\0'))
// 	{
// 		if ((s1c[i] - s2c[i]) == 0)
// 			n--;
// 		else
// 			return ((s1c[i] - s2c[i]));
// 		i++;
// 	}
// 	return (0);
// }

void	check_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return ;
		i++;
	}
}

//  This function extracts and splits the PATH directories from the environment
//  variables. It searches for the PATH variable, removes the "PATH=" prefix,
//  and splits the remaining string using the ':' delimiter.

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
	if (envp[gpp.i] == NULL)
		return (0);
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
	// printf("temp: [%s] \n", gpp.temp);
	gpp.possible_paths = ft_split(gpp.temp, ':');
	free(gpp.temp);
	return (gpp.possible_paths);
}

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	*dst;

// 	i = 0;
// 	j = 0;
// 	dst = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (dst == NULL)
// 		return (NULL);
// 	while (s1[i] != '\0')
// 	{
// 		dst[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j] != '\0')
// 	{
// 		dst[i] = s2[j];
// 		j++;
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

//* This function constructs and checks possible paths for a command within the
//* directories specified by the PATH environment variable. It returns the full
//* path of the command if found, or NULL if not found.

char	*get_path(char *cmd, char **envp)
{
	char	**possible_paths;
	char	*path;
	char	*temp;
	int		i;

	if (cmd == NULL)
		return (NULL);
	check_envp(envp);
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
			return (free_matrix(possible_paths), path);
		free(path);
	}
	free_matrix(possible_paths);
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
	free(to_free);
}
