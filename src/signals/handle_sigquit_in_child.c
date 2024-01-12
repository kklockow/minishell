/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigquit_in_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:06:05 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/12 16:40:56 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	sigquit_handler(int signum);

void	handle_sigquit_in_child(void)
{
	struct sigaction	sigquit;

	sigemptyset(&sigquit.sa_mask);
	sigquit.sa_handler = sigquit_handler;
	sigquit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sigquit, NULL);
}

static	void	sigquit_handler(int signum)
{
	t_cmd	**command;
	t_shell	**shell;

	if (signum == SIGQUIT)
	{
		command = get_command_struct();
		shell = get_shell_struct();
		unlink(".heredoc");
		clean_exit(131, *shell, *command);
	}
}
