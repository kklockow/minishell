/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_to_home.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:40:03 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 18:37:59 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (str[i] == '~' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
			return (i);
	}
	return (-1);
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
	update_cmd(s, var_content, sign_location, var);
	free(var_content);
	return (0);
}
