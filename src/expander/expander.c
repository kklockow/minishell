/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:54:21 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/14 17:39:26 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		expander(t_shell *shell, t_data *s);
int		get_sign_location(char *str);
char	*get_variable_to_expand(char *str, int sign_location);
char	*search_for_var(char *var, char **envp);
void	update_cmd(t_data *s, char *var, int start, char *name);

// int	main(int ac, char **av, char **envp)
// {
// 	t_cmd	*c_table;
// 	t_cmd	*new;
// 	t_cmd	*new2;
// 	t_cmd	*new3;
// 	t_shell	*shell;
// 	char	*input;
// 	int		i;
// 	char	**shell_envp;

// 	ac = 0;
// 	av = NULL;
// 	c_table = malloc(sizeof (t_cmd));
// 	c_table->cmd = "sahne $USER sahne $USER";
// 	c_table->infile = NULL;
// 	c_table->outfile = NULL;
// 	c_table->read_pipe = 0;
// 	c_table->write_pipe = 0;
// 	c_table->heredoc = NULL;
// 	c_table->next = NULL;
// 	shell = malloc(sizeof (t_shell *));
// 	shell->envp = init_env(envp);
// 	printf("before: %s\n", c_table->cmd);
// 	expander(shell, c_table);
// 	printf("after: %s\n", c_table->cmd);
// 	return (0);
// }

void	expand(t_parser *s, t_shell *shell)
{
	t_data	*current;

	current = s->lexer->head;
	while (current != NULL)
	{
		expander(shell, current);
		current = current->next;
	}
}

int	expander(t_shell *shell, t_data *s)
{
	int		sign_location;
	char	*var;
	char	*var_content;

	sign_location = get_sign_location(s->str);
	if (sign_location == -1)
		return (0);
	var = get_variable_to_expand(s->str, sign_location);
	var_content = search_for_var(var, shell->envp);
	printf("%i\n%s\n%s\n", sign_location, var, var_content);
	update_cmd(s, var_content, sign_location, var);
	free(var);
	free(var_content);
	return (0);
}

int	get_sign_location(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!(str[i]))
		return (-1);
	return (i);
}

char	*get_variable_to_expand(char *str, int sign_location)
{
	int		i;
	int		len;
	char	*var_str;
	int		var_i;

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
	while (str[i] && str[i] != ' ')
	{
		var_str[var_i] = str[i];
		i++;
		var_i++;
	}
	var_str[var_i] = '\0';
	return (var_str);
}

char	*search_for_var(char *var, char **envp)
{
	int		i;
	char	*var_content;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0)
		{
			var_content = ft_strdup(envp[i] + 1 + ft_strlen(var));
			return (var_content);
		}
		i++;
	}
	var_content = malloc(sizeof (char) * 1);
	var_content[0] = '\0';
	return (var_content);
}

//ADD FREE C_TABLE->CMD WHEN MERGED!! IT IS ALLOCATED MEMORY FOR GODS SAKE!

void	update_cmd(t_data *s, char *var, int start, char *name)
{
	char	*new;
	int		i_old;
	int		i_new;
	int		i_var;

	new = malloc(sizeof (char) * (ft_strlen(var) + ft_strlen(s->str) - ft_strlen(name) - 1));
	i_new = 0;
	i_old = 0;
	while (i_old < start)
	{
		new[i_new] = s->str[i_old];
		i_new++;
		i_old++;
	}
	i_var = 0;
	while (var[i_var] != '\0')
	{
		new[i_new] = var[i_var];
		i_new++;
		i_var++;
	}
	i_old += ft_strlen(name) + 1;
	while (s->str[i_old] != '\0')
	{
		new[i_new] = s->str[i_old];
		i_new++;
		i_old++;
	}
	// free(c_table->cmd);
	new[i_new] = '\0';
	s->str = new;
}
