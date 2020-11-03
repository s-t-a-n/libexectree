/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   post_processing.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:10:57 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/19 23:38:36 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "grammargenerator.h"

static uint8_t	attempt_stitch(t_grammar_ir *ir, t_gram_token *token)
{
	t_gram_production *production;

	production = grammar_ir_find_production(ir, (char *)token->terminal);
	if (production)
	{
		free(token->terminal);
		token->terminal = NULL;
		token->production = production;
		return (0);
	}
	else
		return (1);
}

uint8_t			gramgen_post_process(t_grammar_ir *ir)
{
	uint8_t	errors;
	t_list	*lst;

	if ((lst = ir->post))
	{
		errors = 0;
		while (lst)
		{
			if (attempt_stitch(ir, (t_gram_token *)lst->subject) != 0)
			{
				logger(CRIT, 3, "grammar_generator",
								"nonterminal has no rule",
								(char *)((t_gram_token *)lst->subject)->terminal);
				errors++;
			}
			lst = lst->next;
		}
	}
	else
		return (0);
	lst_destroy(&ir->post, false);
	return (errors);
}
