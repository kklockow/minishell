/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:54:21 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/08 20:32:39 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand(t_parser *s)
{
	t_data	*current;
	int		guard;

	guard = 0;
	current = s->lexer->head;
	// printf("start\n");
	while (current != NULL)
	{
		// printf("before: [%s]\n", current->str);
		if (guard == 0)
			guard = expander(s->shell, current);
		// printf("result: [%s]\n", current->str);
		current = current->next;
	}
}

int	expander(t_shell *shell, t_data *s)
{
	int		sign_location;
	char	*var;
	char	*var_content;

	if (s->type == SINGLE_QUOTE)
		return (0);
	if (s->type == DOUBLE_LESS)
		return (1);
	if (s->type != DOUBLE_QUOTE)
		expand_to_home(shell, s);
	// printf("[%s]\n", s->str);
	sign_location = get_sign_location(s->str);
	if (sign_location == -1)
	{
		if (s->str && s->str[0] == '$' && s->next && (s->next->type == DOUBLE_QUOTE || s->next->type == SINGLE_QUOTE))
		{
			// printf("went into new\n");
			free(s->str);
			s->str = malloc(sizeof (char) * 1);
			s->str[0] = '\0';
		}
		return (0);
	}
	var = get_variable_to_expand(s->str, sign_location);
	var_content = search_for_var(var, shell->envp, shell);
	update_cmd(s, var_content, sign_location, var);
	free(var);
	free(var_content);
	expander(shell, s);
	return (0);
}

int	get_sign_location(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
	{
		i++;
		if (str[i] == '$')
		{
			if (str[i + 1] == '\0')
				i++;
			else if (str[i + 1] == ' ')
				i++;
		}
	}
	if (str[i] == '\0')
		return (-1);
	if (str[i] == '$' && (str[i + 1] == ' ' || str[i + 1] == '\0'))
		return (-1);
	return (i);
}

// if (str[i] == '\0')
	// 	return (-1);
	// if (str[i + 1] == ' ')
	// 	get_sign_location(str, i + 1);
	// if (str[i + 1] == '\0')
	// 	return (-1);
	// printf("%s\n", str);
	// while (str[i] && str[i] != '$')
	// 	i++;
	// if (str[i] == '\0')
	// {
	// 	printf("went in\n");
	// 	return (-1);
	// }
	// if (str[i + 1] == ' ')
	// 	i = get_sign_location(str, i + 1);
	// if (i == -1)
	// 	return (-1);

char	*get_variable_to_expand(char *str, int sign_location)
{
	int		i;
	int		len;
	char	*var_str;
	int		var_i;

	// printf("[%s]\n", str);
	i = sign_location + 1;
	len = 0;
	while (str[i] && str[i] != ' ')
	{
		len++;
		i++;
	}
	var_str = malloc(sizeof (char) * (len + 1));
	i = sign_location + 1;
	var_i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '/' && str[i] != 39 && str[i] != '$')
	{
		var_str[var_i] = str[i];
		i++;
		var_i++;
		// printf("[%s]\n", var_str);
	}
	var_str[var_i] = '\0';
	return (var_str);
}

char	*search_for_var(char *var, char **envp, t_shell *shell)
{
	int		i;
	char	*var_content;
	char	*var_equal;

	if (ft_strncmp(var, "?", 1) == 0)
	{
		var_content = ft_itoa(shell->exit_code);
		return (var_content);
	}
	if (ft_strncmp(var, " ", 1) == 0)
		return (NULL);
	var_equal = ft_strjoin(var, "=");
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_equal, envp[i], ft_strlen(var_equal)) == 0)
		{
			var_content = ft_strdup(envp[i] + ft_strlen(var_equal));
			return (var_content);
		}
		i++;
	}
	var_content = malloc(sizeof (char) * 1);
	var_content[0] = '\0';
	return (var_content);
}
