#ifndef NODE_H
# define NODE_H

typedef struct	s_node t_node;
typedef struct	s_node
{
	t_node		*parent;
	t_node		*left;
	t_node		*right;
	void		*children;
}				t_node;

#endif
