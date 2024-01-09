/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:00:16 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 15:59:11 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_numeric(char *str, int i, t_cmd *cmd, t_shell *shell)
{
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != '\1')
	{
		if (!(str[i] > 47 && str[i] < 58))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str + 5, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			clean_exit(255, shell, cmd);
		}
		i++;
	}
	return (i);
}

void	exit_builtin(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	*str;

	str = cmd->cmd;
	i = 4;
	if (str[i] == '\0')
		clean_exit(0, shell, cmd);
	i++;
	i = check_numeric(str, i, cmd, shell);
	while (str[i] && str[i] == '\1')
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_code = 1;
		return ;
	}
	clean_exit(ft_atoi(str + 5), shell, cmd);
}

void	clean_exit(int exit_code, t_shell *shell, t_cmd *cmd)
{
	shell_struct_free(&shell);
	free_command_struct(&cmd);
	rl_clear_history();
	unlink("heredoc");
	exit (exit_code);
}
