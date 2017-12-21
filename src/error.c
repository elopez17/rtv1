#include <rtv1.h>

void	rtv1_error(int code)
{
	static char	*msg[] = {
		"invalid amount of arguements",
		"could not open file",
		"invalid file"
	};

	ft_printf("%{RD}RTv1: %s%{NC}\nusage: %{rd}./RTv1%{nc} \
%{TQ}scenes/%{nc}[file]\n", msg[code]);
	exit(0);
}
