/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:51 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/02 18:41:01 by kklockow         ###   ########.fr       */
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
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n'
		&& str[i + 2] && str[i + 2] == ' ')
	{
		new_line = 0;
		i += 3;
	}
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n')
		new_line = 0;
	if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n')
		i += 2;
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

void	check_for_invalid(char *str, t_shell *shell)
{
	if (ft_isalpha(str[0]) == 0)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid indentifier\n", 2);
		shell->exit_code = 1;
	}
}

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
		check_for_invalid(var[num], shell);
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
