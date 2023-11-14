/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/14 12:50:03 by fgabler          ###   ########.fr       */
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

#endif
