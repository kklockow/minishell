/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:50:34 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/20 16:31:48 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_len(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

//This function duplicates a string and initializes the duplicate. It allocates
//memory for the duplicate string, copies the content of the original string,
//and sets the null terminator at the end.

char	*ft_strdup_init(const char *s1)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = malloc(ft_strlen((char *)s1) + 1);
	if (dst == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		dst[i] = s1[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

//  * This function initializes a new shell environment from an existing
//  * environment. It creates a new environment array and duplicates the content
//  * of the existing environment.

char	**init_env(char **envp)
{
	char	**shell_env;
	int		i;

	shell_env = malloc(sizeof (char *) * (ft_env_len(envp) + 1));
	if (shell_env == NULL)
		return NULL;
	i = 0;
	while (envp[i])
	{
		shell_env[i] = ft_strdup_init(envp[i]);
		i++;
	}
	shell_env[i] = NULL;
	return (shell_env);
}
