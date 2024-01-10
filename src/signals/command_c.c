/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 08:53:49 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/10 18:47:23 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	command_c_handler(int signum, siginfo_t *info, void *context);

void	command_c(void)
{
	struct sigaction	command_c;

	sigemptyset(&command_c.sa_mask);
	command_c.sa_sigaction = command_c_handler;
	command_c.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &command_c, NULL);
}

static void	command_c_handler(int signum, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}
