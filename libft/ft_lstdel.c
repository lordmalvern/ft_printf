/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 22:13:13 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/13 17:12:15 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *to_free;

	while (*alst)
	{
		del((*alst)->content, (*alst)->content_size);
		to_free = *alst;
		*alst = (*alst)->next;
		free(to_free);
	}
	alst = NULL;
}
