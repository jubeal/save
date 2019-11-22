
#include "unknow_project.h"

void    save_player(t_engine *engine, t_mesh current, int fd)
{
    char    *test;
    int     j;

    write(fd, "player: Player ", 15);

    test = ft_strjoinf(ft_ftoa(current.pos.x), " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.pos.y), 3);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.pos.z), 3);
    test = ft_strjoinf(test, " ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_ftoa(current.size.x), " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.size.y), 3);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.size.z), 3);
    test = ft_strjoinf(test, " ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    write(fd, "NULL ", 5);

    test = ft_strjoin(ft_ftoa(current.kinetic), " ");
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_ftoa(current.rotation.x), " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.rotation.y), 3);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_ftoa(current.rotation.z), 3);
    test = ft_strjoinf(test, " ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_ftoa(t_face_list_get(current.faces, 0)->color.r), " ", 1);
    test = ft_strjoinf(test, ft_ftoa(t_face_list_get(current.faces, 0)->color.g), 3);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_ftoa(t_face_list_get(current.faces, 0)->color.b), 3);
    test = ft_strjoinf(test, " 1.0 ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_itoa(engine->user_engine->player->hp), " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->armor), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->fuel), 2);
    test = ft_strjoinf(test, " ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_itoa(engine->user_engine->player->weapons[0].ammo), " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[0].total_ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[1].ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[1].total_ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[2].ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[2].total_ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[3].ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[3].total_ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[4].ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->weapons[4].total_ammo), 2);
    test = ft_strjoinf(test, " ", 1);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);

    test = ft_strjoinf(ft_itoa(engine->user_engine->player->red_card), " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->blue_card), 2);
    test = ft_strjoinf(test, " ", 1);
    test = ft_strjoinf(test, ft_itoa(engine->user_engine->player->green_card), 2);
    j = ft_strlen(test);
    write(fd, test, j);
    free(test);
    write(fd, "\n", 1);
}

void    save_map(t_engine *engine, int wich)
{
    char    *command;
    char    *file;
    char    *test;
    int     i;
    int     j;
    t_mesh  current;

    file = ft_itoa(wich);
    command = ft_strjoin("rm -rf ressources/map/save", file);
    command = ft_strjoinf(command, ".map", 1);
    system(command);
    command = ft_strjoinf("touch ressources/map/save", file, 2);
    command = ft_strjoinf(command, ".map", 1);
    system(command);

    int fd = open(command + 6, O_WRONLY);
    // printf("%s\n", command + 6);
    // printf("%d\n", fd);
    free(command);
    if (fd < 0)
        error_exit(-7001, "impossible fd");
    i = 0;
    while (i < engine->physic_engine->mesh_list->size)
    {
        current = t_mesh_list_at(engine->physic_engine->mesh_list, i);
        if (current.primitive == -1)
            save_player(engine, current, fd);
        else if (current.primitive >= 0 && (current.is_visible || !current.no_hitbox))
        {
            //- mesh primitive ou # + obj path
            if (current.collectible == 1)
                write(fd, "item: ", 6);
            else if (current.primitive == 0)
                write(fd, "plane: ", 7);
            else if (current.primitive == 1)
                write(fd, "cube: ", 6);
            else if (current.primitive == 10)
                write(fd, "# ", 2);
            //- mesh name
            j = ft_strlen(current.name);
            test = ft_strjoin(current.name, " ");
            printf("%s\n", test);
            write(fd, test, j + 1);
            //- coord 3 en 0.0 0.0 0.0
            test = ft_strjoinf(ft_ftoa(current.pos.x), " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.pos.y), 3);
            test = ft_strjoinf(test, " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.pos.z), 3);
            test = ft_strjoinf(test, " ", 1);
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            //- size 3 en 0.0 0.0 0.0
            test = ft_strjoinf(ft_ftoa(current.size.x), " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.size.y), 3);
            test = ft_strjoinf(test, " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.size.z), 3);
            test = ft_strjoinf(test, " ", 1);
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            //- texture path
            if (current.texture != NULL)
            {
                printf("%s\n", current.texture->path);
                test = ft_strjoin(current.texture->path, " ");
                j = ft_strlen(test);
                write(fd, test, j);
                free(test);
            }
            else
                write(fd, "NULL ", 5);
            //- gravity
            test = ft_strjoin(ft_ftoa(current.kinetic), " ");
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            //- rotation 3 en 0.0 0.0 0.0
            test = ft_strjoinf(ft_ftoa(current.rotation.x), " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.rotation.y), 3);
            test = ft_strjoinf(test, " ", 1);
            test = ft_strjoinf(test, ft_ftoa(current.rotation.z), 3);
            test = ft_strjoinf(test, " ", 1);
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            // - color 4 en 0.0 0.0 0.0 0.0
            test = ft_strjoinf(ft_ftoa(t_face_list_get(current.faces, 0)->color.r), " ", 1);
            test = ft_strjoinf(test, ft_ftoa(t_face_list_get(current.faces, 0)->color.g), 3);
            test = ft_strjoinf(test, " ", 1);
            test = ft_strjoinf(test, ft_ftoa(t_face_list_get(current.faces, 0)->color.b), 3);
            test = ft_strjoinf(test, " 1.0 ", 1);
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            test = ft_strjoinf(ft_itoa(current.hp), " ", 1);
            j = ft_strlen(test);
            write(fd, test, j);
            free(test);
            // - visibility
            if (current.no_hitbox == 1)
                write(fd, "#\n", 2);
            else if (current.is_visible == 0)
                write(fd, "*\n", 2);
            else
                write(fd, "\n", 1);
        }
        i++;
    }
}
