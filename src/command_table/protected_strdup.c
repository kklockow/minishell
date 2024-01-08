/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 22:38:42 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/07 22:42:06 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*protected_strdup(char *string, t_parser *parser)
{
	char	*str_tmp;

	str_tmp = ft_strdup(string);
	if_null_stop_process(str_tmp, parser);
	return (str_tmp);
}
