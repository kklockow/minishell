/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:15:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/11 18:16:08 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quots_check(char *input, t_data *data, int *i)
{
	int	signle_quote;
	int	dobble_quote;
	
	if (input[*i] == 22)
		mark_till_next_quote();
	else if (input[*i] == 27)
		mark_till_next_quote();
	return (0);
}
