#ifndef UNKNOW_PROJECT_ITEM_H
# define UNKNOW_PROJECT_ITEM_H

#include "unknow_project_player.h"

typedef struct  	s_item
{
	char			*name;
	t_mesh			*mesh;
	int				picked_up; // 0 no | 1 yes
	int 			(*pf)(t_player*);
}       			t_item;

typedef struct	s_item_list
{
	t_item		*item;
	int			size;
	int			max_size;
}				t_item_list;

t_item_list 	create_t_item_list();
t_item_list 	*initialize_t_item_list();
void			t_item_list_push_back(t_item_list *dest, t_item to_add);
void			t_item_list_erase(t_item_list *dest, int index);
void			delete_t_item_list(t_item_list dest);
void			free_t_item_list(t_item_list *dest);
void			clean_t_item_list(t_item_list *dest);
t_item			t_item_list_at(t_item_list *dest, int index);
t_item			*t_item_list_get(t_item_list *dest, int index);
int				t_item_list_get_index(t_item_list *dest, t_item *mesh);

#endif
