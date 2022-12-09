void replace_char(char *str, char src, char dst)
{
	while (*str) {
		if (*str == src)
			*str = dst;
		str++;
	}
}

int file_exist(const char *path)
{
	if (access(path, F_OK) == 0)
		return 1;
	else
		return 0;
}