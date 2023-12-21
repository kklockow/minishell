/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:38:55 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 17:13:06 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_free(t_parser **parser)
{
	(*parser)->shell = NULL;
	(*parser)->command = NULL;
	save_free((void **) parser);
}
