/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:47:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/22 13:04:08 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_till_equal(char *str, int i)
{
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

int	count_till_space_backwards(char *str, int i)
{
	while (str[i] && str[i] != ' ')
		i--;
	printf("%i\n", i);
	return (i);
}

int	count_len(char *str, int i)
{
	int	guard;
	int	len;

	guard = 0;
	while (str[i])
	{
		if (str[i] == '=' && guard == 0)
		{
			guard = 1;
			while (str[i] == '=')
			{
				i++;
				len++;
			}
		}
		if (str[i] == '=' && guard == 1)
		{
			len -= count_till_space_backwards(str, i);
			break ;
		}
		i++;
		len++;
	}
	return (len);
}
