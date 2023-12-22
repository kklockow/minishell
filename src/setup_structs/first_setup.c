/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:27:19 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 17:01:21 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_setup(t_coordinate *coordinate, char **envp)
{
	if (coordinate->first_set_up == false)
		return ;
	coordinate->shell = ft_calloc(1, sizeof(t_shell));
	if (coordinate->shell == NULL)
	{
		coordinate->run_loop = false;
		return ;
	}
	coordinate->shell->envp = init_env(envp);
	if (coordinate->shell->envp == NULL)
	{
		coordinate->run_loop = false;
		return ;
	}
}
