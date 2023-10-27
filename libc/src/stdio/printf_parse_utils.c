#include <printf.h>

t_ll pf_va_arg(t_flags f, va_list l) {
	t_ll n;
	if (f & MODIFIER_LL)
		n = va_arg(l, t_ll);
	else if (f & MODIFIER_L)
		n = va_arg(l, t_ll);
	else if (f & MODIFIER_HH)
		n = (int8_t)va_arg(l, int32_t);
	else if (f & MODIFIER_H)
		n = (int16_t)va_arg(l, int32_t);
	else
		n = va_arg(l, int32_t);
	return n;
}

t_ull pf_va_arg_unsigned(t_flags f, va_list l) {
	t_ull n;
	if (f & MODIFIER_LL)
		n = va_arg(l, t_ull);
	else if (f & MODIFIER_L)
		n = va_arg(l, t_ull);
	else if (f & MODIFIER_HH)
		n = (uint8_t)va_arg(l, uint32_t);
	else if (f & MODIFIER_H)
		n = (uint16_t)va_arg(l, uint32_t);
	else
		n = va_arg(l, uint32_t);
	return n;
}
