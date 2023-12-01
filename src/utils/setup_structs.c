/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_structs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 09:47:13 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/01 11:18:09 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_structs(t_cmd **data, t_lexer **lexer)
{
	*data = ft_calloc(1, sizeof(t_cmd));
	if (data == NULL)
		return (false); //free
	*lexer = ft_calloc(1, sizeof(t_lexer));
	if (data == NULL)
		return (false); //free
	return (true);
}
