/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal_heredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:05:44 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 16:27:34 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	heredoc_handler(int signum, siginfo_t *info, void *context);

void	handle_signal_heredoc()
{
	struct sigaction	heredoc_signal;

	heredoc_signal.sa_sigaction = heredoc_handler;
	sigaction(SIGINT, &heredoc_signal, NULL);
}

static	void	heredoc_handler(int signum, siginfo_t *info, void *context)
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
