/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgabler <mail@student.42heilbronn.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:59:52 by fgabler           #+#    #+#             */
/*   Updated: 2023/12/19 19:54:54 by fgabler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_structs(t_coordinate *coordinate)
{
	free_lexer_struct(&coordinate->parser->lexer);
	parser_free(&coordinate->parser);
	save_free((void **) &coordinate->input);
}
