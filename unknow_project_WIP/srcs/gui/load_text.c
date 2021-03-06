#include "unknow_project.h"

void    load_letter(t_gui *gui, char *str, int idx)
{
    TTF_Font    *police;
    SDL_Surface *font = NULL;
    SDL_Color color = {0, 0, 0};

    str[1] = '\0';
    police = TTF_OpenFont("ressources/assets/ttf/Tinos-Regular.ttf", 60);
    font = TTF_RenderText_Blended(police, str, color);
    gui->letter[idx]->surface->w = (GLuint)(font->w);
    gui->letter[idx]->surface->h = font->h;
    gui->letter[idx]->surface->internalFormat = 4;
    gui->letter[idx]->surface->pixels = (GLubyte *)malloc (sizeof (GLubyte) * gui->letter[idx]->surface->w * gui->letter[idx]->surface->h * gui->letter[idx]->surface->internalFormat);
	gui->letter[idx]->surface->pixels = font->pixels;
    gui->letter[idx]->letter = str[0];
    TTF_CloseFont(police);
}

void    load_menu(t_gui *gui)
{
    gui->menu[0] = png_load("ressources/assets/imgs/Title_screen.png");
    gui->menu[1] = png_load("ressources/assets/imgs/settings_screen.png");
    gui->menu[2] = png_load("ressources/assets/imgs/controls_screen.png");
    gui->menu[3] = png_load("ressources/assets/imgs/credits_screen.png");
    gui->menu[4] = png_load("ressources/assets/imgs/pause_menu.png");
    gui->menu[5] = png_load("ressources/assets/imgs/settings_pause_menu.png");
    gui->menu[8] = png_load("ressources/assets/imgs/trainee.png");
    gui->menu[9] = png_load("ressources/assets/imgs/recruit.png");
    gui->menu[10] = png_load("ressources/assets/imgs/pirate.png");
    gui->menu[12] = png_load("ressources/assets/texture/balle.png");
    gui->menu[13] = png_load("ressources/assets/texture/tdm2.png");
    gui->menu[14] = png_load("ressources/assets/texture/press_key.png");
}