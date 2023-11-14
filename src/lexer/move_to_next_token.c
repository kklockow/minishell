/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_next_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:06:39 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/13 15:18:01 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes_and_no_space(int	position, char *input);

void	move_to_next_token(int	*position, char *input)
{
	int			hit_space;
	int			i;

	hit_space = 0;
	i = *position;
	while(input[i] != '\0')
	{
		if (input[i] == ' ') // || input[i] == '"' && input[i] == '\'') && guard == 0)
			hit_space = 1;
		if (input[i] != ' ' && hit_space == 1)
		{
			*position = i;
			return ;
		}
		if (quotes_and_no_space(i, input) && i > *position)
		{
			*position = i;
			return ;
		}
		i++;
	}
}

static int	quotes_and_no_space(int	position, char *input)
{
	if (position > 0)
	{
		if (input[position] == '\'' && input[position - 1] == '\'')
			return (1);
		if (input[position] == '"' && input[position - 1] == '"')
			return (1);
	}
	return (0);
}
