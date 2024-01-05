/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_01.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:47:07 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/05 15:29:24 by kklockow         ###   ########.fr       */
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

char	*split_export(char *str)
{
	int		len;
	char	*new;
	int		i;
	int		guard;
	int		o;

	// str = "X=' A  B  '";
	len = get_len_export(str);
	// printf("%i\n", len);
	new = malloc(sizeof (char) * (len + 1));
	i = 0;
	o = 0;
	while (str[i])
	{
		guard = 0;
		while (str[i] == ' ')
		{
			if (guard == 0)
			{
				new[o] = str[i];
				o++;
			}
			i++;
			guard = 1;
		}
		new[o] = str[i];
		o++;
		i++;
	}
	new[o] = 0;
	// printf("[%s]\n", new);
	return (new);
}
