/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:49:59 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 19:29:42 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_whitespace(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != ' ')
		i++;
	if (i == 0)
		return (1);
	while (str[i] == ' ')
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

void	handle_pipe(t_cmd *c_table, int *pipefd)
{
	if (c_table->write_pipe == 1)
	{
		if (c_table->next->read_pipe == 1)
			dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	execute_command(t_cmd *current_cmd, t_shell *shell, t_cmd *head)
{
	char	*path;
	char	**split;

	if (current_cmd->cmd == NULL || current_cmd->cmd[0] == '\0')
		clean_exit (1, shell, head);
	if (current_cmd->heredoc_as_argument == 1)
		current_cmd->cmd = ft_strjoin(current_cmd->cmd, "\1.heredoc");
	check_for_path(current_cmd, shell);
	split = ft_split(current_cmd->cmd, '\1');
	if (access(split[0], F_OK | X_OK) != 0)
		path = get_path(split[0], shell->envp);
	else
		path = ft_strdup(split[0]);
	execve(path, split, shell->envp);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(split[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free_matrix(split);
	free(path);
	clean_exit (127, shell, head);
}

void	check_for_path(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (cmd->cmd[i] == ' ')
		i++;
	if (cmd->cmd[i] == '.' && cmd->cmd[i + 1] == '/')
	{
		if (access(cmd->cmd, F_OK | X_OK) != 0)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->cmd, 2);
			perror("\1");
			clean_exit(127, shell, cmd);
		}
	}
}

void	cleaning_up(pid_t pid, int stdin, int stdout, t_shell *shell)
{
	int	status;

	waitpid(pid, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
}
