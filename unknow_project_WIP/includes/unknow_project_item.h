#ifndef UNKNOW_PROJECT_ITEM_H
# define UNKNOW_PROJECT_ITEM_H

#include "unknow_project_engine.h"
#include "unknow_project_player.h"

typedef struct  	s_item
{
	int				type; // 0 = hp | 1 = ammo | 2 = armor
	char			*name;
	t_mesh			*mesh;
	void 			(*pf)(t_player*);
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
t_item			create_health_pack(t_vector3 pos, t_engine *engine);
t_item			create_ammo_pack(t_vector3 pos, t_engine *engine);
t_item			create_armor_pack(t_vector3 pos, t_engine *engine);

#endif