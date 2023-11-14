/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 12:23:17 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/11 18:15:13 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *input, t_data **data)
{
	t_data		*tmp_data;
	int			i;

	while (input[i] != '\0')
	{
		quots_check(input, *data, &i);

	}
	return (0);
}

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
