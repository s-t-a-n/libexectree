/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_processing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:57 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 22:13:16 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "lexergenerator.h"

static uint8_t	attempt_stitch(t_lexer_ir *ir, t_lex_token *token)
{
	t_lex_node *node;

	node = lexer_find_node(ir, (char *)token->sig);
	if (node)
	{
		token->type = NONTERMINAL;
		free(token->sig);
		token->sig = node;
		return (0);
	}
	else
		return (1);
}

uint8_t			lexer_post_process(t_lexer_ir *ir)
{
	uint8_t	errors;
	t_list	*lst;

	if ((lst = ir->post))
	{
		errors = 0;
		while (lst)
		{
			if (attempt_stitch(ir, (t_lex_token *)lst->subject) != 0)
			{
				logger(CRIT, 3, "lexer_generator", "nonterminal has no definition : ", (char *)((t_lex_token *)lst->subject)->sig);
				errors++;
			}
			lst = lst->next;
		}
	}
	else
		return(0);
	lst_destroy(&ir->post, false);
	return (errors);
}
