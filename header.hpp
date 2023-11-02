/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:23:54 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 00:59:15 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>

const std::string WHITESPACE = " \n\r\t\f\v";

class header_req{
    private:
    std::string method;
    std::string path;
    std::string version;
    std::string User_agent;
    std::string accept;
    std::string host;
    std::string connection;
    std::string accept_encoding;
    std::string transfer_encoding;
    std::string content_type;
    std::string all_header;
    std::string extention;
    std::string type;
    std::string bound;
    std::string folder_upload; 
    std::string full_path;
    std::string atindex;
    std::string cookie;
    std::string query;
    bool    length;
    bool    encoding;
    bool    _type;
    bool    _bound;
    bool    bool_meth;
    int     content_length;
    int     fd_body;
    int     body_size;
    bool    bound_done;
    public:
    header_req();
    header_req(header_req const &o);
    header_req const &operator=(header_req const &o);
    ~header_req();
    void    set_method(std::string l);
    void    set_path(std::string l);
    void    set_version(std::string l);
    void    set_User_agent(std::string l);
    void    set_accept(std::string l);
    void    set_host(std::string l);
    void    set_connection(std::string l);
    void    set_accept_encoding(std::string l);
    void    set_content_length(int l);
    void    set_content_type(std::string l);
    void    set_extention(std::string l);
    void    set_type(std::string l);
    void    set_cookie(std::string const &l);
    void    set_fd(int fd);
    void    set_all_header(std::string l);
    void    set_transfer_encoding(std::string t);
    void    set_bool_encoding(void);
    void    set_bool_length(void);
    void    set_bool_type(void);
    void    set_bound(std::string l);
    void    set_bool_bound(void);
    void    set_folder_upload(std::string const &l);
    void    set_full_path(std::string const &f);
    void    set_atindex(std::string const &a);
    void    set_bool_meth(bool t);
    void    set_body_size(int l);
    void    set_bool_bound_done();
    void    set_query(std::string l);
    int     const &get_content_length() const;
    int     const &get_fd() const;
    int     get_body_size() const;
    bool    get_bool_encoding() const;
    bool    get_bool_length() const;
    bool    get_bool_type() const;
    bool    get_bool_bound() const;
    bool    get_bool_meth() const;
    bool    const &get_bound_done() const;
    bool    check_uri_char() const;
    std::string const &get_method() const;
    std::string const &get_path() const;
    std::string const &get_version() const;
    std::string const &get_User_agent() const;
    std::string const &get_accept() const;
    std::string const &get_host() const;
    std::string const &get_connection() const;
    std::string const &get_accept_encoding() const;
    std::string const &get_content_type() const;
    std::string const &get_extention() const;
    std::string const &get_type() const;
    std::string const &get_all_header() const;
    std::string const &get_transfer_encoding() const;
    std::string const &get_folder_upload() const;
    std::string const &get_bound() const;
    std::string const &get_full_path() const;
    std::string const &get_atindex() const;
    std::string const &get_cookie() const;
    std::string const &get_query() const;
};

std::string ltrim(const std::string &s);
std::string rtrim(const std::string &s);
std::string trim(const std::string &s);

#endif