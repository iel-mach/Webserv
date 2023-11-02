/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utiles.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:02 by iel-mach          #+#    #+#             */
/*   Updated: 2023/04/16 12:34:09 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILES_HPP
#define UTILES_HPP

#include "Locationdata.hpp"
#include "servdata.hpp"
#include "request.hpp"
#include "response.hpp"
#include <fstream> 
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include "socket.hpp"


std::vector<std::vector<std::string> >    ret_vector(const std::string &av);
std::string get_file(const std::string &av);
void    check_syntax(std::string const &lop);
std::vector<Servdata> parsing(std::vector<std::vector<std::string> > r, int s);
int count_server(std::vector<std::vector<std::string> > r);
int create_socket(int po);
void loop(_socket sock);

#endif