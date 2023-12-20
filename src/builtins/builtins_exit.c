/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:00:16 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/20 19:04:49 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		check_numeric(char *str, int i)
{
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != ' ')
	{
		if (!(str[i] > 47 && str[i] < 58))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str + 5, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit (255);
		}
		i++;
	}
	return(i);
}

void	exit_builtin(char *str, t_shell *shell)
{
	int	i;

	i = 4;
	if (str[i] == '\0')
		exit (0);
	i++;
	i = check_numeric(str, i);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] != '\0')
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->exit_code = 1;
		return ;
	}
	// printf("%i\n", ft_atoi(str + 5));
	exit(ft_atoi(str + 5));
}
