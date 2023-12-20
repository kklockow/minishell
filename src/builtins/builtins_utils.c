/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:20 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/19 20:19:41 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(t_cmd *current_cmd)
{
	if (current_cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(current_cmd->cmd, "echo ", 5) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "export", 6) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "unset ", 6) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "env", 3) == 0)
		return (1);
	if (ft_strncmp(current_cmd->cmd, "exit", 4) == 0
		&& (current_cmd->cmd[4] == ' '
			|| current_cmd->cmd[4] == '\0'))
		return (1);
	return (0);
}

int	handle_builtin(t_cmd *current_cmd, t_shell *shell)
{
	if (ft_strncmp(current_cmd->cmd, "echo", 4) == 0)
		echo_builtin(current_cmd->cmd);
	if (ft_strncmp(current_cmd->cmd, "cd", 2) == 0)
		cd_builtin(current_cmd->cmd, shell);
	if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0)
		pwd_builtin(current_cmd->cmd);
	if (ft_strncmp(current_cmd->cmd, "export", 6) == 0)
		export_builtin(current_cmd->cmd + 7, shell);
	if (ft_strncmp(current_cmd->cmd, "unset", 5) == 0)
		unset_builtin(current_cmd->cmd + 6, shell);
	if (ft_strncmp(current_cmd->cmd, "env", 3) == 0)
		env_builtin(shell->envp);
	if (ft_strncmp(current_cmd->cmd, "exit", 4) == 0)
		exit_builtin(current_cmd->cmd, shell);
	return (0);
}

// * This function removes a specified environment variable from the shell's
// * environment. It creates a new environment array without the variable to be
// * removed and frees the memory of the old environment array.

char	**env_remove_one(char **envp, char *str, int len)
{
	char	**shell_env;
	int		i;

	shell_env = malloc(sizeof (char *) * (ft_env_len(envp)));
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], str, len) != 0)
	{
		shell_env[i] = ft_strdup_init(envp[i]);
		i++;
	}
	i++;
	while (envp[i] && ft_strncmp(envp[i], str, len) != 0)
	{
		shell_env[i - 1] = ft_strdup_init(envp[i]);
		i++;
	}
	shell_env[i - 1] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (shell_env);
}

//This function adds a new environment variable to the shell's environment. It
//creates a new environment array with the new variable and frees the memory
//of the old environment array.

char	**env_add_new(char **envp, char *str)
{
	char	**shell_env;
	int		i;

	shell_env = malloc(sizeof (char *) * (ft_env_len(envp) + 2));
	i = 0;
	while (envp[i])
	{
		shell_env[i] = ft_strdup_init(envp[i]);
		i++;
	}
	shell_env[i] = ft_strdup_init(str);
	shell_env[i + 1] = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (shell_env);
}

//  * This function counts the number of characters in a string until the first
//  * '=' character is encountered. It is useful for determining the length of
//  * environment variable names.

int	count_till_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}
