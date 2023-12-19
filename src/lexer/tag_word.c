/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tag_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:21:03 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 16:45:22 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_word(char c);
static void	set_lexer_node(t_lexer *lexer, int token_len);
static void	find_token_len(t_lexer *lexer, int *token_len);
static int	is_space_after_token(t_lexer *lexer, int token_len);

int	tag_word(t_lexer *lexer)
{
	int	token_len;
	if (is_word(lexer->input[lexer->pos]) == false
		|| (lexer->shell->process->time_to_lex == false)
		|| lexer->set_token == true)
		return (false);
	if (add_token_node(lexer) == false)
		return (false);
	find_token_len(lexer, &token_len);
	set_lexer_node(lexer, token_len);
	return (true);
}

static void	find_token_len(t_lexer *lexer, int *token_len)
{
	int	start_pos;

	start_pos = lexer->pos;
	while (is_word(lexer->input[start_pos]) == true && lexer->input[start_pos])
	{
		start_pos++;
	}
	*token_len = start_pos - lexer->pos;
}

static int	is_word(char c)
{
	if ((c == ' ') || (c == '>') || (c == '<') || (c == '|') || (c == '\'')
		|| (c == '\"') || (c == '\0'))
		return (false);
	else
		return (true);
}

static void	set_lexer_node(t_lexer *lexer, int token_len)
{
	t_data		*last_node;

	last_node = go_to_last_lexer_node(lexer->head);
	last_node->token_len = token_len;
	last_node->type = WORD;
	last_node->space = is_space_after_token(lexer, token_len);
	last_node->str = ft_substr(lexer->input, lexer->pos, token_len);
	lexer->pos = lexer->pos + token_len;
	lexer->set_token = true;
}

static int	is_space_after_token(t_lexer *lexer, int token_len)
{
	if (lexer->input[lexer->pos + token_len] == '\0')
		return (false);
	else if (lexer->input[lexer->pos + token_len] == ' ')
		return (true);
	else
		return (false);
}
