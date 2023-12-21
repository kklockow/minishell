/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:32:35 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/21 16:58:12 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_free(void **pointer)
{
	if (*pointer == NULL)
		return ;
	free(*pointer);
	*pointer = NULL;
}
