bool    ft_isin(const char &c, const char *str) {
	for (; *str; ++str)
		if (*str == c)
			return (true);
	return (false);
}
