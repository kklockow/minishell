/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lexer_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 19:30:05 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/20 16:45:08 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	data_free(t_data **data);

void	free_lexer_struct(t_lexer **lexer)
{
	data_free(&(*lexer)->head);
	(*lexer)->shell = NULL;
	save_free((void **) &(*lexer)->input);
	save_free((void **) lexer);
}

static void	data_free(t_data **data)
{
	t_data	*tmp;

	if (*data == NULL)
		return ;
	while (*data != NULL)
	{
		tmp = (*data)->next;
		save_free((void **) &(*data)->str);
		save_free((void **) data);
		*data = tmp;
	}
	*data = NULL;
}
