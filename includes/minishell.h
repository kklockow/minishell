/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:47 by kklockow          #+#    #+#             */
/*   Updated: 2024/01/12 15:25:14 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////STANDARD//LIBRARY///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////SELFMADE//LIBARY///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

# include "structures.h"
# include "libft.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTIONS///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//INIT
void	get_input(t_coordinate *coordinate);
void	input_check(int ac, char **av, t_coordinate *coordinate);
char	**init_env(char **envp);
int		ft_env_len(char **envp);
char	*ft_strdup_init(const char *s1);

//SETUP
void	first_setup(t_coordinate *coordinate, char **envp);
void	setup_structs(t_coordinate *coordinate);

//LEXER
int		lexing(t_lexer *lexer, t_process *process);
void	move_to_next_token(int	*position, char *input);
void	move_to_next_token(int	*position, char *input);
int		find_quote_pair(t_lexer *lexer);
int		add_token_node(t_lexer *lexer);
int		get_single_tokens(t_lexer *lexer, char token);
int		double_greater_and_smaler(t_lexer *lexer);
int		tag_word(t_lexer *lexer);
int		time_to_lex(t_lexer *lexer);
void	skip_whitespace(t_lexer *lexer);
void	free_struct_and_stop_lexing(t_lexer **lexer);
t_data	*go_to_last_lexer_node(t_data *lexer);

//COMMAND TABLE
int		add_space_check(t_data *data);
int		is_redirect(t_data *data);
int		command_table(t_parser *parser, t_process *process);
void	command_node_add_back(t_cmd **command, t_parser *parser);
void	fill_command_struct(t_parser *parser);
void	pipe_roules_check(t_parser *parser);
void	redirect_roules_check(t_parser *parser);
void	syntax_check(t_parser *parser);
void	setup_parser_struct(t_parser *parser, t_cmd *command, t_lexer *lexer);
void	syntax_error_print(t_data *data);
void	heredoc_argument(t_data *data, t_cmd *command);
void	repeat_set_data_next_save(t_data **data);

//EXPANDER
int		expander(t_shell *shell, t_data *s);
void	expand(t_parser *s);
int		expand_to_home(t_shell *shell, t_data *s);
int		get_sign_location(char *str);
char	*get_variable_to_expand(char *str, int sign_location);
char	*search_for_var(char *var, char **envp, t_shell *shell);
char	*split_variable(char *str);
void	handle_non_sign(t_data *s);
void	free_and_do_again(char *var, char *vc, t_shell *shell, t_data *s);
void	update_cmd(t_data *s, char *var, int start, char *name);
int		get_len_export(char *str);

//EXECUTOR
t_cmd	**get_command_struct(void);
t_shell	**get_shell_struct(void);
int		executor_main(t_cmd *command, t_shell *shell);
int		redirect(t_cmd *c_table, int *pipefd, t_shell *shell);
void	check_envp(char **envp);
char	**get_possible_paths(char **envp);
char	*get_path(char *cmd, char **envp);
char	**ft_split(char const *s, char c);
char	*get_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_matrix(char **to_free);
size_t	ft_strlen(const char *c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
int		here_doc_handling(char *delimiter);
int		check_for_whitespace(char *str);
void	handle_pipe(t_cmd *c_table, int *pipefd);
void	execute_command(t_cmd *current_cmd, t_shell *shell, t_cmd *head);
void	check_for_path(t_cmd *cmd, t_shell *shell);
void	cleaning_up(pid_t pid, int stdin, int stdout, t_shell *shell);
void	clean_exit(int exit_code, t_shell *shell, t_cmd *cmd);

//BUILTIN
int		echo_builtin(char *str);
int		pwd_builtin(void);
int		cd_builtin(char *str, t_shell *shell);
int		env_builtin(char **envp);
int		export_builtin(char *str, t_shell *shell);
int		unset_builtin(char *str, t_shell *shell, int i);
void	exit_builtin(t_cmd *cmd, t_shell *shell);
int		handle_builtin_piped(t_cmd *current_cmd, t_shell *shell, t_cmd *head);
int		count_len(char *str, int i);

//BUILTIN_UTILS
int		handle_builtin(t_cmd *current_cmd, t_shell *shell);
int		check_builtin(t_cmd *current_cmd);
char	**env_remove_one(char **envp, char *str, int len);
char	**env_add_new(char **envp, char *str);
int		count_till_equal(char *str);
int		check_for_newline(char *str);

//SIGNALS
void	catch_signals(t_coordinate *coordinate);
void	command_c(void);
void	command_quit(void);
void	hide_ctrl_chars(t_coordinate *coordinate);
void	handle_sigint_in_child(void);
void	handle_sigquit_in_child(void);

//FREE STRUCTS
void	free_structs(t_coordinate *coordinate);
void	free_lexer_struct(t_lexer **lexer);
void	save_free(void **pointer);
void	parser_free(t_parser **parser);
void	shell_struct_free(t_shell **shell);
void	free_command_struct(t_cmd **command);

//HANDLE PROCESS
void	stop_process(t_process *process);
void	set_error_code(t_shell *shell, int error_code);
void	stop_loop(t_coordinate *coordinate);
void	if_null_stop_process(char *string, t_parser *parser);

#endif
