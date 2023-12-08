/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_print.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:16:58 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/08 09:54:39 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_token(t_data *data);
static void	pipe_is_one_token_print(t_data *data);
static int	tow_double_less_no_space(t_data *data);

void	print_syntax_error(t_data *data)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	print_token(data);
	ft_putstr_fd("'\n", 2);
}

static void print_token(t_data *data)
{
	if (data == NULL || data->next == NULL)
	{
		ft_putstr_fd("newline", 2);
		return ;
	}
	else if (tow_double_less_no_space(data) == true)
		ft_putstr_fd("<", 2);
	else
		ft_putstr_fd(data->str, 2);
	pipe_is_one_token_print(data);

}

static void	pipe_is_one_token_print(t_data *data)
{
	if (data->next->type == PIPE && data->space == false)
		ft_putstr_fd(data->next->str, 2);
}

static int	tow_double_less_no_space(t_data *data)
{
	if (data->type == DOUBLE_LESS && data->next->type == DOUBLE_LESS
		&& data->space == false)
		return (true);
	return (false);
}
