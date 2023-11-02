/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:58:18 by iel-mach          #+#    #+#             */
/*   Updated: 2023/04/16 12:42:00 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servdata.hpp"
#include "Locationdata.hpp"
#include "Utiles.hpp"
#include "socket.hpp"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		_socket sock;
		std::vector<std::vector<std::string> > r = ret_vector(av[1]);
		int s = count_server(r);
		std::vector<Servdata> servs = parsing(r, s);
		std::map<int, int> arr;
		int po[s];
		int i = 0;
		for (; i < s; i++)
		{
			po[i] = atoi(servs[i].get_port().c_str());
			int server_fd = create_socket(po[i]);
			sock.set_serv_fds(server_fd, servs[i]);
			sock.set_arr_zero(server_fd);
			sock.set_r(server_fd);
			if (server_fd > sock.get_max_fds())
				sock.set_max_fds(server_fd);
		}
		loop(sock);
	}
	else
	{
		std::cout << "Error: Bad argument." << std::endl;
		return (1);
	}
}