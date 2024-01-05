/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:51 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/05 16:38:03 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//  * This function implements the echo built-in command. It processes the input
//  * string to determine whether the '-n' option is present. If the '-n' option
//  * is found, a newline character is not printed at the end. The processed
//  * string is then printed to the standard output.

int	echo_builtin(char *str)
{
	int		i;
	int		new_line;
	char	**split;

	new_line = 1;
	// printf("[%s]\n", str);
	// i = 0;
	// if (str[i] == '\1')
	// 	i++;
	// if (str[i] && str[i + 1] && str[i] == '-' && str[i + 1] == 'n'
	// 	&& str[i + 2] && str[i + 2] == '\1')
	// {
	// 	new_line = 0;
	// 	i += 3;
	// }
	// while (str[i])
	// {
	// 	if (str[i] != '\1')
	// 		write (1, &str[i], 1);
	// 	i++;
	// }
	// printf("[%s]\n", str);
	split = ft_split(str, '\1');
	i = 0;
	while (split[i] && (ft_strncmp(split[i], "-n\1", 3) == 0
			|| ft_strncmp(split[i], "-n\0", 3) == 0))
	{
		new_line = 0;
		i++;
	}
	while (split[i])
	{
		// printf("%i\n[%s]\n", i, split[i]);
		printf("%s", split[i]);
		if (split[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
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

int	check_for_invalid_unset(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((ft_isalpha(str[0]) == 0 && str[0] != '_')
			|| (ft_isalnum(str[i]) == 0 && str[i] != '_'))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset_builtin(char *str, t_shell *shell, int i)
{
	int		num;
	int		len;
	char	**var;
	char	*joined;

	var = ft_split(str, '\1');
	num = 0;
	while (var[num] != NULL)
	{
		shell->exit_code = check_for_invalid_unset(var[num], shell);
		joined = ft_strjoin(var[num], "=");
		while (joined[i])
			i++;
		len = i;
		i = 0;
		while (shell->envp[i] && ft_strncmp(shell->envp[i], joined, len) != 0)
			i++;
		if (shell->envp[i] != NULL)
			shell->envp = env_remove_one(shell->envp, joined, len);
		free(joined);
		num++;
	}
	free_matrix(var);
	return (shell->exit_code);
}
