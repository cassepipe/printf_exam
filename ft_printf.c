#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

size_t ft_strlen(const char *s)
{
	int len = 0;
	if (s)
	{
		while (*s)
		{
			len++;
			s++;
		}
	}
	return (len);
}

char *int_repr(int n, char *buffer, size_t buffsize, const char *base_str)
{
	long nb = n;
	int neg = 0;
	int i = buffsize - 1;
	size_t base = ft_strlen(base_str);

	if (n < 0)
	{
		neg = 1;
		nb = -1 * nb;
	}
	buffer[i] = 0;
	while (1)
	{
		i--;
		buffer[i] = base_str[nb % base];
		nb = nb / base;
		if (nb == 0)
			break;
	}
	if (neg)
	{
		i--;
		buffer[i] = '-';
	}
	return (&buffer[i]);
}

char *uint_repr(unsigned int n, char *buffer, size_t buffsize, const char *base_str)
{
	unsigned long nb = n;
	int i = buffsize - 1;
	size_t base = ft_strlen(base_str);

	buffer[i] = 0;
	while (1)
	{
		i--;
		buffer[i] = base_str[nb % base];
		nb = nb / base;
		if (nb == 0)
			break;
	}
	return (&buffer[i]);
}


int write_format(const char *str, va_list ap)
{
	size_t written = 0;
	char *charstr;
	char *nbstr;
	char buffer[256];

	if (*str && *str == '%')
		str++;
	if (*str && *str == 's')
	{
		charstr = va_arg(ap, char*);
		if (charstr)
			written = write(STDOUT_FILENO, charstr, ft_strlen(charstr));
		else
			written = write(STDOUT_FILENO, "(null)", sizeof("(null)") - 1);
	}
	else if (*str && *str == 'd')
	{
		nbstr = int_repr(va_arg(ap, int), buffer, sizeof(buffer), "0123456789");
		written = write(STDOUT_FILENO, nbstr, ft_strlen(nbstr));
	}
	else if (*str && *str == 'x')
	{
		nbstr = uint_repr(va_arg(ap, int), buffer, sizeof(buffer), "0123456789abcdef");
		written = write(STDOUT_FILENO, nbstr, ft_strlen(nbstr));
	}
	else if (*str)
	{
		write(STDOUT_FILENO, "%", 1);
		written = 1;
	}

	return (written);
}


static int	ft_vprintf(const char* str, va_list ap)
{
	size_t total_written= 0;
	const char *behind;


	while (*str)
	{
		behind = str;
		while (*str && *str != '%')
			str++;
		total_written += write(STDOUT_FILENO, behind, str - behind);
		total_written += write_format(str, ap);
		if (*str && *str == '%')
			str++;
		if (*str && (*str == 'd' || *str == 'x' || *str == 's'))
			str++;
	}
	return (total_written);
}

int ft_printf(const char* str, ...)
{
	va_list ap;
	size_t ret;

	va_start(ap, str);
	ret = ft_vprintf(str, ap);
	va_end(ap);

	return (ret);
}

#include <limits.h>
int main(void)
{
	   printf("This is a long %     \n", 1);
	ft_printf("This is a long %     \n", 1);


	   printf("This is a long %%     \n", 1);
	ft_printf("This is a long %%     \n", 1);

	   printf("This is a long %s     \n", "liiiiine");
	ft_printf("This is a long %s     \n", "liiiiine");

	   printf("This is a long %s     \n", (char*)NULL);
	ft_printf("This is a long %s     \n", NULL);

	   printf("This is a positive nb %d     \n", INT_MAX);
	ft_printf("This is a positive nb %d     \n", INT_MAX);

	   printf("This is a negative nb %d     \n", INT_MIN);
	ft_printf("This is a negative nb %d     \n", INT_MIN);

	   printf("This is int min as hex %x     \n", INT_MIN);
	ft_printf("This is int min as hex %x     \n", INT_MIN);

	   printf("This is int max as hex %x     \n", INT_MAX);
	ft_printf("This is int max as hex %x     \n", INT_MAX);
}
