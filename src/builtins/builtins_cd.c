/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 11:09:51 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 12:45:13 by kklockow         ###   ########.fr       */
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

int	cd_to_home(t_shell *shell)
{
	int	i;

	update_oldpwd(shell);
	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "HOME=", 5) == 0)
			break ;
		i++;
	}
	if (shell->envp[i] == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->exit_code = 1;
		return (1);
	}
	if (chdir(shell->envp[i] + 5) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(shell->envp[i] + 5, 2);
		perror("\1");
		shell->exit_code = 1;
	}
	update_pwd(shell);
	return (0);
}

int	cd_back_one(t_shell *shell)
{
	int		i;
	char	*temp;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "OLDPWD=", 7) == 0)
			break ;
		i++;
	}
	if (shell->envp[i] == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		shell->exit_code = 1;
		return (1);
	}
	temp = shell->envp[i] + 7;
	update_oldpwd(shell);
	if (chdir(temp) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(temp + 7, 2);
		perror("\1");
		shell->exit_code = 1;
	}
	printf("%s\n", temp);
	update_pwd(shell);
	return (0);
}

int	cd_builtin(char *str, t_shell *shell)
{
	if (str[2] == '\0')
		return (cd_to_home(shell));
	if (str[3] == '-' && (str[4] == '\1' || str[4] == '\0'))
		return (cd_back_one(shell));
	update_oldpwd(shell);
	if (chdir(str + 3) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str + 3, 2);
		perror("\1");
		shell->exit_code = 1;
	}
	update_pwd(shell);
	return (0);
}
