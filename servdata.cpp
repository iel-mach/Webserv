/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servdata.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:31:22 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 01:00:25 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "servdata.hpp"
#include "response.hpp"
#include <utility>


Servdata::Servdata()
{
    this->serv_name = "";
    this->serv_port = "";
    this->serv_host = "";
    this->serv_limit = "";
    this->serv_error = "";
    this->bool_error = false;
    this->req_done = false;
    this->res_done = false;
    this->meth = false;
    this->fd_res = 0;
    this->fd_req = -1;
    this->query = "";
    bzero(buffer, 1024);
    this->valread = 0;
}

Servdata::~Servdata()
{
    
}

void    Servdata::set_port(std::string const &p)
{
    this->serv_port = p;
}

void    Servdata::set_name(std::string const &n)
{
    this->serv_name = n;
}

void    Servdata::set_host(std::string const &h)
{
    this->serv_host = h;
}

void    Servdata::set_limit(std::string const &l)
{
    this->serv_limit = l;
}

void    Servdata::set_error(std::string const &e)
{
    this->serv_error = e;
}

void    Servdata::set_cgi(const std::string &key, const std::string &value)
{
        this->serv_cgi[key] = value;
}

void    Servdata::set_loc(const std::string &key, const Locationdata &value)
{
    this->serv_loc.insert(std::pair<std::string, Locationdata> (key, value));
}

void    Servdata::set_fd_req(int fd)
{
    
    this->fd_req = fd;
}


std::string const &Servdata::get_port() const {return (this->serv_port);}

std::string const &Servdata::get_name() const {return this->serv_name;}

std::string const &Servdata::get_host() const {return this->serv_host;}

std::string const &Servdata::get_limit() const {return this->serv_limit;}

std::string const &Servdata::get_error() const {return this->serv_error;}

std::map <std::string, std::string>  const &Servdata::get_cgi() const {return this->serv_cgi;}

std::map <std::string, Locationdata> Servdata::get_loc() const
{
    return(this->serv_loc);
}

bool const &Servdata::get_bool_error() const
{
    return this->bool_error;
}

bool const &Servdata::get_req_done() const
{
    return this->req_done;
}

 request &Servdata::get_request()
 {
    return this->reqst;
 }


response &Servdata::get_res()
{
    return this->respns;
}

void    Servdata::read_req()
{
    bzero(this->buffer, 1024);
    this->valread = 0;
    this->valread = read(this->fd_req, this->buffer, sizeof(this->buffer));
    if(this->valread < 0)
        this->bool_error = true;
    else if(this->reqst.get_bool_head_done() == false)
        this->reqst.set_first_buffer(this, buffer, valread);
    else if (this->reqst.get_bool_body_done() == false)
    {
        if(!this->respns.get_status().compare("201"))
        {
            this->reqst.set_bool_upload("true");
            this->reqst.set_body(this, this->buffer, this->valread);
        }
        else
        {
            this->reqst.set_bool_upload("false");
            this->reqst.set_body(this, this->buffer, this->valread);
        }
    }
    if (this->reqst.get_bool_head_done() == true && this->reqst.get_bool_body_done() == true)
    {
        this->reqst.set_false_head();
        this->reqst.set_false_body();
        this->req_done = true;
    }                                                                                                          
}

bool const &Servdata::get_bool_fdres() const
{
    return this->bool_fdres;
}

void    Servdata::set_body_res()
{
    if(this->respns.get_bool_is_file() == true )
    {
        if(this->get_bool_fdres() == true)
        {
            if(respns.get_cgi_true() == true)
            {
                if(!this->cgi.get_ex().compare(".php"))
                {
                    this->fd_res = open(this->cgi.get_cgi_tmp_name().c_str(), O_RDONLY, 0777);
                    if(this->fd_res < 0)
                    {
                        perror("fd_res not open ");
                        close(this->fd_res);
                    }
                    lseek(this->fd_res, this->respns.get_size_php_h(), SEEK_SET);
                    this->bool_fdres = false;
                }
                else
                {
                    this->respns.set_bool_body_done("true");
                }
            }
            else
            {
                this->fd_res = open(this->respns.get_fd_res().c_str(), O_RDONLY, 0777);
                this->bool_fdres = false;
            }
        }
        if(this->get_bool_fdres() == false)
        {
            this->valread = read(this->fd_res, this->buffer, sizeof(this->buffer));
            if(valread <= 0)
            {
                close(this->fd_res);
                this->bool_fdres = true;
                this->respns.set_bool_body_done("true");
            }
        }
    }
}

int const &Servdata::get_fd_req() const
{
    return this->fd_req;
}

void    Servdata::set_meth()
{
    this->meth = true;
}

bool const &Servdata::get_meth() const
{
    return this->meth;
}

void    Servdata::check_meth_allow()
{
    std::map<std::string, Locationdata> it = this->get_loc();
    std::vector<std::string>::const_iterator ite = it[this->get_request().get_best_location()].get_meth().begin();
    std::vector<std::string>::const_iterator end = it[this->get_request().get_best_location()].get_meth().end();
    for(; ite != end; ++ite)
    {
        if(this->get_request().get_header_req().get_method() == *ite)
        {
            this->set_meth();
            break;
        }
    }
}

void    Servdata::start_response()
{
    int x = 0;
    if(this->respns.get_bool_head_done() == false)
    {
        if(this->get_fd_req() == -1)
        {
            this->respns.set_bool_head_done("true");
            this->respns.set_bool_body_done("true");
        }
        else
        {
            this->valread = 0;
            bzero(this->buffer, 1024);
            std::string hed = "";
            hed = this->respns.set_headers(this->reqst, &this->cgi, this);
            int i = 0;
            while (hed[i])
            {
                this->buffer[i] = hed[i];
                this->valread++;
                i++;
            }
            this->respns.set_bool_head_done("true");
            this->bool_fdres = true;
        }
    }
    else if(this->respns.get_bool_body_done() == false)
    {
        this->set_body_res();
    }
    if(this->respns.get_bool_head_done() == false || this->respns.get_bool_body_done() == false || this->respns.get_bool_is_file() == false)
    {
        x = send(this->get_fd_req(), this->buffer, (size_t)this->valread, 0);
        if(x < 0)
        {
            close(this->fd_res);
            this->res_done = true;
        }
    }
    if (this->respns.get_bool_head_done() == true && this->respns.get_bool_body_done() == true)
    {
        bzero(this->buffer, 1024);
        close(this->fd_res);
        this->res_done = true;
        this->set_bool_header_cgi("true");
        this->get_res().set_support_cgi("true");
        remove(this->cgi.get_cgi_tmp_name().c_str());
        remove("./cgi-bin/body.txt");
    }
}

void    Servdata::set_ex_php(std::string s)
{
    this->ex = s;
}

std::string const &Servdata::get_ex_php() const
{
    return this->ex;
}

bool const &Servdata::get_res_done() const
{
    return this->res_done;
}

void    Servdata::set_res_done()
{
    this->respns.set_bool_head_done("false");
    this->respns.set_bool_body_done("false");
    this->res_done = false;
}

void    Servdata::set_bool_header_cgi(std::string l)
{
    if(!l.compare("true"))
        this->header_cgi = true;
    else
        this->header_cgi = false;
}

bool const &Servdata::get_bool_header_cgi() const
{
    return this->header_cgi;
}

void    Servdata::set_res_done_()
{
    this->res_done = false;
}

std::string Servdata::sup_cgi_conf(std::string l)
{
    std::map <std::string, std::string>::const_iterator it = this->get_cgi().begin();
    std::map <std::string, std::string>::const_iterator ite = this->get_cgi().end();
    for(; it != ite; ++it)
    {
        if(!it->first.compare(l))
            return(it->second);
    }
    return ("");
}

void    Servdata::check_cgi()
{
    this->cgi.set_map_cgi(this->get_cgi());
    this->cgi.cgi(this->get_port(), &this->reqst, &this->respns);
}