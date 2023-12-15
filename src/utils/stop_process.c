/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:14:19 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 11:23:06 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	stop_process(t_process *process)
{
	process->time_to_lex = false;
	process->time_to_exec = false;
	process->time_to_pars = false;
}
