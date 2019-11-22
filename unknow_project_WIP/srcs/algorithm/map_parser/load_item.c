/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adjouber <adjouber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 13:29:58 by adjouber          #+#    #+#             */
/*   Updated: 2019/10/31 13:29:59 by adjouber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unknow_project.h"

t_item			create_t_item(t_mesh mesh)
{
	t_item		item;

	if (ft_strcmp(mesh.name, "Ammo_Pack") == '_')
		item = create_ammo_pack(mesh.hp * -1);
	else if (ft_strcmp(mesh.name, "Health_Pack") == '_')
		item = create_health_pack();
	else if (ft_strcmp(mesh.name, "Armor_Pack") == '_')
		item = create_armor_pack();
	else if (ft_strcmp(mesh.name, "Jet_Pack") == '_')
		item = create_jet_pack();
	else if (ft_strcmp(mesh.name, "Card") == '_')
		item = create_color_card(mesh.hp * -1);
	return (item);
}

t_item_list		*load_items(t_mesh_list *meshs)
{
	t_item_list	*result;
	t_item		item;
	int			i;

	i = 0;
	result = initialize_t_item_list();
	while (i < meshs->size)
	{
		if (t_mesh_list_at(meshs, i).collectible == 1)
		{
			item = create_t_item(t_mesh_list_at(meshs, i));
			t_item_list_push_back(result, item);
		}
		i++;
	}
	return (result);
}
