/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kklockow <kklockow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:35:47 by kklockow          #+#    #+#             */
/*   Updated: 2023/12/12 10:25:29 by fgabler          ###   ########.fr       */
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
void	skip_whitespace(t_lexer *lexer);
void	free_struct_and_stop_lexing(t_lexer **lexer);
t_data	*go_to_last_lexer_node(t_data *lexer);

//COMMAND TABLE
int		is_redirect(t_data *data);
int		command_table(t_lexer *lexer, t_cmd *command);
void	command_node_add_back(t_cmd **command, t_parser *parser);
void	fill_command_struct(t_parser *parser);
void	pipe_roules_check(t_parser *parser);
void	redirect_roules_check(t_parser *parser);
void	syntax_check(t_parser *parser);
void	setup_parser_struct(t_parser *parser, t_cmd *command, t_lexer *lexer);
void	syntax_error_print(t_data *data);


//UTILS
void	get_input(char **input, t_process *process);
int		setup_structs(t_cmd **command, t_lexer **lexer,
		t_process *process, char *input);
void	set_process_stat(t_process *process, int lexer, int parser, int exec);

#endif
