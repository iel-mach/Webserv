/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locationdata.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:06:42 by mbouhaba          #+#    #+#             */
/*   Updated: 2023/04/16 07:58:41 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Locationdata.hpp"

void    Locationdata::set_meth(std::string const &u)
{
    this->loc_meth.push_back(u);
}

void    Locationdata::set_root(std::string const &r)
{
    this->loc_root = r;
}

void    Locationdata::set_autoindex(std::string const &u)
{
    this->loc_autoindex = u;
}
void    Locationdata::set_default(std::string const &r)
{
    this->loc_default = r;
}

void    Locationdata::set_upload(std::string const &u)
{
    this->loc_upload = u;
}

void    Locationdata::set_redirect(std::string const &u)
{
    this->loc_redirect = u;
}

std::vector<std::string> Locationdata::get_meth()
{
    return(this->loc_meth);
}

std::string const &Locationdata::get_root() const
{
    return(this->loc_root);
}

std::string const &Locationdata::get_autoindex() const
{
    return(this->loc_autoindex);
}

std::string const &Locationdata::get_default() const
{
    return(this->loc_default);
}

std::string const &Locationdata::get_upload() const
{
    return(loc_upload);
}

std::string const &Locationdata::get_redirect() const
{
    return this->loc_redirect;
}

void    Locationdata::init_attribt()
{
    this->loc_root = "";
    this->loc_autoindex = "";
    this->loc_upload = "";
    this->loc_default = "";
    this->loc_redirect = "";
    this->loc_meth.clear();
}