/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/09 19:29:17 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		executor_with_pipes(t_cmd *c_table, t_shell *shell, t_cmd *head);
int		executor_main(t_cmd *command, t_shell *shell);
int		executor_no_pipes(t_cmd *c_table, t_shell *shell);

int	executor_main(t_cmd *command, t_shell *shell)
{
	t_cmd	*head;

	if (shell->process->time_to_exec != true)
		return (-1);
	if (command->next == NULL)
		executor_no_pipes(command, shell);
	else
	{
		head = command;
		executor_with_pipes(command, shell, head);
	}
	return (0);
}

	// if (command->cmd && command->cmd[ft_strlen(command->cmd) - 1] == '\1')
	// 	command->cmd = ft_strjoin_mod(command->cmd, " ");

//  * This function checks if the given command is a built-in command. If it is,
//  * it redirects I/O and executes the built-in command. If it's not a built-in
//  * command, it forks a new process, redirects I/O, and executes the external
//  * command in the child process.

int	do_unpiped_command(t_cmd *c_table, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (redirect(c_table, NULL, shell) == -1)
			return (-1);
		execute_command(c_table, shell, c_table);
	}
	waitpid(pid, &status, 0);
	shell->exit_code = WEXITSTATUS(status);
	return (0);
}

int	executor_no_pipes(t_cmd *c_table, t_shell *shell)
{
	int		stdin;
	int		stdout;

	if (c_table->heredoc != NULL)
		signal(SIGINT, SIG_IGN);
	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (check_builtin(c_table) == 0)
		do_unpiped_command(c_table, shell);
	else
	{
		redirect(c_table, NULL, shell);
		shell->exit_code = handle_builtin(c_table, shell);
	}
	command_c();
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	return (0);
}

int	exec_piped_child(t_cmd *c_table, t_shell *shell, t_cmd *head, int *pipefd)
{
	redirect(c_table, pipefd, shell);
	if (check_builtin(c_table) == 1)
		handle_builtin_piped(c_table, shell, head);
	else
		execute_command(c_table, shell, head);
	return (0);
}

//  * This function iterates through the command table, creating pipes as needed
//  * and forking processes for each command. It redirects I/O and executes
//  * commands in child processes. It also handles inter-process communication
//  * with pipes and waits for child processes to finish execution.

int	executor_with_pipes(t_cmd *c_table, t_shell *shell, t_cmd *head)
{
	int		pipefd[2];
	pid_t	pid;
	int		stdin;
	int		stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	while (c_table != NULL)
	{
		if (c_table->heredoc != NULL)
			signal(SIGINT, SIG_IGN);
		if (c_table->write_pipe == 1)
			if (pipe(pipefd) == -1)
				return (0);
		pid = fork();
		if (pid == 0)
			exec_piped_child(c_table, shell, head, pipefd);
		handle_pipe(c_table, pipefd);
		if (c_table->heredoc != NULL)
			waitpid(pid, 0, 0);
		c_table = c_table->next;
		command_c();
	}
	cleaning_up(pid, stdin, stdout, shell);
	return (0);
}

// void	check_for_path(t_cmd *cmd, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd->cmd[i] == ' ')
// 		i++;
// 	if (cmd->cmd[i] == '.' && cmd->cmd[i + 1] == '/')
// 	{
// 		//maybe stat function also
// 		if (access(cmd->cmd, F_OK | X_OK) != 0)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(cmd->cmd, 2);
// 			perror("\1");
// 			clean_exit(127, shell, cmd);
// 		}
// 	}
// }

//  * This function splits the given command into an array of strings,
//  * checks if the command is accessible, and retrieves its full path.
//  * It then attempts to execute the command using execve. If execve fails,
//  * it prints an error message and exits the child process.

// void	execute_command(t_cmd *current_cmd, t_shell *shell, t_cmd *head)
// {
// 	char	*path;
// 	char	**split;

// 	if (current_cmd->cmd == NULL || current_cmd->cmd[0] == '\0')
// 		clean_exit (1, shell, head);
// 	if (current_cmd->heredoc_as_argument == 1)
// 		current_cmd->cmd = ft_strjoin(current_cmd->cmd, "\1.heredoc");
// 	check_for_path(current_cmd, shell);
// 	split = ft_split(current_cmd->cmd, '\1');
// 	if (access(split[0], F_OK | X_OK) != 0)
// 		path = get_path(split[0], shell->envp);
// 	else
// 		path = ft_strdup(split[0]);
// 	execve(path, split, shell->envp);
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(split[0], 2);
// 	ft_putstr_fd(": command not found\n", 2);
// 	free_matrix(split);
// 	free(path);
// 	clean_exit (127, shell, head);
// }

//  * This function is responsible for handling pipes between commands in the
//  * command table. If the current command writes to a pipe, it checks if the
//  * next command reads from a pipe. If true, it duplicates the read end of
//  * the pipe to the standard input. It then closes both ends of the pipe.

// void	handle_pipe(t_cmd *c_table, int *pipefd)
// {
// 	if (c_table->write_pipe == 1)
// 	{
// 		if (c_table->next->read_pipe == 1)
// 			dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 	}
// }

// int	check_for_whitespace(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (!str)
// 		return (0);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	if (i == 0)
// 		return (1);
// 	while (str[i] == ' ')
// 	{
// 		i++;
// 		if (str[i] == '\0')
// 			return (1);
// 	}
// 	return (0);
// }
