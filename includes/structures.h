/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/13 13:37:18 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H


///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////PROCESS/MANAGMENT////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct	s_process
{
	int		time_to_setup;
	int		time_to_lex;
	int		time_to_pars;
	int		time_to_exec;
}	t_process;

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
	t_process		process;
}	t_lexer;

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

typedef struct s_shell
{
	char		**envp;
	t_process	*process;
}t_shell;

///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////COOMMAND/TABLE///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

typedef struct s_parser
{
	int		error_accured;
	t_lexer	*lexer;
	t_cmd	*command;
	//	t_shell	*shell;
}	t_parser;

#endif
