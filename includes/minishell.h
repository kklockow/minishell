/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:47 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/11 15:18:53 by kklockow         ###   ########.fr       */
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

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////SELFMADE//LIBARY///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

# include "structures.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTIONS///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//INIT

char	**init_env(char **envp);
int		ft_env_len(char **envp);
char	*ft_strdup_init(const char *s1);

//LEXER

void	move_to_next_token(int	*position, char *input);

//EXECUTOR
int		executor_main(t_cmd *c_table, t_shell *shell);
int		redirect(t_cmd *c_table, int *pipefd);

void	check_envp(char **envp);
char	**get_possible_paths(char **envp);
char	*get_path(char *cmd, char **envp);
char	**ft_split(char const *s, char c);
char	*get_path(char *cmd, char **envp);
char	*ft_strjoin(char const *s1, char const *s2);

void	free_matrix(char **to_free);

size_t	ft_strlen(const char *c);
void	putstr_error(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);

int		here_doc_handling(char *delimiter);

//BUILTIN_UTILS

int		handle_builtin(t_cmd *current_cmd, t_shell *shell);
int		check_builtin(t_cmd *current_cmd);
char	**env_remove_one(char **envp, char *str, int len);
char	**env_add_new(char **envp, char *str);
int		count_till_equal(char *str);

//BUILTIN

int		echo_builtin(char *str);
int		pwd_builtin(char *str);
int		cd_builtin(char *str, t_shell *shell);
int		env_builtin(char **envp);
int		export_builtin(char *str, t_shell *shell);
int		unset_builtin(char *str, t_shell *shell);


#endif
