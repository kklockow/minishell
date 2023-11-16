/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/16 15:15:20 by kklockow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

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
	int				read_pipe;
	int				write_pipe;
	struct s_cmd	*next;
}	t_cmd;

#endif
