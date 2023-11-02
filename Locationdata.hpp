/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Locationdata.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 21:09:28 by iel-mach          #+#    #+#             */
/*   Updated: 2023/04/06 05:18:40 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATIONDATA_HPP
#define LOCATIONDATA_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

class Locationdata {
    private:
        std::string loc_redirect;
        std::vector<std::string> loc_meth;
        std::string loc_root;
        std::string loc_autoindex;
        std::string loc_default;
        std::string loc_upload;
    public:
        void    init_attribt();
        void    set_meth(std::string const &u);
        void    set_root(std::string const &r);
        void    set_autoindex(std::string const &u);
        void    set_default(std::string const &r);
        void    set_upload(std::string const &u);
        void    set_redirect(std::string const &u);
        std::vector<std::string> get_meth();
        std::string const &get_root() const;
        std::string const &get_autoindex() const;
        std::string const &get_default() const;
        std::string const &get_upload() const;
        std::string const &get_redirect() const;
};

#endif