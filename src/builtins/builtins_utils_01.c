/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:47:07 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 18:09:12 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_till_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}

int	get_len_export(char *str)
{
	int	i;
	int	len;
	int	guard;

	i = 0;
	len = 0;
	while (str[i])
	{
		guard = 0;
		while (str[i] == ' ')
		{
			if (guard == 0)
				len++;
			i++;
			guard = 1;
		}
		i++;
		len++;
	}
	return (len);
}
