/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_null_stop_process.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:21:13 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/18 16:22:55 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	if_null_stop_process(char *string, t_parser *parser)
{
	if (string == NULL)
		stop_process(parser->shell->process);
}
