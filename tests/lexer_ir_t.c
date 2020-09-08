#include <stdio.h>
#include <stdlib.h>

#include "lexer_ir.h"

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_lexer_ir *ir = lexer_generator(argv[1]);
		if (ir)
			printf("CREATED LEXER IR SUCCESFULLY!\n");
		lexer_generator_destroy(ir);
		return (0);
	}
	else
		return (1);
}
