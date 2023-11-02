/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:53:04 by mbouhaba          #+#    #+#             */
/*   Updated: 2023/05/12 23:11:45 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "Locationdata.hpp"
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
#include "header.hpp"

class Servdata;

class request{
private:
    int size_bound;
    bool    first_file_cgi;
    header_req hed;
    std::string header;
    std::string filename;
    std::string uppload;
    std::string best_location;
    std::string hexa;
    std::string bound;
    std::string short_path;
    int     fd_body;
    int     length;
    bool    head_done;
    bool    first_buffer;
    bool    body_done;
    bool    bool_file;
    bool    first_chunk;
    bool    bool_last_hexa;
    bool    bool_hexa;
    bool    bool_upload;
    bool    redec_true;
    bool child_executed;
    bool    bool_list_folder;
public:
    request();
    request(const request &o);
    request const &operator=(const request &o);
    ~request();
    header_req const &get_header_req() const;
    void    set_header();
    void    set_fd_body(int _fd_body);
    void    set_first_buffer(Servdata *serv, char *buffer, int valread);
    void    set_bool_head_done();
    void    set_body(Servdata *serv, char *buffer, int valread);
    void    set_bool_fisrt_buffer();
    void    set_bool_body_done();
    void    set_file_name(std::string l);
    void    set_false_head();
    void    set_false_body();
    void    set_content_length(char *buffer, int valread);
    void    set_content_bound(Servdata *serv, char *buffer, int valread);
    void    set_uppload(std::string s);
    void    set_file_bound(std::string bound);
    void    set_best_location(std::map<std::string, Locationdata> const &serv_loc);
    void    search_upload_location(std::map<std::string, Locationdata> const &serv_loc);
    void    set_bool_upload(std::string const &l);
    void    check_query(std::string token);
    void    set_short_path(std::string path);
    void    set_child_executed(std::string l);
    void    set_bool_list_folder(std::string l);
    int const   &get_lenght() const;
    int const   &get_fd_body() const;
    bool const  &get_bool_head_done() const;
    bool const  &get_bool_body_done() const;
    bool const  &get_first_chunk() const;
    bool const  &get_bool_last_hexa() const;
    bool const  &get_bool_hexa() const;
    bool const  &get_bool_upload() const;
    std::string get_extencion(std::string const &extencion);
    std::string const &get_uppload() const;
    std::string const &get_file_name() const;
    std::string const &get_best_location() const;
    std::string const &get_short_path() const;
    void    set_redec_true();
    bool const    &get_redec();
    bool    const &get_child_executed() const;
    bool const &get_bool_list_folder() const;

};


#endif