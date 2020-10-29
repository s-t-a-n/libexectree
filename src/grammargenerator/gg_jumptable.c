
#include "grammargenerator.h"

void				*gramgen_lex_lookup_add(t_list **tab,
											char *line,
											void *subject)
{
	size_t			index;

	if (ft_isalnum(*line))
		index = *line;
	else if (ft_isalnum(*(line + 1)))
		index = *(line + 1);
	else
		return (NULL);
	return (index >= 0 && index < SYMBOL_SETSIZE ? lst_addback(&tab[index], subject) : NULL);
}

//void				*gramgen_parse_lookup_add(t_list *tab,
//											size_t index,
//											char *line,
//											void *subject)
//{
//	unsigned int	c;
//
//	return (lst_addback(&tab[index], subject));
//}

//size_t				gramgen_parse_lookup_add(void *vec, )
//{
//
//}
