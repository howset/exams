#include "ft_list.h"

int ft_list_size(t_list *begin_list)
{
    int i = 0;
    
    while (begin_list->next)
    {
        begin_list = begin_list->next;
        i++;
    }
    return (i);
}