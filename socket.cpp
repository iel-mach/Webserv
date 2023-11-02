/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 00:28:57 by iel-mach          #+#    #+#             */
/*   Updated: 2023/04/16 12:35:09 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.hpp"

_socket::_socket()
{
    FD_ZERO(&this->master_r);
	FD_ZERO(&this->master_w);
	FD_ZERO(&this->w_set);
	FD_ZERO(&this->r_set);
    this->max_fds = 0;
}

_socket::~_socket()
{
}

void    _socket::erase_serv_fd(int fd)
{
    this->serv_fds.erase(fd);
}

void    _socket::set_w(int fd)
{
     FD_SET(fd, &this->w_set);
}

void    _socket::set_r(int fd)
{
    FD_SET(fd, &this->r_set);
}

void    _socket::set_masters()
{
    this->master_w = this->w_set;
	this->master_r = this->r_set;
}

void    _socket::set_max_fds(int fd)
{
    this->max_fds = fd;
}

void    _socket::set_arr_zero(int fd)
{
    this->arr[fd] = 0;
}

void    _socket::clear_fd_r(int fd)
{
    FD_CLR(fd, &this->r_set);
}

void    _socket::clear_fd_w(int fd)
{
    FD_CLR(fd, &this->w_set);
}

int _socket::selec()
{
    int d = select(this->max_fds + 1, &this->master_r, &this->master_w, NULL, NULL);
    return d;
}

int _socket::fd_iset(int fd, std::string s)
{
    if(!s.compare("read"))
    {
        if(FD_ISSET(fd, &this->master_r))
            return 1;
        return 0;
    }
    else  if(!s.compare("write"))
    {
        if(FD_ISSET(fd, &this->master_w))
            return 1;
        return 0;
    }
    return 0;
}

void    _socket::set_serv_fds(int key, Servdata value)
{
    this->serv_fds.insert(std::pair<int, Servdata> (key, value));
}

int const &_socket::get_arr(int fd)
{
    return this->arr[fd];
}

int const &_socket::get_max_fds() const
{
    return this->max_fds;
}

void    _socket::set_arr_one(int fd)
{
    this->arr[fd] = 1;
}

std::map<int, Servdata> _socket::get_serv_fds() const
{
    return this->serv_fds;
}

void    _socket::clear_fd_m_r(int fd)
{
    FD_CLR(fd, &this->master_r);
}
void    _socket::clear_fd_m_w(int fd)
{
    FD_CLR(fd, &this->master_w);
}