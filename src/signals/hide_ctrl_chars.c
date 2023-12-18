/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hide_ctrl_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:05:21 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/18 14:07:46 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hide_ctrl_chars(t_coordinate *coordinate)
{
	struct termios	term;

	if (tcgetattr(1, &term) == -1)
	{
		perror("minishell: tcgetattr");
		coordinate->shell->exit_code = 1;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(1, TCSANOW, &term) == -1)
	{
		perror("minishell: tcsetattr");
		coordinate->shell->exit_code = 1;
	}
}
