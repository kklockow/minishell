/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:51:26 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/10 18:49:04 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_quit(void)
{
	struct sigaction	command_d;

	sigemptyset(&command_d.sa_mask);
	command_d.sa_handler = SIG_IGN;
	command_d.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &command_d, NULL);
}
