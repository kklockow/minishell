/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 09:27:11 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/02 14:56:38 by kklockow         ###   ########.fr       */
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

int	number_of_sign(char *str)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			n++;
			while (str[i] == '=')
				i++;
		}
		if (str[i])
			i++;
	}
	return (n);
}

char	**all_exports(char *str)
{
	char	**all;
	int		num_sign;
	int		i;
	int		j;
	int		len;
	int		start;
	int		o;

	num_sign = number_of_sign(str);
	// printf("%i\n", number_of_sign(str));
	all = malloc(sizeof (char *) * (num_sign + 1));
	j = 0;
	len = 0;
	i = 0;
	while (j < num_sign)
	{
		i = count_till_equal(str, i);
		start = count_till_space_backwards(str, i);
		len = count_len(str, start);
		all[j] = malloc(sizeof (char) * len + 1);
		o = 0;
		while (o < len)
		{
			all[j][o] = str[start];
			start++;
			o++;
		}
		all[j][o] = '\0';
		printf("string %i is %s\n", j, all[j]);
		j++;
	}
	return (all);
}

void	add_or_new(t_shell *shell, int i, char *var)
{
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

	printf("DOES NOTHING CURRENTLY AAAAAAARG\n");
	return (0);
	if (str[0] == '\0')
	{
		print_declare_env(shell);
		return (0);
	}
	var = all_exports(str);
	num = 0;
	while (var[num] != NULL)
	{
		len = count_till_equal(var[num], 0);
		i = 0;
		while (shell->envp[i] != 0
			&& ft_strncmp(shell->envp[i], var[num], len) != 0)
			i++;
		add_or_new(shell, i, var[num]);
		num++;
	}
	return (0);
}

