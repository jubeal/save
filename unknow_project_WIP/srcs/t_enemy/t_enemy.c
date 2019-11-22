#include "unknow_project.h"

void        enemy_look(t_engine *engine)
{
  int       i;
  t_camera  *cam;
  t_mesh    target;

  i = 0;
  while (i < engine->physic_engine->mesh_list->size)
  {
    target = t_mesh_list_at(engine->physic_engine->mesh_list, i);
    if (ft_strcmp(target.name, "Player") == 0)
      break ;
    i++;
  }
  i = 0;
  while (i < engine->visual_engine->camera_list->size)
  {
    cam = t_camera_list_get(engine->visual_engine->camera_list, i);
    if (cam->body != NULL)
    {
      if (ft_strcmp(cam->body->name, "Enemy") == 0)
      {
        cam->pos = add_vector4_to_vector4(cam->body->pos, create_t_vector4(0.15, 0.45, -0.15));
        t_camera_look_at_point(cam, target.pos);
      }
    }
    i++;
  }
}

void        enemy_shoot(t_engine *engine)
{
    int			i;
	int			diff;
	static int	j = -5;
    t_mesh  	*target;
	t_mesh		*mesh;

    i = 0;
    while (i < engine->physic_engine->mesh_list->size)
    {
        target = t_mesh_list_get(engine->physic_engine->mesh_list, i);
        if (ft_strcmp(target->name, "Enemy") == 0)
        {
			// printf("%d\n", j);
			mesh = cast_ray(engine, target->camera->pos, target->camera->forward, "Enemy");
        	if (mesh != NULL && engine->tick - j == 2 && ft_strcmp(mesh->name, "Player") == 0)
    		{
				// printf("here shoot\n");
				if (engine->user_engine->player->armor != 0)
				{
					if (engine->user_engine->player->armor >= 5)
						engine->user_engine->player->armor -= 5;
					else
					{
						diff = 5 - engine->user_engine->player->armor;
						engine->user_engine->player->armor = 0;
						engine->user_engine->player->hp -= diff;
					}
				}
				else
            		engine->user_engine->player->hp -= 5;
				j = -5;
    		}
    		else if (mesh != NULL && engine->tick - j > 3 && ft_strcmp(mesh->name, "Player") == 0)
			{
				// printf("here load\n");
    			j = engine->tick;
			}
			else if (mesh == NULL || ft_strcmp(mesh->name, "Player") != 0)
				j = -5;
        }
        i++;
    }
}
