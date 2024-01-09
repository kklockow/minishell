/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:12:05 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 19:56:58 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_variable(char *str, char *new, int i, int o)
{
	int		guard;

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
	return (new);
}

char	*split_variable(char *str)
{
	int		len;
	char	*new;

	len = get_len_export(str);
	new = malloc(sizeof (char) * (len + 1));
	new = fill_variable(str, new, 0, 0);
	return (new);
}

void	handle_non_sign(t_data *s)
{
	if (s->str && s->str[0] == '$' && s->next
		&& (s->next->type == DOUBLE_QUOTE || s->next->type == SINGLE_QUOTE))
	{
		free(s->str);
		s->str = malloc(sizeof (char) * 1);
		s->str[0] = '\0';
	}
}

void	free_and_do_again(char *var, char *vc, t_shell *shell, t_data *s)
{
	free(var);
	free(vc);
	expander(shell, s);
}
