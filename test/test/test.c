/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gphilipp <gphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:29:00 by gphilipp          #+#    #+#             */
/*   Updated: 2023/06/04 20:56:29 by gphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main() {
	char				*str = NULL;
	char				cp[] = "Hello world!";
	int					i = -1;

	str = malloc(126);
	str = realloc(str, 129);
	while (++i < 12) {
		str[i] = cp[i];
	}
	free(str);

	printf("%s\n", str);

	//realloc(malloc(3450), 3650);
	show_alloc_mem();

	return (0);
}
