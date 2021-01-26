#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int     ft_printf(const char *, ...);

typedef struct  s_form
{
    int     width;
    int     precision;
}               t_form;

void    ft_putchar(char c, int *cnt)
{
    write(1, &c, 1);
    (*cnt)++;
}

void    ft_putstr(char *str, int *cnt)
{
    if (!str)
    {
        ft_printf("ERROR_IN_PUTSTR\n");
        return ;
    }
    while (*str)
        ft_putchar(*(str++), cnt);
}

int     ft_atoi(char **str)
{
    int ans;

    if (!str || !(*str))
    {
        ft_printf("ERROR_IN_ATOI\n");
        return (-1);
    }
    ans = 0;
    while (**str)
    {
        if (**str < '0' || **str > '9')
            break ;
        ans = 10 * ans + **str - '0';
        (*str)++;
    }
    return (ans);
}

void    ft_assign(char **ans, const char *base, long long num, int base_len)
{
    if (num >= base_len)
        ft_assign(ans, base, num / base_len, base_len);
    **ans = base[(int)(num % base_len)];
    (*ans)++;
}

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
}

int     ft_strlen(char *s)
{
    return (*s ? 1 + ft_strlen(s + 1) : 0);
}

int     ft_max(int a, int b)
{
    return (a > b ? a : b);
}

int     ft_min(int a, int b)
{
    return (a < b ? a : b);
}

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
}

void    ft_str(va_list *arg, t_form *form, int *cnt)
{
    char    *str;

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
}

void    ft_parse(char **pos, va_list *arg, int *cnt)
{
    char    *str;
    t_form  form;

    str = *pos;
    form.width = ft_atoi(&str);
    if (*str == '.')
    {
        str++;
        form.precision = ft_atoi(&str);
    }
    else
        form.precision = -1;
    if (*str == 'd')
        ft_int(arg, &form, cnt);
    else if (*str == 's')
        ft_str(arg, &form, cnt);
    else
        ft_x(arg, &form, cnt);
    str++;
    *pos = str;
}

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
}
*/
