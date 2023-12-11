/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/07 16:43:49 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

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
	char	**envp;
}t_shell;

#endif
