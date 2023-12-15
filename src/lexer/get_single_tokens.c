/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_single_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:25:56 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/15 11:09:50 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fill_node(t_lexer *lexer, char token);
static void	get_token_typ(char token, t_data *data);
static void	get_token_string(char token, t_data *data);
static void	check_space_after_token(t_data *data, t_lexer *lexer);

int	get_single_tokens(t_lexer *lexer, char token)
{
	if (lexer->input[lexer->pos] != token
		|| lexer->shell->process->time_to_lex == false || lexer->set_token == true)
		return (false);
	if (add_token_node(lexer) == false)
		return (false); //free
	fill_node(lexer, token);
	lexer->set_token = true;
	return (true);
}

static void	fill_node(t_lexer *lexer, char token)
{
	t_data	*fill_node;

	fill_node = go_to_last_lexer_node(lexer->head);
	get_token_typ(token, fill_node);
	get_token_string(token, fill_node);
	check_space_after_token(fill_node, lexer);
	lexer->pos++;
	fill_node->next = NULL;
	fill_node->token_len = 1;
}

static void	get_token_typ(char token, t_data *data)
{
	if (token == '>')
		data->type = GREATER;
	else if (token == '<')
		data->type = LESS;
	else if (token == '|')
		data->type = PIPE;
}

static void	get_token_string(char token, t_data *data)
{
	if (token == '>')
		data->str = ft_strdup(">");
	else if (token == '<')
		data->str = ft_strdup("<");
	else if (token == '|')
		data->str = ft_strdup("|");
}

static void	check_space_after_token(t_data *data, t_lexer *lexer)
{
	if (lexer->input[lexer->pos + 1] == ' '
		&& lexer->input[lexer->pos + 1] != '\0')
		data->space = true;
	else
		data->space = false;
}
