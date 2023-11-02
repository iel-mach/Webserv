/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servdata.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:04:24 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 01:00:35 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVDATA_HPP
#define SERVDATA_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include "Locationdata.hpp"
#include "request.hpp"
#include "response.hpp"
#include "cgi.hpp"
#include <fstream>

class response;
class request;

class Servdata {
    private:
        std::map <std::string, std::string> serv_cgi;
        std::map<std::string, Locationdata> serv_loc;
        std::string serv_name;
        std::string serv_port;
        std::string serv_host;
        std::string serv_limit;
        std::string serv_error;
        char buffer[1024];
        int valread;
        int fd_req;
        int fd_res;
        bool meth;
        bool bool_error;
        bool req_done;
        bool res_done;
        bool bool_fdres;
        request reqst;
        response respns;
        bool header_cgi;
        std::string ex;
        std::string query;
        Cgi cgi;
    public:
        int i;
        Servdata();
        ~Servdata();
        void    set_port(std::string const &p);
        void    set_name(std::string const &n);
        void    set_host(std::string const &h);
        void    set_limit(std::string const &l);
        void    set_error(std::string const &e);
        void    set_cgi(const std::string &key, const std::string &value);
        void    set_loc(const std::string &key, const Locationdata &value);
        void    set_fd_req(int fd);
        void    read_req();
        void    start_response();
        void    set_res_done();
        void    set_body_res();
        void    set_res_done_();
        void    check_meth_allow();
        void    set_meth();
        void    set_ex_php(std::string s);
        void    set_bool_header_cgi(std::string l);
        void    check_cgi();
        void    set_size_php_h(int l);
        std::string sup_cgi_conf(std::string l);
        std::map <std::string, Locationdata> get_loc() const;
        std::map <std::string, std::string>  const &get_cgi() const;
        std::string const &get_port() const;
        std::string const &get_name() const;
        std::string const &get_host() const;
        std::string const &get_limit() const;
        std::string const &get_error() const;
        std::string const &get_ex_php() const;
        int const &get_fd_req() const;
        bool const &get_bool_error() const;
        bool const &get_req_done() const;
        bool const &get_res_done() const;
        bool const &get_bool_fdres() const;
        bool const &get_meth() const;
        bool const &get_bool_header_cgi() const;
        request &get_request();
        response &get_res();
        
};


#endif