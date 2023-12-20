/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:32:35 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/19 19:32:57 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_free(void **pointer)
{
	if (*pointer == NULL)
		return ;
	free(*pointer);
	pointer = NULL;
}
