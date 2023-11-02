/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:19:28 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/12 16:11:45 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <sys/stat.h>
#include "Locationdata.hpp"
#include "request.hpp"
#include "cgi.hpp"
#include <dirent.h>

class request;
class Servdata;

class response
{
    private:
        std::string headers;
        std::map<std::string, std::string> res_status;
        std::map<std::string, std::string> error_filename;
        std::string content_type;
        long content_length;
        std::string status;
        std::string extension_get;
        std::string body;
        bool    bool_head_done;
        bool    bool_body_done;
        bool    is_file;
        bool    is_file_delete;
        bool    bool_default;
        std::string    new_file;
        std::string  path_before_redirect;
        bool    support_cgi;
        int size_php_h;
        bool    cgi_true;
        bool    bool_redec;
    public:
        int     cgi_tmp_fd;
        std::string cgi_tmp_name;
        char stok_content_cgi[1024];
        std::string header_php;
        bool first_cgi;
        response();
        ~response();
        std::string const &set_headers(request &r, Cgi *cgi, Servdata *serv);
        std::string const &get_headers() const;
        void    set_res_status(request &r, std::string path_error);
        std::map<std::string, std::string> const &get_res_status() const;
        void    set_content_type(std::string s);
        std::string const &get_content_type() const;
        void    set_content_length(long t);
        void    set_extension_get();
        void    set_bool_redec(std::string l);
        long  const &get_content_lenght() const;
        void    check_error(Servdata *serv);
        void    set_new_file(std::string f_path);
        void    set_first_cgi(std::string l);
        void    set_error_filename();
        void    set_path_before(std::string l);
        void    set_cgi_true(std::string l);
        std::string const &get_path_before() const;
        long    const &get_content_length() const;
        void    set_status(std::string stat);
        void    set_bool_head_done(std::string l);
        void    set_bool_body_done(std::string l);
        void    set_bool_default(std::string l);
        void    set_bool_is_file(std::string l);
        void    set_support_cgi(std::string l);
        bool    get_bool_is_file();
        void    set_bool_is_file_del(std::string l);
        bool    get_bool_is_file_del();
        std::string const &get_status() const;
        void    file_size(std::string f);
        std::string const &get_new_file() const;
        bool const &get_bool_head_done() const;
        bool const &get_bool_body_done() const;
        bool const &get_bool_defaul() const;
        bool const &get_support_cgi() const;
        std::string get_fd_res() const;
        std::string get_res_status_() const;
        bool get_first_cgi();
        bool    const &get_bool_redec() const;
        bool    const &get_cgi_true() const;
        void    ft_delete(std::string full_path);
        void    ft_get(Servdata *serv);
        void    exetention_cgi(std::string path_cgi);
        void    content_type_from_php(std::string s);
        void    set_size_php_h(int l);
        int get_size_php_h() const;
};

std::string int_to_string(long f_size);

#endif