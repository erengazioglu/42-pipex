/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egaziogl <egaziogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 03:15:02 by egaziogl          #+#    #+#             */
/*   Updated: 2026/01/23 13:48:24 by egaziogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	if (lst->next && lst->prev)
	{
		lst->prev->next = lst->next;
		lst->next->prev = lst->prev;
	}
	else if (lst->next)
		lst->next->prev = NULL;
	else if (lst->prev)
		lst->prev->next = NULL;
	free(lst);
}
