#include "philosophers_bonus.h"

size_t  ft_strlen(const char *str)
{
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}
char	*ft_strdup(const char *s)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc((ft_strlen(s) + 1));
	if (p == NULL)
		return (p);
	while (i < ft_strlen(s) + 1)
	{
		*(p + i) = s[i];
		i++;
	}
	return (p);
}

static size_t	ft_countnbr(int n)
{
	size_t	len;

	len = 0;
	if (n >= 0 && n <= 9)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	lennb;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	lennb = ft_countnbr(n);
	p = malloc(lennb + 1);
	if (p == NULL)
		return (NULL);
	if (n < 0)
	{
		p[0] = '-';
		n *= -1;
	}
	p[lennb] = '\0';
	while (n > 0)
	{
		p[--lennb] = n % 10 + 48;
		n /= 10;
	}
	return (p);
}

static void	ft_len(char const *s1, char const *s2, size_t *lens1, size_t *lens2)
{
	*lens1 = ft_strlen(s1);
	*lens2 = ft_strlen(s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	lens1;
	size_t	lens2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	ft_len(s1, s2, &lens1, &lens2);
	p = malloc(lens1 + lens2 + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		p[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < lens2)
	{
		p[i + lens1] = s2[i];
		i++;
	}
	p[i + lens1] = '\0';
	return (p);
}

char *generate_namesem(int index)
{
    char *num;
    char *name;

    num = ft_itoa(index);
    if (!num)
        return (num);

    name = ft_strjoin(SEM_MEAL, num);
    free(num);
    return (name);
}
