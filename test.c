#include <stddef.h>
#include <stdlib.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;

	i = 0;
	if (size > 0)
	{
		while (--size > 0 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i])
		i++;
	return (i);
}

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;
	int	quote;

	i = 0;
	count = 0;
	quote = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] == '"')
			quote++;
		if (s[i])
			count++;
		while ((quote % 2 == 0 && s[i] != c) || (quote % 2 == 1 && s[i] != '"') && s[i])
		{
			if (s[i] == '"')
				quote++;
			i++;
		}
	}
	if (quote % 2 == 1)
		return (-1);
	return (count - (quote / 2));
}

static char	**ft_freesplit(char **result, int k)
{
	while (k >= 0)
	{
		free(result[k]);
		k--;
	}
	return (NULL);
}

static int	ft_sizechain(const char *s, char c, int quote)
{
	int	size;

	if (quote % 2 == 1)
		c = '"';
	size = 0;
	while (*s != c && *s)
	{
		size++;
		s++;
	}
	return (size);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		k;
	int		quote;

// renvoyer erreur de comportement non defini quand renvoie NULL -> quand quote ouverte
	if (!s || ft_count(s, c) == -1)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	k = 0;
	i = 0;
	quote = 0;
	while (k < ft_count(s, c))
	{
		while (s[i] != '"' || s[i] == c && s[i])
			i++;
		if (s[i] == '"')
			quote++;
		result[k] = malloc(sizeof(char) * (ft_sizechain(&s[i], c, quote) + 1));
		if (result[k] == NULL)
			return (ft_freesplit(result, k));
		ft_strlcpy(result[k++], &s[i], ft_sizechain(&s[i], c, quote) + 1);
		i += ft_sizechain(&s[i], c, quote);
		if (quote % 2 == 1)
			quote++;
	}
	result[ft_count(s, c)] = NULL;
	return (result);
}

#include <stdio.h>

int	main()
{
	char	str[100] = "yo \"|\"";
	char	**split_line;
	int		i;

	split_line = ft_split(str, '|');
	i = 0;
	while (split_line[i])
	{
		printf("%d: %s\n", i, split_line[i]);
		i++;
	}
	return 0;
}