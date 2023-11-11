/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:01:44 by fgabler           #+#    #+#             */
/*   Updated: 2023/11/11 16:48:24 by fgabler          ###   ########.fr       */
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
	DOUBBLE_GREAT,
	DOUBBLE_LESS,
	SINGLE_QUOTE,
	DOUTBLE_QUOTE,
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
