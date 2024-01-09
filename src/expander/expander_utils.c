/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:12:05 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/08 21:47:36 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_variable(char *str)
{
	int		len;
	char	*new;
	int		i;
	int		o;
	int		guard;

	// printf("[%s]\n", str);
	len = get_len_export(str);
	new = malloc(sizeof (char) * (len + 1));
	i = 0;
	// while (str[i] == ' ')
	// 	i++;
	o = 0;
	while (str[i])
	{
		guard = 0;
		while (str[i] == ' ')
		{
			if (guard == 0)
			{
				guard = 1;
				new[o] = str[i];
				o++;
			}
			i++;
		}
		new[o] = str[i];
		o++;
		if (str[i])
			i++;
	}
	new[o] = '\0';
	// printf("[%s]\n", new);
	return (new);
}