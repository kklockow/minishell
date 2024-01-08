/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:12:05 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/08 17:12:21 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*split_variable(char *str)
{
	int		len;
	char	*new;
	int		i;
	int		o;

	len = get_len_export(str);
	new = malloc(sizeof (char) * (len + 1));
	i = 0;
	while (str[i] == ' ')
		i++;
	o = 0;
	while (str[i])
	{
		while (str[i] == ' ')
		{
			if (str[i + 1] && str[i + 1] != ' ')
			{
				new[o] = str[i];
				o++;
			}
			i++;
		}
		new[o] = str[i];
		o++;
		i++;
	}
	new[o] = '\0';
	// printf("[%s]\n", new);
	return (new);
}