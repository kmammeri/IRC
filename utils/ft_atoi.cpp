#include <cctype>

using namespace std;

int	ft_atoi(const char *str)
{
	long	ret;
	int		i;
	int		signe;

	signe = 1;
	ret = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
	}
	while (str[i] && isdigit(str[i]) == 1)
	{
		ret = ret * 10 + str[i] - 48;
		if (ret > 2147483648 && signe == -1)
			return (0);
		if (ret > 2147483647 && signe == 1)
			return (-1);
		i++;
	}
	return (ret * signe);
}