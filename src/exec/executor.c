/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:34:07 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/21 16:45:01 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		executor_with_pipes(t_cmd *c_table, t_shell *shell);
void	handle_pipe(t_cmd *c_table, int *pipefd);
void	execute_command(t_cmd *current_cmd, char **envp);
int		executor_main(t_cmd *command, t_shell *shell);
int		executor_no_pipes(t_cmd *c_table, t_shell *shell);
int		check_for_trailing_whitespace(char *str);

void	putstr_error(char *str)
{
//	char	*minishell;
	int		i;

//	minishell = "minishell: ";
	i = 0;
	while (str[i])
	{
		write (2, &str[i], 1);
		i++;
	}
	write (2, "\n", 1);
}

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
// 	c_table->cmd = "$new";
// 	c_table->infile = NULL;
// 	c_table->outfile = NULL;
// 	c_table->read_pipe = 0;
// 	c_table->write_pipe = 0;
// 	c_table->heredoc = NULL;
// 	c_table->next = NULL;
// 	new = malloc(sizeof (t_cmd));
// 	new->cmd = "env";
// 	new->infile = NULL;
// 	new->outfile = NULL;
// 	new->read_pipe = 0;
// 	new->write_pipe = 0;
// 	// c_table->next = new;
// 	// new->next = NULL;
// 	// new2 = malloc(sizeof (t_cmd));
// 	// new2->cmd = "unset hallo= HALLO";
// 	// new2->infile = NULL;
// 	// new2->outfile = NULL;
// 	// new2->read_pipe = 0;
// 	// new2->write_pipe = 0;
// 	// new2->append = 0;
// 	// // c_table->next->next = new2;
// 	// new2->next = NULL;
// 	// new3 = malloc(sizeof (t_cmd));
// 	// new3->cmd = "ls";
// 	// new3->infile = NULL;
// 	// new3->outfile = NULL;
// 	// new3->read_pipe = 0;
// 	// new3->write_pipe = 0;
// 	// c_table->next->next->next = new3;
// 	// new3->next = NULL;
// 	// c_table = malloc(sizeof (t_cmd));
// 	// c_table->cmd = "grep s";
// 	// c_table->infile = "infile";
// 	// c_table->outfile = "outfile";
// 	// c_table->read_pipe = 0;
// 	// c_table->write_pipe = 0;
// 	// c_table->next = NULL;

// 	shell = malloc(sizeof (t_shell *));
// 	shell->envp = init_env(envp);
// 	i = 1;
// 	while (i < 2)
// 	{
// 		executor_main(new, shell);
// 		printf("finished %i\n\n\n", 1);
// 		executor_main(c_table, shell);
// 		printf("finished %i\n\n\n", 2);
// 		executor_main(new, shell);
// 		printf("finished %i\n\n\n", 3);
// 		// executor_main(new2, shell);
// 		// printf("finished %i\n\n\n", 4);
// 		// executor_main(new, shell);
// 		// printf("finished %i\n\n\n", 5);
// 		i++;
// 	}
// 	return (0);
// }

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
	stdin = dup(STDIN_FILENO);
	if (check_builtin(c_table) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			if (redirect(c_table, NULL, shell) == -1)
				return (-1);
			execute_command(c_table, shell->envp);
		}
		waitpid(pid, &status, 0);
		shell->exit_code = WEXITSTATUS(status);
	}
	else
	{
		redirect(c_table, NULL, shell);
		handle_builtin(c_table, shell);
	}
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

	stdin = dup(STDIN_FILENO);
	while (c_table != NULL)
	{
		if (c_table->write_pipe == 1)
		{
			if (pipe(pipefd) == -1)
				return (0);
		}
		pid = fork();
		if (pid == 0)
		{
			redirect(c_table, pipefd, shell);
			execute_command(c_table, shell->envp);
		}
		handle_pipe(c_table, pipefd);
		if (c_table->heredoc != NULL)
			waitpid(pid, 0, 0);
		c_table = c_table->next;
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

void	execute_command(t_cmd *current_cmd, char **envp)
{
	char	*path;
	char	**split;

	// putstr_error(current_cmd->cmd);
	//change the flags
	// printf("[%s]\n", current_cmd->cmd);
	if (current_cmd->cmd == NULL || current_cmd->cmd[0] == '\0')
		exit (1);
	if (check_for_trailing_whitespace(current_cmd->cmd) == 0)
	{
		split = ft_split(current_cmd->cmd, ' ');
		if (access(split[0], F_OK | X_OK) != 0)
			path = get_path(split[0], envp);
		else
			path = split[0];
		execve(path, split, envp);
		free(path);
		dup2(STDOUT_FILENO, STDERR_FILENO);
		printf("minishell: %s: command not found\n", split[0]);
		exit (127);
	}
	dup2(STDOUT_FILENO, STDERR_FILENO);
	printf("minishell: %s: command not found\n", current_cmd->cmd);
	exit (127);
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

int	check_for_trailing_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
	{
		i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}
