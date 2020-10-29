/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   process_word.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: sverschu <sverschu@student.codam.n>          +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/19 22:11:03 by sverschu      #+#    #+#                 */
/*   Updated: 2020/10/25 20:15:20 by sverschu      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vector.h"

#include "logger.h"
#include "grammargenerator.h"

uint8_t				gg_process_word(t_gram_rule *def, char **line)
{
	t_gram_token	*token;
	char			*word;
	size_t			wordlen;

	wordlen = 0;
	while (*(*line + wordlen) && (*(*line + wordlen) != ' ') && *(*line + wordlen) != '|')
		wordlen++;
	word = ft_strsub(*line, 0, wordlen);
	(*line) += wordlen + (*(*line + wordlen) ? 1 : 0);
	if (word)
	{
		token = gramgen_token_create(TERMINAL, word);
		if (token && vector(&def->tokens, V_PUSHBACK, 0, token))
		{
			logger(INFO, 3, "grammar_generator",
							"adding (word) terminal to rule",
							word);
			return (0);
		}
		free(word);
		gramgen_token_destroy(token);
	}
	return (1);
}
