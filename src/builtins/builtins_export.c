/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:27:11 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/02 15:30:37 by kklockow         ###   ########.fr       */
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

int	export_builtin(char *str, t_shell *shell)
{
	int		i;
	int		num;
	int		len;
	char	**var;

	// printf("[%s]\n", str);
	if (str[0] == '\0')
	{
		print_declare_env(shell);
		return (0);
	}
	var = ft_split(str, ' ');
	num = 0;
	while (var[num] != NULL)
	{
		// printf("var[%i] = [%s]\n", num, var[num]);
		len = count_till_equal(var[num]);
		if (len != -1)
			export(var[num], shell, len);
		num++;
	}
	return (0);
}

