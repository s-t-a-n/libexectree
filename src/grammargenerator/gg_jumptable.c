
#include "grammargenerator.h"

void				*gramgen_lex_jtable_add(t_list **tab, t_gram_token *token)
{
	size_t			index;

#ifdef DEBUG
	assert(token);
	assert(token->terminal);
#endif

	if (token->terminal && ft_isascii(*token->terminal))
		index = *token->terminal;
	else
		return (NULL);
	return (index >= 0 && index < SYMBOL_SETSIZE ? lst_addback(&tab[index], token) : NULL);
}
