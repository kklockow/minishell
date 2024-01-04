/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:27:11 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/04 18:36:03 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//* This function implements the export built-in command. It takes a string
//* containing environment variable assignments, splits them into individual
//* variables, and updates the shell's environment accordingly. If an existing
//* variable is found, its value is updated; otherwise, a new variable is added
//* to the environment.

void	print_declare_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i] != NULL)
	{
		printf("declare -x %s\n", shell->envp[i]);
		i++;
	}
}

void	export(char *var, t_shell *shell, int len)
{
	int	i;

	i = 0;
	while (shell->envp[i] != 0
		&& ft_strncmp(shell->envp[i], var, len) != 0)
		i++;
	if (shell->envp[i] != NULL)
	{
		free(shell->envp[i]);
		shell->envp[i] = ft_strdup_init(var);
	}
	else
		shell->envp = env_add_new(shell->envp, var);
}

int	check_for_invalid_export(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_isalpha(str[0]) == 0 && str[0] != '_')
			|| (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '='))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export_builtin(char *str, t_shell *shell)
{
	int		i;
	int		num;
	int		len;
	char	**var;

	if (str[0] == '\0')
	{
		print_declare_env(shell);
		return (0);
	}
	var = ft_split(str, '\1');
	num = 0;
	while (var[num] != NULL)
	{
		shell->exit_code = check_for_invalid_export(var[num], shell);
		len = count_till_equal(var[num]);
		if (len != -1)
			export(var[num], shell, len);
		num++;
	}
	free_matrix(var);
	return (0);
}
