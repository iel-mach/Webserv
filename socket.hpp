/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:29:10 by iel-mach          #+#    #+#             */
/*   Updated: 2023/04/16 12:34:51 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "servdata.hpp"

class _socket
{
    private:
        fd_set w_set;
        fd_set r_set;
        fd_set master_r;
        fd_set master_w;
        int max_fds;
        std::map<int, int> arr;
        std::map<int, Servdata> serv_fds;
    public:
        _socket();
        ~_socket();
        void    erase_serv_fd(int fd);
        void    set_w(int fd);
        void    set_r(int fd);
        void    set_masters();
        void    set_max_fds(int fd);
        void    set_arr_zero(int fd);
        void    set_arr_one(int fd);
        void    clear_fd_r(int fd);
        void    clear_fd_w(int fd);
        void    clear_fd_m_r(int fd);
        void    clear_fd_m_w(int fd);
        void    set_serv_fds(int key, Servdata value);
        int selec();
        int fd_iset(int fd, std::string s);
        int const &get_max_fds() const;
        int const &get_arr(int fd);
        std::map<int, Servdata> get_serv_fds() const;
};



#endif