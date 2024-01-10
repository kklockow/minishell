/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 12:56:37 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/09 17:12:43 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirect(t_data *data)
{
	if (data->type == DOUBLE_LESS || data->type == DOUBLE_GREAT
		|| data->type == LESS || data->type == GREATER)
		return (true);
	return (false);
}
