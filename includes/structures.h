/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2024/01/07 15:49:24 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////GLOBAL/STRUCTS///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

struct	s_parser;
struct	s_cmd;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////PROCESS/MANAGMENT////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_process
{
	int		*run_loop;
	int		time_to_setup;
	int		time_to_lex;
	int		time_to_pars;
	int		time_to_exec;
}	t_process;

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////SHELL/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_shell
{
	char		**envp;
	int			exit_code;
	t_process	*process;
}t_shell;

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////LEXER/////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef enum e_type
{
	WORD,
	PIPE,
	GREATER,
	LESS,
	DOUBLE_GREAT,
	DOUBLE_LESS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_type;

typedef struct s_data
{
	t_type			type;
	char			*str;
	int				token_len;
	int				space;
	struct s_data	*next;
}	t_data;

typedef struct s_lexer
{
	int				pos;
	int				set_token;
	t_data			*head;
	char			*input;
	t_shell			*shell;
}	t_lexer;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////COOMMAND/TABLE///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_parser
{
	int				error_accured;
	int				new_pipe;
	t_lexer			*lexer;
	struct s_cmd	*command;
	t_shell			*shell;
}	t_parser;

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////EXECUTOR//////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_cmd
{
	char			*cmd;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				read_pipe;
	int				write_pipe;
	int				append;
	int				heredoc_as_argument;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_gpp
{
	int		i;
	int		j;
	int		k;
	char	**possible_paths;
	char	*temp;
}t_gpp;

typedef struct s_update
{
	char	*new;
	int		i_old;
	int		i_new;
	int		i_var;
	int		for_malloc;
}t_update;

///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////COORDINAR/////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_coordinate
{
	t_process	process;
	t_parser	*parser;
	t_cmd		*command;
	t_shell		*shell;
	char		*input;
	int			first_set_up;
	int			run_loop;
}	t_coordinate;

#endif
