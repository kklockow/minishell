/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:47:07 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/12 14:37:11 by kklockow         ###   ########.fr       */
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
		if (guard == 0)
		{
			i++;
			len++;
		}
	}
	return (len);
}

int	check_for_newline(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n\1", 3) == 0)
		return (1);
	if (ft_strncmp(str, "-n\0", 3) == 0)
		return (1);
	i = 2;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		while (str[i])
		{
			if (str[i] != 'n' && str[i] != '\0')
				return (0);
			i++;
		}
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
