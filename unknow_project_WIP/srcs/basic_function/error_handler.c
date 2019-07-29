#include "unknow_project.h"

void	error_exit(int error, char *message)
{
	ft_putstr("Error ");
	ft_putnbr(error);
	ft_putstr(" : ");
	ft_putstr(message);
	endl();
	exit(error);
}
