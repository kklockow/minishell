/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:09:51 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/08 11:22:55 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


//  * This function updates the OLDPWD environment variable with the previous
//  * working directory. It searches for the existing OLDPWD variable, gets the
//  * current working directory, creates a new OLDPWD string, and replaces the
//  * old OLDPWD variable.

int	update_oldpwd(t_shell *shell)
{
	int		i;
	char	cwd[1028];
	char	*str;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	if (shell->envp[i] == NULL)
		return (-1);
	getcwd(cwd, sizeof(cwd));
	str = ft_strjoin("OLDPWD=", cwd);
	free(shell->envp[i]);
	shell->envp[i] = str;
	return (0);
}

//This function updates the PWD environment variable with the current working
//directory. It searches for the existing PWD variable, gets the current working
//directory, creates a new PWD string, and replaces the old PWD variable.

int	update_pwd(t_shell *shell)
{
	int		i;
	char	cwd[1028];
	char	*str;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "PWD=", 4) == 0)
			break ;
		i++;
	}
	if (shell->envp[i] == NULL)
		return (-1);
	getcwd(cwd, sizeof(cwd));
	str = ft_strjoin("PWD=", cwd);
	free(shell->envp[i]);
	shell->envp[i] = str;
	return (0);
}

int	cd_builtin(char *str, t_shell *shell)
{
	update_oldpwd(shell);
	chdir(str + 3);
	update_pwd(shell);
	return (0);
}
