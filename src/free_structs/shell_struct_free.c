/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_struct_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:16:35 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 14:30:44 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envp(char **envp);

void	shell_struct_free(t_shell **shell)
{
	free_envp((*shell)->envp);
	free(*shell);
	*shell = NULL;
}

static void	free_envp(char **envp)
{
	free_dubble_array(envp);
	envp = NULL;
}
