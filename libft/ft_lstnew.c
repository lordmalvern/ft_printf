/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 21:53:49 by bpuschel          #+#    #+#             */
/*   Updated: 2016/11/16 22:47:07 by bpuschel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*head;

	head = ft_memalloc(sizeof(*head));
	if (head == NULL)
		return (NULL);
	head->content = ft_memalloc(content_size * sizeof(content));
	if (content == NULL || head->content == NULL)
	{
		head->content = NULL;
		head->content_size = 0;
	}
	else
	{
		ft_memcpy(head->content, content, content_size);
		head->content_size = content_size;
	}
	head->next = NULL;
	return (head);
}
