/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_generator_definition_lifetime.c              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 18:28:15 by sverschu      #+#    #+#                 */
/*   Updated: 2020/09/06 18:32:21 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexergenerator.h"

t_lex_definition	*lexer_definition_create(	t_lex_definition_type type,
												char *terminal,
												t_lex_object *nonterminal)
{
	t_lex_definition *def;

	if (!terminal)
		return(NULL);
	def = malloc(sizeof(t_lex_definition));
	if (def)
	{
		def->type = type;
		def->terminal = terminal;
		def->nonterminal = nonterminal;
	}
	return(def);
}

t_lex_definition	*lexer_definition_destroy(t_lex_definition *def)
{
	free(def->terminal);
	free(def);
	return(NULL);
}
