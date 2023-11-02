/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:36:37 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 00:59:07 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
#define CGI_HPP

#include "request.hpp"

class response;
class Cgi{
    private:
        char **env;
        char **args;
        std::string ex;
        std::string path;
        std::map <std::string, std::string> map_cgi;
        std::string exec_script;
        std::string env_query;
        std::string save_query;
        std::string cgi_tmp_name;
        int fd_post;
        int cgi_tmp_fd;
        bool cgi_tmp_fd_bool;
        int pid;
    public:
    void    set_env(std::string port, request *req);
    void    cgi(std::string port, request *req, response *res);
    void    set_args(request *reqs, response *resps);
    void    set_map_cgi(std::map <std::string, std::string> serv_cgi);
    void    set_env_query(std::string l);
    void    set_cgi_tmp_name(std::string l);
    void    set_exec_script(std::string l);
    void sup_cgi_conf(std::string l);
    void    set_cgi_tmp_fd_bool(std::string l);
    std::string query_post();
    void        to_fork(request *req, response *res);
    std::string const   &get_cgi_tmp_name() const;
    std::string const   &get_env_query() const;
    std::string const   &get_ex() const;
    std::string const   &get_exec_script() const;
    int         const   &get_cgi_tmp_fd() const;
    bool    const &get_cgi_tmp_fd_bool() const;
};

#endif