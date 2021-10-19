void		**ft_realloc_tab(void **tab, int currsize, int newsize)
{
	int	i;

	i = 0;
    void **new_tab; 

    new_tab = malloc(newsize);
	while (i < currsize)
	{
		new_tab[i] = ft_strdup(tab[i],
				data->map_w, sizeof(char) * x + 1);
		i++;
	}
	return (new_tab);
}