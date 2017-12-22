/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysalata <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:52:23 by ysalata           #+#    #+#             */
/*   Updated: 2016/12/05 14:42:44 by ysalata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list *ret;

	if (!(ret = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	ret->content_size = content ? content_size : 0;
	ret->content = NULL;
	ret->next = NULL;
	if (content && (ret->content = malloc(content_size)))
		ft_memcpy(ret->content, content, content_size);
	return (ret);
}
