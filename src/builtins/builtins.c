/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:51 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/20 21:13:36 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  * This function implements the echo built-in command. It processes the input
//  * string to determine whether the '-n' option is present. If the '-n' option
//  * is found, a newline character is not printed at the end. The processed
//  * string is then printed to the standard output.

int	echo_builtin(char *str)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n'
		&& str[i + 2] && str[i + 2] == ' ')
	{
		new_line = 0;
		i += 3;
	}
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
	return (0);
}

//  * This function implements the pwd built-in command. It checks if the input
//  * string is valid for the pwd command. If the input is invalid, it prints
//  * an error message. Otherwise, it retrieves the current working directory
//  * and prints it to the standard output.

int	pwd_builtin(void)
{
	char	cwd[1028];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (0);
}

//* This function implements the export built-in command. It takes a string
//* containing environment variable assignments, splits them into individual
//* variables, and updates the shell's environment accordingly. If an existing
//* variable is found, its value is updated; otherwise, a new variable is added
//* to the environment.

int	export_builtin(char *str, t_shell *shell)
{
	int		i;
	int		num;
	int		len;
	char	**var;

	var = ft_split(str, ' ');
	num = 0;
	while (var[num] != NULL)
	{
		len = count_till_equal(var[num]);
		i = 0;
		while (shell->envp[i] != 0
			&& ft_strncmp(shell->envp[i], var[num], len) != 0)
			i++;
		if (shell->envp[i] != NULL)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_strdup_init(var[num]);
		}
		else
			shell->envp = env_add_new(shell->envp, var[num]);
		num++;
	}
	return (0);
}

// This function implements the env built-in command. It takes the current
// environment variables and prints them to the standard output, one per line.

int	env_builtin(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

//This function implements the unset built-in command. It removes the specified
//environment variables from the shell's environment.
//If a variable is not found, it prints an error message.

int	unset_builtin(char *str, t_shell *shell)
{
	int		i;
	int		num;
	int		len;
	char	**var;

	var = ft_split(str, ' ');
	num = 0;
	while (var[num] != NULL)
	{
		i = 0;
		if (ft_isalpha(var[num][0]) == 0)
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(var[num], 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
			shell->exit_code = 1;
		}
		while (var[num][i] && var[num][i] != '=')
			i++;
		len = i;
		i = 0;
		while (shell->envp[i] != 0
			&& ft_strncmp(shell->envp[i], var[num], len) != 0)
			i++;
		if (shell->envp[i] != NULL)
			shell->envp = env_remove_one(shell->envp, var[num], len);
		num++;
	}
	return (0);
}
