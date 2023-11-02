/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:26:38 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 00:23:04 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.hpp"

header_req::header_req()
{
    this->method = "";
    this->path = "";
    this->version = "";
    this->User_agent = "";
    this->accept = "";
    this->host = "";
    this->connection = "";
    this->accept_encoding = "";
    this->content_length = 0;
    this->content_type = "";
    this->all_header = "";
    this->extention = "";
    this->type = "";
    this->transfer_encoding = "";
    this->bound = "";
    this->fd_body = 0;
    this->length = false;
    this->encoding = false;
    this->_type = false;
    this->_bound = false;
    this->folder_upload = "";
    this->full_path = "";
    this->atindex = "";
    this->body_size = 0;
    this->bool_meth = false;
    this->bound_done = false;
}

header_req::header_req(const header_req &o)
{
    *this = o;
}

header_req const &header_req::operator=(const header_req &o)
{
    this->method = o.method;
    this->path = o.path;
    this->version = o.version;
    this->User_agent = o.User_agent;
    this->accept = o.accept;
    this->host = o.host;
    this->connection = o.connection;
    this->accept_encoding = o.accept_encoding;
    this->content_length = o.content_length;
    this->content_type = o.content_type;
    this->all_header = o.all_header;
    this->extention = o.extention;
    this->type = o.type;
    this->fd_body = o.fd_body;
    this->transfer_encoding = o.transfer_encoding;
    this->length = o.length;
    this->encoding = o.encoding;
    this->_type = o._type;
    this->bound = o.bound;
    this->_bound = o._bound;
    this->folder_upload = o.folder_upload;
    this->full_path = o.full_path;
    this->atindex = o.atindex;
    this->body_size = o.body_size;
    this->bool_meth = o.bool_meth;
    return *this;
}

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string &s) {
    return rtrim(ltrim(s));
}

header_req::~header_req() {}

void header_req::set_method(std::string l)
{
    this->method = l;
}

void header_req::set_path(std::string l)
{
    this->path = l;
}

void header_req::set_version(std::string l)
{
    this->version = l;
}

void header_req::set_User_agent(std::string l)
{
    this->User_agent =l;
}

void header_req::set_accept(std::string l)
{
    this->accept = l;
}

void header_req::set_host(std::string l)
{
    this->host = l;
}

void header_req::set_connection(std::string l)
{
    this->connection = l;
}

void header_req::set_accept_encoding(std::string l)
{
    this->accept_encoding = l;
}

void header_req::set_content_length(int l)
{
    this->content_length = l;
}

void header_req::set_body_size(int l)
{
    this->body_size = l;
}

void header_req::set_content_type(std::string l)
{
    this->content_type = l;
}

void header_req::set_extention(std::string l)
{
    this->extention = l;
}

void header_req::set_type(std::string l)
{
    this->type = l;
}

void header_req::set_all_header(std::string l)
{
    this->all_header = l;
}

void header_req::set_fd(int fd)
{
    this->fd_body = fd;
}

void    header_req::set_transfer_encoding(std::string t)
{
    this->transfer_encoding = t;
}

void    header_req::set_bound(std::string t)
{
    this->bound = t;
}

void    header_req::set_folder_upload(std::string const &l)
{
    this->folder_upload = l;
}

void    header_req::set_full_path(std::string const &l)
{
    this->full_path = l;
}

void    header_req::set_cookie(std::string const &l)
{
    this->cookie = l;
}

void    header_req::set_atindex(std::string const &l)
{
    this->atindex = l;
}

void    header_req::set_query(std::string l)
{
    this->query = l;
}

void    header_req::set_bool_encoding(void)
{
    this->encoding = true;
}

void    header_req::set_bool_length(void)
{
    this->length = true;
}

void    header_req::set_bool_type(void)
{
    this->_type = true;
}

void    header_req::set_bool_bound(void)
{
    this->_bound = true;
}

void    header_req::set_bool_meth(bool t)
{
    this->bool_meth = t;
}

void    header_req::set_bool_bound_done()
{
    this->bound_done = true;
}



std::string const &header_req::get_method() const
{
    return(this->method);
}

std::string const &header_req::get_path() const
{
    return(this->path);
}

std::string const &header_req::get_version() const
{
    return(this->version);
}

std::string const &header_req::get_User_agent() const
{
    return(this->User_agent);
}

std::string const &header_req::get_accept() const
{
    return(this->accept);
}

std::string const &header_req::get_host() const
{
    return(this->host);
}

std::string const &header_req::get_connection() const
{
    return(this->connection);
}

std::string const &header_req::get_cookie() const
{
    return(this->cookie);
}

std::string const &header_req::get_query() const
{
    return this->query;
}

std::string const &header_req::get_accept_encoding() const
{
    return(this->accept_encoding);
}

int const &header_req::get_content_length() const
{
    return(this->content_length);
}

int header_req::get_body_size() const
{
    return(this->body_size);
}

std::string const &header_req::get_content_type() const
{
    return(this->content_type);
}

std::string const &header_req::get_extention() const
{
    return(this->extention);
}

std::string const &header_req::get_type() const
{
    return(this->type);
}

std::string const &header_req::get_all_header() const
{
    return(this->all_header);
}

std::string const &header_req::get_transfer_encoding() const
{
    return this->transfer_encoding;
}

std::string const &header_req::get_bound() const
{
    return this->bound;
}

std::string const &header_req::get_folder_upload() const
{
    return this->folder_upload;
}

std::string const &header_req::get_full_path() const
{
    return this->full_path;
}

std::string const &header_req::get_atindex() const
{
    return this->atindex;
}

bool header_req::get_bool_encoding() const
{
    return this->encoding;
}

bool header_req::get_bool_length() const
{
    return this->length;
}

bool    header_req::get_bool_type() const
{
    return this->_type;
}

bool    header_req::get_bool_bound() const
{
    return this->_bound;
}

bool    header_req::get_bool_meth() const
{
    return this->bool_meth;
}

bool const &header_req::get_bound_done() const
{
    return this->bound_done;
}

bool    header_req::check_uri_char() const
{
    std::string str_uri = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.-_~:/?#[]@!$&'()*+,;=%";
    for (std::size_t i = 0; i < this->path.length(); i++)
    {
        if (str_uri.find(this->path[i]) == std::string::npos)
            return false;
    }
    for(std::size_t i = 0; i < this->path.length(); i++)
    {
        if(path[i] == '%')
        {
            if(isxdigit(path[i + 1]))
            {
                return false;
            }
        }
    }
    return true;
}