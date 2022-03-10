
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
////////////////////////////////////////

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
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

static int	ft_sizechain(const char *s, char c)
{
	int	size;

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

	if (!s)
		return (NULL);
	result = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (result == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (k < ft_count(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		result[k] = malloc(sizeof(char) * (ft_sizechain(&s[i], c) + 1));
		// mempush(result[k], sizeof(char), ft_sizechain(&s[i], c) + 1);
		if (result[k] == NULL)
			return (ft_freesplit(result, k));
		ft_strlcpy(result[k++], &s[i], ft_sizechain(&s[i], c) + 1);
		i += ft_sizechain(&s[i], c);
	}
	result[ft_count(s, c)] = NULL;
	return (result);
}

#include <stdio.h>

int	main()
{
	char	str[100] = "hello \"|\"";
	char	**splitline;
	int		i;

	splitline = ft_split(str, '|');
	i = 0;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}