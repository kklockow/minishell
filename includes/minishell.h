/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:47 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/04 11:14:15 by fgabler          ###   ########.fr       */
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

///////////////////////////////////////////////////////////////////////////////
////////////////////////////////SELFMADE//LIBARY///////////////////////////////
///////////////////////////////////////////////////////////////////////////////

# include "structures.h"
# include "libft.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////FUNCTIONS///////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//LEXER
int		lexing(t_lexer *lexer);
int		find_quote_pair(t_lexer *lexer);
int		add_token_node(t_lexer *lexer);
int		get_single_tokens(t_lexer *lexer, char token);
int		double_greater_and_smaler(t_lexer *lexer);
int		tag_word(t_lexer *lexer);
int		time_to_lex(t_lexer *lexer);
void	set_up_lexer_struct(t_lexer *lexer, char *input);
void	skip_whitespace(t_lexer *lexer);
void	free_struct_and_stop_lexing(t_lexer **lexer);
t_data	*go_to_last_lexer_node(t_data *lexer);

//PARSER


//UTILS
int		setup_structs(t_cmd **command, t_lexer **lexer, t_process *process);
void	get_input(char *input, t_process *process);

#endif
