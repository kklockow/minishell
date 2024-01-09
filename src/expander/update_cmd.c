/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:02:14 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/08 17:14:26 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ADD FREE C_TABLE->CMD WHEN MERGED!! IT IS ALLOCATED MEMORY FOR GODS SAKE!
// "'$USER'"

t_update	update_till_dollar(t_update u, t_data *s, int start)
{
	u.i_new = 0;
	u.i_old = 0;
	while (u.i_old < start)
	{
		u.new[u.i_new] = s->str[u.i_old];
		u.i_new++;
		u.i_old++;
	}
	return (u);
}

void	update_cmd(t_data *s, char *var, int start, char *name)
{
	t_update	u;
	char		*split_var;

	split_var = split_variable(var);
	u.for_malloc = ft_strlen(split_var) + ft_strlen(s->str) - ft_strlen(name);
	u.new = malloc(sizeof (char) * u.for_malloc);
	u = update_till_dollar(u, s, start);
	u.i_var = 0;
	while (split_var[u.i_var] != '\0')
	{
		u.new[u.i_new] = split_var[u.i_var];
		u.i_new++;
		u.i_var++;
	}
	u.i_old += ft_strlen(name) + 1;
	while (s->str[u.i_old] != '\0')
	{
		u.new[u.i_new] = s->str[u.i_old];
		u.i_new++;
		u.i_old++;
	}
	free(s->str);
	free(split_var);
	u.new[u.i_new] = '\0';
	s->str = u.new;
}
