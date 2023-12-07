/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:50:34 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/07 14:01:49 by kklockow         ###   ########.fr       */
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

char	**init_env(char **envp)
{
	char	**shell_env;
	int		i;

	shell_env = malloc(sizeof (char *) * (ft_env_len(envp) + 1));
	i = 0;
	while (envp[i])
	{
		shell_env[i] = ft_strdup_init(envp[i]);
		i++;
	}
	shell_env[i] = NULL;
	return (shell_env);
}
