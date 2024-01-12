/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sigint_in_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <fgabler@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:05:44 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/12 16:40:45 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

static	void	sigint_handler(int signum, siginfo_t *info, void *context);

void	handle_sigint_in_child(void)
{
	struct sigaction	sigint;

	sigemptyset(&sigint.sa_mask);
	sigint.sa_sigaction = sigint_handler;
	sigint.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sigint, NULL);
}

static	void	sigint_handler(int signum, siginfo_t *info, void *context)
{
	t_cmd	**command;
	t_shell	**shell;

	(void) info;
	(void) context;
	if (signum == SIGINT)
	{
		command = get_command_struct();
		shell = get_shell_struct();
		unlink(".heredoc");
		clean_exit(1, *shell, *command);
	}
}
