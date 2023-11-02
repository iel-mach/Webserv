/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 14:00:04 by mbouhaba          #+#    #+#             */
/*   Updated: 2023/05/14 01:02:19 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "request.hpp"
#include "servdata.hpp"
#include "response.hpp"

request::request()
{
    this->filename = "";
    this->header = "";
    this->uppload = "";
    this->best_location = "";
    this->bound = "";
    this->hexa = "";
    this->fd_body = 0;
    this->length = 0;
    this->first_buffer = false;
    this->head_done = false;
    this->body_done = false;
    this->bool_file = false;
    this->first_chunk = true;
    this->bool_hexa = false;
    this->bool_last_hexa = false;
    this->bool_upload = false;
    this->redec_true = false;
    this->size_bound = 0;
    this->first_file_cgi = true;
}

request::request(const request &o)
{
    *this = o;
}

request const &request::operator=(const request &o)
{
    this->filename = o.filename;
    this->header = o.header;
    this->uppload = o.uppload;
    this->best_location = o.best_location;
    this->bound = o.bound;
    this->fd_body = o.fd_body;
    this->length = o.length;
    this->first_buffer = o.first_buffer;
    this->head_done = o.head_done;
    this->body_done = o.body_done;
    this->bool_file = o.bool_file;
    return(*this);
}

request::~request()
{
    
}

void    request::set_false_head()
{
    this->head_done = false;
}

void    request::set_false_body()
{
    this->body_done = false;
}


void    request::set_bool_body_done()
{
    this->body_done = true;
}

void    request::set_bool_head_done()
{
    this->head_done = true;
}

void    request::set_bool_fisrt_buffer()
{
    this->first_buffer = true;
}

void    request::set_uppload(std::string s)
{
    this->uppload = s;
}

int const   &request::get_lenght() const
{
    return this->length;
}

bool const &request::get_bool_head_done() const
{
    return this->head_done;
}


bool const &request::get_bool_body_done() const
{
    return this->body_done;
}

void    request::set_child_executed(std::string l)
{
    if(!l.compare("true"))
        this->child_executed = true;
    else
        this->child_executed = false;
}

bool    const &request::get_child_executed() const
{
    return this->child_executed;
}

header_req const &request::get_header_req() const
{
    return this->hed;
}

void    request::set_fd_body(int _fd_body)
{
    this->fd_body = _fd_body;
}

int const   &request::get_fd_body() const
{
    return this->fd_body;
}

void    request::set_file_name(std::string l)
{
    this->filename = "";
    std::string rnd = "";
    if(this->hed.get_bool_bound() == false)
    {
        if(this->get_bool_upload() == true)
        {
            srand(time(NULL));
            std::string alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
            for (int i = 0; i < 8; i++)
                rnd += alpha[rand() % alpha.size()];
                this->filename =  l + rnd + get_extencion(this->hed.get_content_type());
        }
    }
}

std::string const &request::get_best_location() const
{
    return this->best_location;
}

std::string const &request::get_uppload() const
{
    return this->uppload;
}

std::string const &request::get_file_name() const
{
    return this->filename;
}

bool const &request::get_first_chunk() const
{
    return this->first_chunk;
}

bool const &request::get_bool_last_hexa() const
{
    return this->bool_last_hexa;
}

bool const &request::get_bool_hexa() const
{
    return this->bool_hexa;
}

void    request::check_query(std::string token)
{
    int i = 0;
    std::string uri = "";
    std::string query = "";
    while(token[i])
    {
        if(token[i] == '?')
        {
            i++;
            while(token[i])
                query += token[i++];
            if(!token[i])
                break;
        }
        else
            uri += token[i];
        i++;
    }
    this->hed.set_path(uri);
    this->hed.set_query(query);
}

void    request::set_header()
{
    std::string token;
    std::string jojo;
    std::string cmp;
    this->hed.set_all_header(this->header);
    std::stringstream ss(this->header);
    getline(ss, token, ' ');
    this->hed.set_method(token);
    getline(ss, token, ' ');
    this->check_query(token);
    getline(ss, token);
    this->hed.set_version(token.substr(0, 8));
     while(getline(ss, token, ':'))
    {
        if(!token.compare("Host"))
        {
            getline(ss, token, ':');
            getline(ss, cmp, '\n');
            cmp = trim(cmp);
            this->hed.set_host(cmp);
        }
        getline(ss, cmp, '\n');
        if(!token.compare("Content-Type"))
        {
            this->hed.set_content_type(cmp);
			this->hed.set_bool_type();
            if(cmp.find("boundary") != std::string::npos)
            {
                std::stringstream ss(cmp);
                std::string boun;
                getline(ss, boun, ';');
                getline(ss, boun, '\n');
                std::string s = ltrim(boun);
                int length = s.length();
                std::string bi = "";
                int i = 0;
                while (i < length - 1)
                {
                    if(s[i] == '=')
                    {
                        i++;
                        bi = "--";
                        while(i < length - 1)
                        {
                            bi += s[i];
                            i++;
                        }
                        bi += "--";
                    }
                    else
                        i++;
                }
                this->hed.set_bound(bi);
                this->hed.set_bool_bound();
            }
        }
        if(!token.compare("User-Agent"))
            this->hed.set_User_agent(cmp);
        if(!token.compare("Accept"))
            this->hed.set_accept(cmp);
        if(!token.compare("Accept-Encoding"))
            this->hed.set_accept_encoding(cmp);
        if(!token.compare("Connection"))
            this->hed.set_connection(cmp);
        if(!token.compare("Content-Length"))
        {
            this->hed.set_content_length(stoi(cmp));
            this->hed.set_bool_length();
        }
        if (!token.compare("Transfer-Encoding"))
        {
            cmp = trim(cmp);
            this->hed.set_transfer_encoding(cmp);
            this->hed.set_bool_encoding();
        }
        if(!token.compare("Cookie"))
        {
            cmp = trim(cmp);
            this->hed.set_cookie(cmp);
        }
    }
}

std::string const &request::get_short_path() const
{
    return this->short_path;
}

void    request::set_short_path(std::string path)
{
    int i = 0;
    this->short_path = "";
    while(path[i])
    {
        if(this->best_location[i] == path[i])
            i++;
        else
        {
            this->short_path += path[i];
            i++;
        }
    }
}

void    request::set_best_location(std::map<std::string, Locationdata> const &serv_loc)
{
    int best_same_char = 0;
    std::string def_loc = "";
    int same_char;
    std::string path = "";
    path = this->get_header_req().get_path();
    for (std::map<std::string, Locationdata>::const_iterator it = serv_loc.begin(); it != serv_loc.end(); ++it)
    {
        same_char = 0;
        if(it->first == "/")
        {
            def_loc = it->first;
        }
        for (size_t j = 0; j < it->first.length() ; j++)
        {
            if(it->first[j] != path[j])
                break ;
            if(it->first[j] == '/' || (path[j + 1] == '\0' && it->first[j + 1] == '/'))
               same_char++;
        }
        if (same_char > best_same_char)
        {
            this->best_location = it->first;
            best_same_char = same_char;
        }
    }
    if (best_same_char == 0)
    {
        this->best_location = def_loc;
    }
    this->set_short_path(this->get_header_req().get_path());
    this->search_upload_location(serv_loc);
}

std::string request::get_extencion(std::string const &extencio)
{
    std::string extencion = trim(extencio);
    if(!extencion.empty())
    {
        if (extencion == "text/html") return ".html";
		else if (extencion == "text/css") return ".css";
		else if (extencion == "text/xml") return ".xml";
		else if (extencion == "text/csv") return ".csv";
		else if (extencion == "image/gif") return ".gif";
		else if (extencion == "image/x-icon") return ".ico";
		else if (extencion == "image/jpeg") return ".jpg";
		else if (extencion == "application/javascript") return ".js";
		else if (extencion == "application/json") return ".json";
		else if (extencion == "image/png") return ".png";
		else if (extencion == "application/pdf") return ".pdf";
		else if (extencion == "image/svg+xml") return ".svg";
		else if (extencion == "text/plain") return ".txt";
		else if (extencion == "application/atom+xml") return ".atom";
		else if (extencion == "application/rss+xml") return ".rss";
		else if (extencion == "image/webp") return ".webp";
		else if (extencion == "video/3gpp") return	".3gpp";
		else if (extencion == "video/3gpp") return ".3gp";
		else if (extencion == "video/mp2t") return ".ts";
		else if (extencion == "video/mp4") return ".mp4";
		else if (extencion == "video/mpeg") return ".mpeg";
		else if (extencion == "video/mpeg") return ".mpg";
		else if (extencion == "video/quicktime") return ".mov";
		else if (extencion == "video/webm") return ".webm";
		else if (extencion == "video/x-flv") return ".flv";
		else if (extencion == "video/x-m4v") return ".m4v";
		else if (extencion == "video/x-mng") return ".mng";
		else if (extencion == "video/x-ms-asf") return ".asx";
		else if (extencion == "video/x-ms-asf") return ".asf";
		else if (extencion == "video/x-ms-wmv") return ".wmv";
		else if (extencion == "video/x-msvideo") return ".avi";
		else if (extencion == "text/mathml") return ".mml";
		else if (extencion == "text/vnd.sun.j2me.app-descriptor") return ".jad";
		else if (extencion == "text/vnd.wap.wml") return ".wml";
		else if (extencion == "text/x-component") return ".htc";
		else if (extencion == "image/tiff") return ".tiff";
		else if (extencion == "image/vnd.wap.wbmp") return ".wbmp";
		else if (extencion == "image/x-jng") return ".jng";
		else if (extencion == "image/x-ms-bmp") return ".bmp";
		else if (extencion == "image/svg+xml") return ".svg";
		else if (extencion == "audio/midi") return ".mid";
		else if (extencion == "audio/mpeg") return ".mp3";
		else if (extencion == "audio/ogg") return ".ogg";
		else if (extencion == "audio/x-m4a") return ".m4a";
		else if (extencion == "audio/x-realaudio") return ".ra";
		else if (extencion == "application/x-perl") return ".pl";
		else if (extencion == "application/x-python") return ".py";
		else if (extencion == "application/x-php") return ".php";
		else if (extencion == "text/x-c++") return ".cpp";
		else if (extencion == "text/x-c") return ".c";
    }
    return ".txt";
}

void    request::set_bool_list_folder(std::string l)
{
    if(!l.compare("true"))
        this->bool_list_folder = true;
    else
        this->bool_list_folder = false;
}

bool const &request::get_bool_list_folder() const
{
    return this->bool_list_folder;
}

void    request::search_upload_location(std::map<std::string, Locationdata> const &serv_loc)
{
    for (std::map<std::string, Locationdata>::const_iterator it = serv_loc.begin(); it != serv_loc.end(); ++it)
    {
        if(it->first.compare(this->best_location) == 0)
        {
            if(access((it->second.get_root() + it->second.get_upload()).c_str(), F_OK) == 0)
                this->set_uppload(it->second.get_root() + it->second.get_upload());
            if(!this->get_header_req().get_path().compare(this->best_location))
            {
                this->hed.set_full_path(it->second.get_root() + "/");
                this->set_bool_list_folder("false");
                this->redec_true = false;
            }
            else
            {
                this->hed.set_full_path(it->second.get_root() + "/" + this->get_short_path());
                if(!this->hed.get_full_path().compare(it->second.get_root() + "/"))
                    this->set_bool_list_folder("false");
                else
                    this->set_bool_list_folder("true");
            }
        }
    }
}

void    request::set_redec_true()
{
    this->redec_true = true;
}

bool const    &request::get_redec()
{
    return this->redec_true;
}

void    request::set_bool_upload(std::string const &l)
{
    if(!l.compare("true"))
        this->bool_upload = true;
    else
        this->bool_upload = false;
}

bool const &request::get_bool_upload() const
{
    return this->bool_upload;
}

void    request::set_content_length(char *buffer, int valread)
{
    if(this->bool_file == false)
    {
        if(this->get_bool_upload() == true)
        {
            this->set_file_name(this->get_uppload());
            this->fd_body = open(this->filename.c_str(), O_CREAT | O_RDWR, 0777);
        }
        else
        {
            this->filename = "./cgi-bin/body.txt";
            this->fd_body = open(this->filename.c_str(), O_CREAT | O_RDWR | O_TRUNC, 0777);
        }
        this->bool_file = true;
    }
    if(this->first_buffer == true)
    {
        int in_hed = valread;
        while(valread < 1024)
        {
            if(buffer[valread] == '\0')
                break;
            write(this->fd_body, &buffer[valread], 1);
            valread++;
        }
        this->length += valread - in_hed;
        if(this->get_lenght() == this->hed.get_content_length())
        {
            
            this->length = 0;
            close(this->fd_body);
            this->set_bool_body_done();
        }
        this->first_buffer = false;
    }
    else
    {
        write(this->fd_body, buffer, valread);
        this->length += valread;
        if(this->get_lenght() == this->hed.get_content_length())
        {
            
            this->length = 0;
            close(this->fd_body);
            this->set_bool_body_done();
        }
    }
}

void    request::set_file_bound(std::string bound)
{
    int pos = bound.find("filename=") + 10;
    this->filename = "";
    while(bound[pos] != '"')
    {
        this->filename += bound[pos];
        pos++;
    }
    if (access(this->filename.c_str(), F_OK) != -1)
    {
        std::ofstream out((this->get_uppload() + this->filename).c_str(), std::ios::out | std::ios::trunc);
        out.close();
        this->fd_body = open((this->get_uppload() + this->filename).c_str(), O_CREAT | O_RDWR , 0777);
    }
    else
       this->fd_body = open((this->get_uppload() + this->filename).c_str(), O_CREAT | O_RDWR, 0777);
}

void    request::set_content_bound(Servdata *serv, char *buffer, int valread)
{
    this->bound = "";
    int i;
    if(this->first_buffer == true && this->hed.get_bound_done() == false && serv->get_res().get_support_cgi() == false)
    {
        while(valread < 1024)
        {
            if(buffer[valread] == '\n' && buffer[valread + 1] == '\r')
                break;
            bound += buffer[valread];
            valread++;
        }
        if(this->get_bool_upload() == true)
            this->set_file_bound(bound);
            
        if(this->get_header_req().get_content_length() < 1024)
        {
            i = valread + 3;
            valread = valread + this->get_header_req().get_content_length();
            const char* it = std::search(buffer, &buffer[valread], this->hed.get_bound().begin(), this->hed.get_bound().end());
            if(it < &buffer[valread])
            {
                std::string last_buffer = "";
                last_buffer.append(buffer, valread);
                int find_bound = last_buffer.find(this->hed.get_bound());
                find_bound = find_bound - 2;
                while(i < find_bound)
                {
                    write(this->fd_body, &buffer[i], 1);
                    i++;
                }
                close(this->fd_body);
                this->set_bool_body_done();
            }
        }
        else
        {
            if (valread < 1024)
            {
                valread = valread + 3;
                while(valread < 1024)
                {
                    write(this->fd_body, &buffer[valread], 1);
                    valread++;
                }
            }
            this->hed.set_bool_bound_done();
        }
    }
    else if(this->first_buffer == false && this->hed.get_bound_done() == false && serv->get_res().get_support_cgi() == false)
    {
        i = 0;
        while(i < valread)
        {
            if(buffer[i] == '\n' && buffer[i + 1] == '\r')
                break;
            bound += buffer[i];
            i++;
        }
        if(this->get_bool_upload() == true)
            this->set_file_bound(bound);
        if(this->get_header_req().get_content_length() < 1024)
        {
            i = i + 3;
            const char* it = std::search(buffer, &buffer[valread], this->hed.get_bound().begin(), this->hed.get_bound().end());
            if(it < &buffer[valread])
            {
                std::string last_buffer = "";
                last_buffer.append(buffer, valread);
                int find_bound = last_buffer.find(this->hed.get_bound());
                find_bound = find_bound - 2;
                while(i < find_bound)
                {
                    write(this->fd_body, &buffer[i], 1);
                    i++;
                }
                close(this->fd_body);
                this->set_bool_body_done();
            }
        }
        else
        {
            if (i < valread)
            {
                i = i + 3;
                while(i < valread)
                {
                    write(this->fd_body, &buffer[i], 1);
                    i++;
                }
            }
        }
        this->hed.set_bool_bound_done();
    }
    else if (this->hed.get_bound_done() == true && serv->get_res().get_support_cgi() == false)
    {
        const char* it = std::search(buffer, &buffer[valread], this->hed.get_bound().begin(), this->hed.get_bound().end());
        if(it < &buffer[valread])
        {
            i = 0;
            std::string last_buffer = "";
            last_buffer.append(buffer, valread);
            int find_bound = last_buffer.find(this->hed.get_bound());
            find_bound = find_bound - 2;
            while(i < find_bound)
            {
                write(this->fd_body, &buffer[i], 1);
                i++;
            }
            close(this->fd_body);
            this->set_bool_body_done();
        }
        else
            write(this->fd_body, buffer, valread);
    }
    if(serv->get_res().get_support_cgi() == true)
    {
        if(this->first_file_cgi == true)
        {
            this->fd_body = open("./cgi-bin/body.txt", O_CREAT | O_RDWR | O_APPEND | O_TRUNC, 0777);
            this->first_file_cgi = false;
        }
        if(this->first_buffer == true)
        {
            this->size_bound = 1024 - valread;
            while(valread < 1024)
            {
                write(this->fd_body, &buffer[valread], 1);
                valread++;
            }
            this->first_buffer = false;
        }
        else
        {
            write(this->fd_body, buffer, valread);
            this->size_bound += valread;
            if(this->size_bound >= this->get_header_req().get_content_length())
            {
                this->set_bool_body_done();
                this->size_bound = 0;
                this->first_file_cgi = true;
                close(fd_body);
            }
        }
    }
}

void    request::set_first_buffer(Servdata *serv, char *buffer, int valread)
{
    this->header = "";
    int pos = std::string(buffer).find("\r\n\r\n");
    if(valread != (pos  + 4))
    {
        int i = 0;
        while(i < pos)
        {
            this->header += buffer[i];
            i++;
        }
        this->set_header();
        this->set_best_location(serv->get_loc());
        this->head_done = true;
        this->first_buffer = true;
        this->bool_file = false;
        this->first_chunk = true;
        this->first_file_cgi = true;
        serv->check_meth_allow();
        serv->get_res().check_error(serv);
        if(serv->get_meth() == false)
            this->body_done = true;
        if(!serv->get_res().get_status().compare("201"))
            this->set_bool_upload("true");
        this->set_body(serv, buffer, pos + 4);
         if(!this->hed.get_method().compare("GET") || !this->hed.get_method().compare("DELETE"))
            this->body_done = true;
    }
    else
    {
        this->header = std::string(buffer);
        this->set_header();
        this->set_best_location(serv->get_loc());
        this->head_done = true;
        this->bool_file = false;
        this->first_buffer = false;
        this->first_chunk = true;
        serv->check_meth_allow();
        serv->get_res().check_error(serv);
        if(serv->get_meth() == false)
            this->body_done = true;
        if((!this->hed.get_method().compare("GET") || !this->hed.get_method().compare("DELETE")))
            this->body_done = true;
    }
}

void    request::set_body(Servdata *serv, char *buffer, int valread)
{
    if(!this->hed.get_method().compare("POST"))
    {
        if(this->hed.get_bool_bound() == false)
            this->set_content_length(buffer, valread);
        else
        {
            this->set_content_bound(serv, buffer, valread);
        }
    }
    else if(this->hed.get_bool_encoding() == true && !this->hed.get_method().compare("POST") && !this->hed.get_transfer_encoding().compare("chunked"))
    {
        if(this->first_buffer == true && this->get_first_chunk() == true)
        {
            valread = valread + 6;
            while(valread < 1024)
            {
                write(this->fd_body, &buffer[valread], 1);
                valread++;
            }
            this->first_chunk = false;
            this->bool_last_hexa = false;
        }
        else if(this->first_buffer == false && this->get_first_chunk() == true)
        {
            int i = 6;
            while(i < valread)
            {
                write(this->fd_body, &buffer[i], 1);
                i++;
            }
            this->first_chunk = false;
            this->bool_last_hexa = false;
        }
        else if(this->get_first_chunk() == false)
        {
            std::string chunked = "";
            chunked.append(buffer, valread);
            std::string to_find = "\r\n";
            const char* it = std::search(buffer, &buffer[valread], to_find.begin(), to_find.end());
            if(it < &buffer[valread])
            {
                int i = 0;
                int lpo = 0;
                this->hexa = "";
                if (this->get_bool_last_hexa() == false)
                    i = 0;
                else
                {
                    if(isxdigit(chunked[i]))
                        i = 3;
                    else
                        i = 2;
                    this->bool_last_hexa = false;
                }
                this->bool_hexa = false;
                while (i < valread)
                {
                    if(chunked[i] == '\r' && chunked[i + 1] == '\n')
                    {
                        lpo = i + 2;
                        while(chunked[lpo] != '\r' && lpo < valread)
                        {
                            if((!isxdigit(chunked[lpo])))
                            {
                                this->bool_hexa = false;
                                    this->hexa = "";
                                    break;
                            }
                            else if (isxdigit(chunked[lpo]))
                            {
                                this->hexa += buffer[lpo];
                                this->bool_hexa = true;
                            }
                            lpo++;
                        }
                        if (this->get_bool_hexa() == true)
                        {
                            if (lpo == valread)
                            {
                                this->bool_last_hexa = true;
                                break;
                            }
                            else if (lpo < valread)
                                lpo = lpo + 2;
                            if (this->hexa.compare("0") == 0)
                            {
                                this->set_bool_body_done();
                                this->bool_last_hexa = false;
                                this->hexa = "";
                                break;
                            }
                            this->hexa = "";
                            i = i + (lpo - i);
                        }
                    }
                    write(this->fd_body, &buffer[i], 1);
                    i++;
                }
            }
            else
                write(this->fd_body, buffer, valread);
        }
    }
}
