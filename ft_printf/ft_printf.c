/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 11:18:42 by yfu               #+#    #+#             */
/*   Updated: 2021/01/29 12:22:48 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

typedef struct	s_form
{
	int	width;
	int	precision;
}				t_form;

int				ft_printf(const char *, ...);

void			ft_putchar(char c, int *cnt)
{
	(*cnt)++;
	write(1, &c, 1);
}

int				ft_atoi(char **str)
{
	int	ans;

	ans = 0;
	while (**str <= '9' && **str >= '0')
	{
		ans = 10 * ans + **str - '0';
		(*str)++;
	}
	return (ans);
}

int				ft_strlen(char *s)
{
	int	cnt;

	if (!s)
		return (0);
	cnt = 0;
	while (*(s++))
		cnt++;
	return (cnt);
}

void			ft_putstr(char *s, int *cnt)
{
	int	len;

	len = ft_strlen(s);
	write(1, s, len);
	(*cnt) += len;
}

void			ft_itoa_sub(long long num, const char *base,
							long long base_len, char **ans)
{
	if (num >= base_len)
		ft_itoa_sub(num / base_len, base, base_len, ans);
	**ans = base[(int)(num % base_len)];
	(*ans)++;
}

char			*ft_itoa_base(long long num, const char *base,
										long long base_len)
{
	char		*re;
	char		*ans;
	long long	num2;
	int			len;

	if (num < 0LL)
		num *= -1LL;
	num2 = num;
	len = 1;
	while (num2 >= base_len)
	{
		len++;
		num2 /= base_len;
	}
	if (!(ans = (char*)malloc((len + 1) * sizeof(char))))
		return (NULL);
	re = ans;
	ft_itoa_sub(num, base, base_len, &ans);
	*ans = '\0';
	return (re);
}

int				ft_max(int a, int b)
{
	return (a > b ? a : b);
}

int				ft_min(int a, int b)
{
	return (a < b ? a : b);
}

void			ft_d(va_list *arg, int *cnt, t_form *form)
{
	long long	num;
	char		*str;
	int			len;

	str = 0;
	num = (long long)va_arg(*arg, int);
	if (num == 0LL && form->precision == 0)
		while ((form->width)-- > 0)
			ft_putchar(' ', cnt);
	else
	{
		str = ft_itoa_base(num, "0123456789", 10LL);
		len = ft_strlen(str);
		form->precision = ft_max(0, form->precision - len);
		form->width = ft_max(0, form->width -
				form->precision - len - (num < 0LL ? 1 : 0));
		while ((form->width)-- > 0)
			ft_putchar(' ', cnt);
		if (num < 0LL)
			ft_putchar('-', cnt);
		while ((form->precision)-- > 0)
			ft_putchar('0', cnt);
		ft_putstr(str, cnt);
		free(str);
	}
}

void			ft_s(va_list *arg, int *cnt, t_form *form)
{
	int		len;
	char	*s;

	s = va_arg(*arg, char*);
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (form->precision == -1)
		form->precision = len;
	form->precision = ft_min(form->precision, len);
	form->width = ft_max(0, form->width - form->precision);
	while ((form->width)-- > 0)
		ft_putchar(' ', cnt);
	while ((form->precision)-- > 0)
		ft_putchar(*(s++), cnt);
}

void			ft_x(va_list *arg, int *cnt, t_form *form)
{
	char		*str;
	long long	num;
	int			len;

	num = (long long)va_arg(*arg, unsigned);
	str = 0;
	if (num == 0LL && form->precision == 0)
		while ((form->width)-- > 0)
			ft_putchar(' ', cnt);
	else
	{
		str = ft_itoa_base(num, "0123456789abcdef", 16LL);
		len = ft_strlen(str);
		form->precision = ft_max(0, form->precision - len);
		form->width = ft_max(0, form->width - form->precision - len);
		while ((form->width)-- > 0)
			ft_putchar(' ', cnt);
		while ((form->precision)-- > 0)
			ft_putchar('0', cnt);
		ft_putstr(str, cnt);
	}
	free(str);
}

void			ft_parse(char **str, va_list *arg, int *cnt)
{
	t_form	form;

	form.width = ft_atoi(str);
	if (**str == '.')
	{
		(*str)++;
		form.precision = ft_atoi(str);
	}
	else
		form.precision = -1;
	if (**str == 'd')
		ft_d(arg, cnt, &form);
	else if (**str == 's')
		ft_s(arg, cnt, &form);
	else if (**str == 'x')
		ft_x(arg, cnt, &form);
	(*str)++;
}

int				ft_printf(const char *str, ...)
{
	char	*ptr;
	va_list	arg;
	int		cnt;

	ptr = (char*)str;
	va_start(arg, str);
	cnt = 0;
	while (*ptr)
	{
		if (*ptr == '%')
		{
			ptr++;
			ft_parse(&ptr, &arg, &cnt);
		}
		else
			ft_putchar(*(ptr++), &cnt);
	}
	va_end(arg);
	return (cnt);
}
