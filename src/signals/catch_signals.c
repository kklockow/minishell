/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 16:54:28 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/19 15:58:29 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	catch_signals(t_coordinate *coordinate)
{
	(void) coordinate;
	//hide_ctrl_chars(coordinate);
	command_c();
	command_quit();
}
