/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_structs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:36:44 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/05 12:42:24 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_shell	**get_shell_struct()
{
	static t_shell	*shell;

	return (&shell);
}

t_cmd	**get_command_struct()
{
	static t_cmd	*command;

	return (&command);
}
