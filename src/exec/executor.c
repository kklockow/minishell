/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/22 11:17:28 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		executor_with_pipes(t_cmd *c_table, t_shell *shell);
void	handle_pipe(t_cmd *c_table, int *pipefd);
void	execute_command(t_cmd *current_cmd, t_shell *shell, t_cmd *head);
int		executor_main(t_cmd *command, t_shell *shell);
int		executor_no_pipes(t_cmd *c_table, t_shell *shell);
int		check_for_whitespace(char *str);

int	executor_main(t_cmd *command, t_shell *shell)
{
	if (shell->process->time_to_exec != true)
		return (-1);
	if (command->next == NULL)
		executor_no_pipes(command, shell);
	else
		executor_with_pipes(command, shell);
	return (0);
}

//  * This function checks if the given command is a built-in command. If it is,
//  * it redirects I/O and executes the built-in command. If it's not a built-in
//  * command, it forks a new process, redirects I/O, and executes the external
//  * command in the child process.

int	executor_no_pipes(t_cmd *c_table, t_shell *shell)
{
	pid_t	pid;
	int		stdin;
	int		status;

	// printf("[%s]\n", c_table->cmd);
	if (c_table->heredoc != NULL)
		signal(SIGINT, SIG_IGN);
	stdin = dup(STDIN_FILENO);
	if (check_builtin(c_table) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (redirect(c_table, NULL, shell) == -1)
				return (-1);
			execute_command(c_table, shell, c_table);
		}
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
	else
	{
		redirect(c_table, NULL, shell);
		handle_builtin(c_table, shell);
	}
	command_c();
	dup2(stdin, STDIN_FILENO);
	return (0);
}

//  * This function iterates through the command table, creating pipes as needed
//  * and forking processes for each command. It redirects I/O and executes
//  * commands in child processes. It also handles inter-process communication
//  * with pipes and waits for child processes to finish execution.

int	executor_with_pipes(t_cmd *c_table, t_shell *shell)
{
	int		pipefd[2];
	pid_t	pid;
	int		stdin;
	int		status;
	t_cmd	*head;

	head = c_table;
	stdin = dup(STDIN_FILENO);
	while (c_table != NULL)
	{
		if (c_table->heredoc != NULL)
			signal(SIGINT, SIG_IGN);
		if (c_table->write_pipe == 1)
		{
			if (pipe(pipefd) == -1)
				return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			redirect(c_table, pipefd, shell);
			if (handle_builtin_piped(c_table, shell, head) == 0)
				execute_command(c_table, shell, head);
		}
		handle_pipe(c_table, pipefd);
		if (c_table->heredoc != NULL)
			waitpid(pid, 0, 0);
		c_table = c_table->next;
		command_c();
	}
	waitpid(pid, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
	dup2(stdin, STDIN_FILENO);
	return (0);
}

//  * This function splits the given command into an array of strings,
//  * checks if the command is accessible, and retrieves its full path.
//  * It then attempts to execute the command using execve. If execve fails,
//  * it prints an error message and exits the child process.

void	execute_command(t_cmd *current_cmd, t_shell *shell, t_cmd *head)
{
	char	*path;
	char	**split;

	if (current_cmd->cmd == NULL || current_cmd->cmd[0] == '\0')
		clean_exit (1, shell, head);
	if (check_for_whitespace(current_cmd->cmd) == 0)
	{
		split = ft_split(current_cmd->cmd, ' ');
		if (access(split[0], F_OK | X_OK) != 0)
			path = get_path(split[0], shell->envp);
		else
			path = ft_strdup(split[0]);
		execve(path, split, shell->envp);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		printf("minishell: %s: command not found\n", split[0]);
		free_matrix(split);
		free(path);
		clean_exit (127, shell, head);
	}
	dup2(STDOUT_FILENO, STDERR_FILENO);
	printf("minishell: %s: command not found\n", current_cmd->cmd);
	clean_exit (127, shell, head);
}

//  * This function is responsible for handling pipes between commands in the
//  * command table. If the current command writes to a pipe, it checks if the
//  * next command reads from a pipe. If true, it duplicates the read end of
//  * the pipe to the standard input. It then closes both ends of the pipe.

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
