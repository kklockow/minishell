/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:59:20 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/08 20:58:52 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(t_cmd *current_cmd)
{
	if (current_cmd->cmd == NULL)
		return (0);
	if (ft_strncmp(current_cmd->cmd, "echo", 4) == 0
		&& (current_cmd->cmd[4] == '\1' || current_cmd->cmd[4] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "cd", 2) == 0
		&& (current_cmd->cmd[2] == '\1' || current_cmd->cmd[2] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0
		&& (current_cmd->cmd[3] == '\1' || current_cmd->cmd[3] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "export", 6) == 0
		&& (current_cmd->cmd[6] == '\1' || current_cmd->cmd[6] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "unset", 5) == 0
		&& (current_cmd->cmd[5] == '\1' || current_cmd->cmd[5] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "env", 3) == 0
		&& (current_cmd->cmd[3] == '\1' || current_cmd->cmd[3] == '\0'))
		return (1);
	if (ft_strncmp(current_cmd->cmd, "exit", 4) == 0
		&& (current_cmd->cmd[4] == '\1' || current_cmd->cmd[4] == '\0'))
		return (1);
	return (0);
}

int	handle_builtin(t_cmd *current_cmd, t_shell *shell)
{
	if (ft_strncmp(current_cmd->cmd, "echo", 4) == 0)
		shell->exit_code = echo_builtin(current_cmd->cmd + 4);
	if (ft_strncmp(current_cmd->cmd, "cd", 2) == 0)
		cd_builtin(current_cmd->cmd, shell);
	if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0)
		shell->exit_code = pwd_builtin();
	if (ft_strncmp(current_cmd->cmd, "export", 6) == 0)
		export_builtin(current_cmd->cmd + 6, shell);
	if (ft_strncmp(current_cmd->cmd, "unset", 5) == 0)
		unset_builtin(current_cmd->cmd + 6, shell, 0);
	if (ft_strncmp(current_cmd->cmd, "env", 3) == 0)
		env_builtin(shell->envp);
	if (ft_strncmp(current_cmd->cmd, "exit", 4) == 0)
		exit_builtin(current_cmd, shell);
	return (shell->exit_code);
}

int	handle_builtin_piped(t_cmd *current_cmd, t_shell *shell, t_cmd *head)
{
	int	exit_code;

	if (ft_strncmp(current_cmd->cmd, "echo", 4) == 0)
	{
		shell->exit_code = echo_builtin(current_cmd->cmd + 4);
		clean_exit(shell->exit_code, shell, head);
	}
	if (ft_strncmp(current_cmd->cmd, "pwd", 3) == 0)
	{
		shell->exit_code = pwd_builtin();
		clean_exit(shell->exit_code, shell, head);
	}
	if (ft_strncmp(current_cmd->cmd, "env", 3) == 0)
	{
		shell->exit_code = env_builtin(shell->envp);
		clean_exit(shell->exit_code, shell, head);
	}
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
	free_matrix(envp);
	return (shell_env);
}
