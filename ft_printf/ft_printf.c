/*
 * start from 02 : 15
 * */

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct	s_form
{
	int	width;
	int	precision;
}		t_form;

void	ft_init_form(t_form	*form)
{
	form->width = 0;
	form->precision = -1;
}
int	ft_printf(const char *, ...);

int	ft_strlen(char *s)
{
	int	ans;

	ans = 0;
	while (*(s++))
		ans++;
	return (ans);
}

void	ft_putchar(char c, int *cnt)
{
	write(1, &c, 1);
	(*cnt)++;
}

<<<<<<< HEAD
void	ft_putstr(char *s, int *cnt)
{
	int	len;

	len = ft_strlen(s);
	write(1, s, len);
	(*cnt) += len;
=======
char    *ft_itoa_base(long long num, const char *base, long long base_len, t_form *form)
{
    int         len;
    long long   num2;
    char        *ans;
    char        *re;

	if (form->precision == 0 && num == 0LL)
	{
		ans = (char*)malloc(1 * sizeof(char));
		*ans = 0;
		return (ans);
	}
    num2 = num;
    len = (num < 0LL ? 2 : 1);
    num = (num < 0LL ? num * -1LL : num);
    while (num >= base_len)
    {
        len++;
        num /= base_len;
    }
    ans = (char*)malloc((len + 1) * sizeof(char));
    re = ans;
    if (num2 < 0LL)
        *(ans++) = '-';
    num2 = (num2 < 0LL ? num2 * -1LL : num2);
    ft_assign(&ans, base, num2, base_len);
    *ans = '\0';
    return (re);
>>>>>>> 101aa175a32e3f595c3888ffa4ebfdd919758b01
}

int	ft_atoi(char **str)
{
	int	ans;

	ans = 0;
	while (**str >= '0' && **str <= '9')
	{
		ans = 10 * ans + *(*str)++ - '0';
	}
	return (ans);
}

int	ft_max(int a, int b)
{
	return (a > b ? a : b);
}

void	ft_itoa_base_sub(unsigned num, char *base, unsigned base_len, char **ans)
{
	if (num >= base_len)
		ft_itoa_base_sub(num / base_len, base, base_len, ans);
	*(*ans)++ = base[num % base_len];
}

<<<<<<< HEAD
char	*ft_itoa_base(unsigned num, char *base, unsigned base_len)
{
	char		*ans;
	char		*re;
	int		len;
	long long	num2;

	len = 1;
	num2 = num;
	while (num2 >= base_len)
	{
		len++;
		num2 /= base_len;
	}
	ans = (char*)malloc((len + 1) * sizeof(char));
	re = ans;
	ft_itoa_base_sub(num, base, base_len, &ans);
	*ans = '\0';
	return (re);
=======
void    ft_int(va_list *arg, t_form *form, int *cnt)
{
    char    *str;
    int     neg;
    int     len;

    str = ft_itoa_base((long long)va_arg(*arg, int), "0123456789", 10LL, form);
	len = ft_strlen(str);
    if (str[0] == '-')
        form->precision = ft_max(0, form->precision - len + 1);
    else
        form->precision = ft_max(0, form->precision - len);
    form->width = ft_max(0, form->width - form->precision - len);
    while ((form->width)-- > 0)
        ft_putchar(' ', cnt);
    if (str[0] == '-')
    {
        ft_putchar(*(str++), cnt);
        neg = 1;
    }
    else
        neg = 0;
    while ((form->precision)-- > 0)
        ft_putchar('0', cnt);
    ft_putstr(str, cnt);
    free(str - neg);
>>>>>>> 101aa175a32e3f595c3888ffa4ebfdd919758b01
}

int	ft_min(int a, int b)
{
	return (a < b ? a : b);
}

<<<<<<< HEAD
void	ft_s(va_list *arg, t_form *form, int *cnt)
{
	char	*str;
	int	len;
	int	ct;

	str = va_arg(*arg, char*);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (form->precision == -1)
		form->precision = len;
	form->precision = ft_min(form->precision, len);
	form->width = ft_max(0, form->width - form->precision);
	while ((form->width)-- > 0)
		ft_putchar(' ', cnt);
	ct = -1;
	while (++ct < form->precision)
		ft_putchar(str[ct], cnt);
}

void	ft_d(va_list *arg, t_form *form, int *cnt)
{
	int	num;
	int	sign;
	char	*str;

	num = va_arg(*arg, int);
	if (num == 0)
	{
		form->precision = (form->precision < 0 ? 1 : form->precision);
		while ((form->width)-- > form->precision)
			ft_putchar(' ', cnt);
		while (form->precision-- > 0)
			ft_putchar('0', cnt);
		return ;
	}
	sign = (num < 0 ? -1 : 1);
	if (num == -2147483648)
		str = ft_itoa_base(2147483648U, "0123456789", 10U);
	else
		str = ft_itoa_base((unsigned)(num * sign), "0123456789", 10U);
	form->precision = ft_max(form->precision - ft_strlen(str), 0);
	form->width -= form->precision + (sign - 1) / -2 + ft_strlen(str);
	while ((form->width)-- > 0)
		ft_putchar(' ', cnt);
	if (sign == -1)
		ft_putchar('-', cnt);
	while ((form->precision)-- > 0)
		ft_putchar('0', cnt);
	ft_putstr(str, cnt);
	free(str);
=======
	str = va_arg(*arg, char*);
	if (!str)
		str = "(null)";
    if (form->precision == -1)
        form->precision = ft_strlen(str);
    form->precision = ft_min(form->precision, ft_strlen(str));
    form->width = ft_max(0, form->width - form->precision);
    while ((form->width)-- > 0)
        ft_putchar(' ', cnt);
    while ((form->precision)-- > 0)
        ft_putchar((*str++), cnt);
}

void    ft_x(va_list *arg, t_form *form, int *cnt)
{
    char    *str;
    int     len;

    str = ft_itoa_base((long long)va_arg(*arg, unsigned), "0123456789abcdef", 16LL, form);
    len = ft_strlen(str);
    form->precision = ft_max(0, form->precision - len);
    form->width = ft_max(0, form->width - form->precision - len);
    while ((form->width)-- > 0)
        ft_putchar(' ', cnt);
    while ((form->precision)-- > 0)
        ft_putchar('0', cnt);
    ft_putstr(str, cnt);
    free(str);
>>>>>>> 101aa175a32e3f595c3888ffa4ebfdd919758b01
}


void	ft_x(va_list *arg, t_form *form, int *cnt)
{
	char		*str;
	unsigned	num;

	num = va_arg(*arg, unsigned);
	if (num == 0U)
	{
		form->precision = (form->precision < 0 ? 1 : form->precision);
		while ((form->width)-- > form->precision)
			ft_putchar(' ', cnt);
		while (form->precision-- > 0)
			ft_putchar('0', cnt);
		return ;
	}
	str = ft_itoa_base(num, "0123456789abcdef", 16U);
	form->precision = ft_max(form->precision - ft_strlen(str), 0);
	form->width -= form->precision + ft_strlen(str);
	while ((form->width)-- > 0)
		ft_putchar(' ', cnt);
	while ((form->precision)-- > 0)
		ft_putchar('0', cnt);
	ft_putstr(str, cnt);
	free(str);
}

<<<<<<< HEAD

void	ft_parse(va_list *arg, char **str, int *cnt)
{
	t_form	form;

	(*str)++;
	ft_init_form(&form);
	form.width = ft_atoi(str);
	if (**str == '.')
	{
		(*str)++;
		form.precision = ft_atoi(str);
	}
	if (**str == 's')
		ft_s(arg, &form, cnt);
	else if (**str == 'd')
		ft_d(arg, &form, cnt);
	else
		ft_x(arg, &form, cnt);
	(*str)++;
}

int	ft_printf(const char *str, ...)
{
	va_list	arg;
	char	*ptr;
	int	cnt;

	va_start(arg, str);
	ptr = (char*)str;
	cnt = 0;
	while (*ptr)
	{
		if (*ptr == '%')
			ft_parse(&arg, &ptr, &cnt);
		else
		{
			ft_putchar(*(ptr++), &cnt);
		}
	}
	va_end(arg);
	return (cnt);
}

int main()
{
	ft_printf("%10.4ss", NULL);
=======
int     ft_printf(const char *str, ...)
{
    va_list arg;
    char    *pos;
    int     cnt;

    va_start(arg, str);
    pos = (char*)str;
	if (!pos || !(*pos))
		return (0);
    cnt = 0;
    while (*pos)
    {
        if (*pos == '%')
        {
            pos++;
            ft_parse(&pos, &arg, &cnt);
        }
        else
            ft_putchar(*(pos++), &cnt);
    }
    va_end(arg);
    return (cnt);
}
/*
int		main()
{
	printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
	ft_printf("d0p %.0d %.0d %.0d %.0d %.0d %.0d %.0d %.0d\n", 0, 42, 1, 4554, 2147483647, (int)2147483648, (int)-2147483648, (int)-2147483649);
>>>>>>> 101aa175a32e3f595c3888ffa4ebfdd919758b01
}
*/
