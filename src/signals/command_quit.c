/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_quit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:51:26 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/18 13:21:13 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_quit()
{
	struct sigaction	command_d;

	command_d.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &command_d, NULL);
}
