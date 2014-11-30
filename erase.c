#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

void	aff(char *s)
{
	while (*s && write(2, s++, 1))
		;
}

char		*ft_itoa(int n)
{
	char 	*ret;
	char	rev[25];
	int	i;
	int	j;
	int	jt;
	int	nt;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		rev[0] = '-';
		i++;
	}
	while (n >= 0)
	{
		nt = n;
		j = 0;
		while (nt >= 10)
		{
			nt = nt / 10;
			j++;
		}
		rev[i] = nt + '0';
		i++;
		jt = j;
		while (j > 0)
		{
			rev[i + j - 1] = '0';
			nt = nt * 10;
			j--;
		}
		if (n >= 10)
			n -= nt;
		if (n < 10)
		{
			rev[i + jt - 1] = n + '0';
			n = -1;
		}
		rev[i + jt] = '\0';
	}
	ret = strdup(rev);
	return (ret);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		aff("Aborting SIGINT");
		exit(0);
	}
	signal(sig, SIG_IGN);
}

int	main(int ac, char **av)
{
	int		size;
	int		tmp;
	int		ret;
	int		pass;
	int		tpass;
	int		fd;
	int		dot;
	char		err[4];
	char		*erase;
	int		rdom;
	struct stat	file;

	err[0] = 8;
	err[1] = 8;
	err[2] = 8;
	err[3] = 0;
	signal(SIGINT, sig_handler);
	if (ac < 2)
	{
		aff("Use : ");
		aff(av[0]);
		aff(" file_to_erase [number of pass [buff size]]\n");
		return (1);
	}
	fd = open(av[1], O_WRONLY);
	if (fd <= 0)
	{
		aff("Error with file : ");
		aff(av[1]);
		aff("\n");
		return (2);
	}
	fstat(fd, &file);
	if (ac > 2)
	{
		pass = atoi(av[2]);
		if (pass < 1)
		{
			aff("Error 2nd argument should be at least 1\n");
			return (3);
		}
		if (ac > 3)
		{
			size = atoi(av[3]);
			if (size < 1)
			{
				aff("Error 3nd argument should be at least 1\n");
				return (4);
			}
		}
		else
			size = 512;
	}
	else
	{
		pass = 3;
		size = 512;
	}
	tpass = 1;
	erase = (char *) malloc(sizeof(char) * (size + 1));
	if (erase == NULL)
	{
		aff("Error, couldn't malloc");
		return (5);
	}
	rdom = open("/dev/urandom", O_RDONLY);
	if (rdom < 0)
	{
		aff("Error opening /dev/urandom\n");
		return (6);
	}
	while (tpass <= pass)
	{
		tmp = 0;
		dot = 0;
		ret = 1;
		while (tmp < file.st_size || (file.st_size == 0 && ret > 0))
		{
			if (tpass == pass)
				bzero(erase, size);
			else
				ret = read(rdom, erase, size);
			ret = pwrite(fd, erase, size, tmp);
			tmp += ret;
			if (file.st_size > 0)
			{
				aff(err);
				aff("   ");
				aff(err);
				aff(ft_itoa((float)((float)tmp / (float)file.st_size) * 100));
				aff("\%");
			}
			else
			{
				if (dot == 1000)
				{
					aff(err);
					aff(err);
					aff(err);
					aff("         ");
					aff(err);
					aff(err);
					aff(err);
					dot = 0;
				}
				if (!(dot % 100))
					aff(".");
				dot++;
			}
		}
		aff("\n");
		aff(ft_itoa((float)((float)tpass / (float)pass) * 100));
		aff("\% Done\n");
		tpass++;
	}
	close(fd);
	close(rdom);
	free(erase);
	return (0);
}
