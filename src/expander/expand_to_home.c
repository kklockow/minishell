/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_to_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:40:03 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/10 09:18:54 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_update	update_till_dollar(t_update u, t_data *s, int start);

int	get_home_location(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != '~')
			i++;
		if (str[i] == '\0')
			return (-1);
		if (i == 0 && str[i] == '~'
			&& (str[i + 1] == ' ' || str[i + 1] == '\0'))
			return (i);
	}
	return (-1);
}

void	update_cmd_tilde(t_data *s, char *var, int start, char *name)
{
	t_update	u;
	char		*split_var;

	split_var = split_variable(var);
	u.for_malloc = ft_strlen(split_var) + ft_strlen(s->str) - ft_strlen(name);
	u.new = malloc(sizeof (char) * u.for_malloc + 1);
	u = update_till_dollar(u, s, start);
	u.i_var = 0;
	while (split_var[u.i_var] != '\0')
	{
		u.new[u.i_new] = split_var[u.i_var];
		u.i_new++;
		u.i_var++;
	}
	u.i_old++;
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

int	expand_to_home(t_shell *shell, t_data *s)
{
	int		sign_location;
	char	*var;
	char	*var_content;

	sign_location = get_home_location(s->str);
	if (sign_location == -1)
		return (0);
	var = "HOME";
	var_content = search_for_var(var, shell->envp, shell);
	update_cmd_tilde(s, var_content, sign_location, "~");
	free(var_content);
	return (0);
}
