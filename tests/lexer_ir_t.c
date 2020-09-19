#include <stdio.h>
#include <stdlib.h>

#include "lexer_ir.h"

int				main(int argc, char **argv)
{
	if (argc == 2)
	{
		t_lexer_ir *ir = lexer_ir_generate(argv[1]);
		if (ir)
		{
			lexer_ir_dump(ir);
			lexer_ir_destroy(ir);
		}
		return (0);
	}
	else
		return (1);
}
