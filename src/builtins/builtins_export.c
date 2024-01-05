/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:27:11 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/05 16:56:15 by kklockow         ###   ########.fr       */
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
		shell->envp[i] = split_export(var);
	}
	else
		shell->envp = env_add_new(shell->envp, var);
}

int	check_valid_char(char c, int i)
{
	if (i == 0)
	{
		if (ft_isalpha(c) == 1)
			return (1);
		if (c == '_')
			return (1);
		if (c == ' ')
			return (1);
		if (c == '/')
			return (1);
	}
	else
	{
		if (ft_isalnum(c) == 1)
			return (1);
		if (c == '_')
			return (1);
		if (c == '=')
			return (1);
		if (c == ' ')
			return (1);
		if (c == '/')
			return (1);
		// if ft_isprint()
	}
	return (0);
}

int	check_for_invalid_export(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	// printf("[%s]\n", str);
	while (str[i])
	{
		// if ((ft_isalpha(str[0]) == 0 && str[0] != '_' && str[0] != ' ')
		// 	|| (ft_isalnum(str[i]) == 0 && str[i] != '_' && str[i] != '='))
		if (check_valid_char(str[i], i) == 0)
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
