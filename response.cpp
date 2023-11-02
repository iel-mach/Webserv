/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:45:10 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 01:23:48 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include "servdata.hpp"

response::response()
{
    this->headers = "";
    this->content_type = "";
    this->content_length = 0;
    this->status = "";
    this->extension_get = "";
    this->support_cgi = false;
}

response::~response()
{
    
}

std::string int_to_string(long f_size)
{
    std::string size_str = "";
    std::stringstream ss;
    ss << f_size;
    size_str = ss.str();
    return (size_str);
}

void response::file_size(std::string r)
{
    FILE* file = fopen(r.c_str(), "rb");
    if (file == NULL)
        printf("Error opening file\n");
    else
    {
        fseek(file, 0, SEEK_END);
        long f_size = ftell(file);
        this->set_content_length(f_size);
    }
    fclose(file);
}

void    response::set_cgi_true(std::string l)
{
    if(!l.compare("true"))
        this->cgi_true = true;
    else
        this->cgi_true = false;  
}

bool    const &response::get_cgi_true() const
{
    return this->cgi_true;
}

std::string const &response::set_headers(request &r, Cgi *cgi, Servdata *serv)
{
    this->headers = "";
    std::string token = "";
    std::map<std::string, Locationdata> it = serv->get_loc();
    if(serv->get_error().empty() && this->status.compare("301") && this->status.compare("200") && this->status.compare("201") && this->status.compare("204"))
    {
        this->headers = "HTTP/1.1 500 Internal Server Error\r\n";
        this->headers += "Content-Type: text/html\r\n";
        this->headers += "Content-Length: " + int_to_string(85) + "\r\n\r\n";
        this->headers += "<html><body><h1>Error: Configuration file is missing or Error_pages doesn't exist.</h1></body></html>";
        this->set_bool_body_done("false");
        return (this->headers);
    }
    if(this->get_cgi_true() == false)
    {
        if(!r.get_header_req().get_method().compare("GET"))
        {
            if(this->get_bool_is_file() == false && this->status.compare("301"))
            {
                std::string folder = "";
                DIR *dire;
                dire = opendir(this->error_filename[this->get_status()].c_str());
                struct dirent *ent;
                if(r.get_bool_list_folder() == true)
                {
                    std::ostringstream oss;
                    oss << "<ul>\n";
                    while ((ent = readdir(dire)) != NULL) {
                        oss << "  <li><a href=\"" << ent->d_name << "\">" << ent->d_name << "</a></li>\n";
                    }
                    oss << "</ul>\n";
                    folder = oss.str();
                }
                else
                {
                    while ((ent = readdir(dire)) != NULL) 
                    {
                        folder += "<li>";
                        folder += ent->d_name; 
                        folder += "</li>";
                        folder += "\n\n";
                    }
                }
                closedir(dire);
                this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
                this->headers += "Content-Type: text/html\r\n";
                int i = folder.length();
                this->headers += "Content-Length: " + int_to_string(i) + "\r\n\r\n";
                this->headers += folder;
                this->set_bool_body_done("true");
            }
            else if(this->get_bool_is_file() == false && !this->status.compare("301"))
            {
                if(this->get_bool_redec() == false)
                {
                    this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
                    this->headers += "Location: " + this->get_path_before() + "/";
                }
                else
                {
                    this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
                    this->headers += "Location: " + it[serv->get_request().get_best_location()].get_redirect();
                }
                this->set_bool_body_done("true");
            }
            else if(this->get_bool_is_file() == true)
            {
                this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
                this->headers += "Content-Type: " + this->content_type + "\r\n";
                this->headers += "Content-Length: " + int_to_string(this->content_length) + "\r\n\r\n";
            }
        }
        else if(!r.get_header_req().get_method().compare("DELETE"))
        {
            this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
            this->headers += "Content-Type: " + this->content_type + "\r\n";
                this->headers += "Content-Length: " + int_to_string(this->content_length) + "\r\n\r\n";
        }
        else if(!r.get_header_req().get_method().compare("POST"))
        {
            if(this->get_bool_is_file() == true)
            {
                this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
                this->headers += "Content-Type: " + this->content_type + "\r\n";
                this->headers += "Content-Length: " + int_to_string(this->content_length) + "\r\n\r\n";
            }
        }
        else
        {
            this->headers = "HTTP/1.1 " + this->res_status[this->get_status()] + "\r\n";
            this->headers += "Content-Type: " + this->content_type + "\r\n";
            this->headers += "Content-Length: " + int_to_string(this->content_length) + "\r\n\r\n";
        }
    }
    else
    {
        if(!cgi->get_ex().compare(".py"))
        {
            std::ifstream infile(cgi->get_cgi_tmp_name()); 
            this->file_size(cgi->get_cgi_tmp_name());
            this->headers = "HTTP/1.1 200 OK\r\n";
            this->headers += "Content-Type: text/html\r\n";
            this->headers += "Content-Length: " + int_to_string(this->get_content_length()) + "\r\n\r\n";
            token = "";
            getline(infile, token);
            token += "\n";
            this->headers += token;
            infile.close();
        }
        else
        {
            std::ifstream infile(cgi->get_cgi_tmp_name());
            int size = 0;
            if (infile.is_open())
            {
                this->headers = "HTTP/1.1 200 OK\r\n";
                while(getline(infile, token))
                {
                    token += "\n";
                    size += token.length();
                    if (token.compare("\r\n") == 0)
                    {
                        break;
                    }
                    this->headers += token;
                }
                this->set_size_php_h(size);
            }
            this->file_size(cgi->get_cgi_tmp_name());
            this->headers += "Content-Length: " + int_to_string(this->get_content_length() - this->get_size_php_h()) + "\r\n\r\n";
            infile.close();
        }
    }
    return this->headers;
}

void    response::set_size_php_h(int l)
{
    this->size_php_h = l;
}

int response::get_size_php_h() const
{
    return this->size_php_h;
}

std::string response::get_fd_res() const
{
    for(std::map<std::string, std::string>::const_iterator it = this->error_filename.begin(); it != this->error_filename.end(); ++it)
    {
        if(this->status == it->first)
            return it->second;
    }
    return NULL;
}

void    response::set_status(std::string stat)
{
    if(stat.compare("200"))
        this->set_bool_is_file("true");
    this->status = stat;
}

void    response::set_res_status(request &r, std::string path_error)
{
    this->res_status["200"] = "200 OK";
    this->res_status["400"] = "400 Bad Request";
    this->res_status["403"] = "403 Forbidden";
    this->res_status["404"] = "404 Not Found";
    this->res_status["405"] = "405 Method Not Allowed";
    this->res_status["413"] = "413 Payload Too Large";
    this->res_status["414"] = "414 URI Too Long";
    this->res_status["501"] = "501 Not Implemented";
    this->res_status["505"] = "505 HTTP Version Not Supported";
    this->res_status["301"] = "301 Moved Permanently";
    this->res_status["409"] = "409 Conflict";
    this->res_status["204"] = "204 No Content";
    this->res_status["500"] = "500 Internal Server Error";
    this->res_status["201"] = "201 Created";

    if(this->get_bool_defaul() == false)
        this->error_filename["200"] = r.get_header_req().get_full_path();
    else
        this->error_filename["200"] = this->get_new_file();

    this->error_filename["400"] = path_error + "bad_request.html";
    this->error_filename["403"] = path_error + "forbidden.html";
    this->error_filename["404"] = path_error + "not_found.html";
    this->error_filename["405"] = path_error + "no_allowed_method.html";
    this->error_filename["413"] = path_error + "payload_large.html";
    this->error_filename["414"] = path_error + "URI_Too_Long.html";
    this->error_filename["501"] = path_error + "not_implemented.html";
    this->error_filename["505"] = path_error + "Not_Supported.html";
    this->error_filename["301"] = path_error + "redirect.html";
    this->error_filename["204"] = path_error + "delete_content.html";
    this->error_filename["409"] = path_error + "conflict.html";
    this->error_filename["500"] = path_error + "internal_serv_error.html";
    this->error_filename["201"] = path_error + "post_created.html";
    this->set_path_before(r.get_header_req().get_path());
}

void    response::set_content_type(std::string s)
{
    this->content_type = s;
}

void    response::set_path_before(std::string l)
{
    this->path_before_redirect = l;
}

void    response::set_content_length(long t)
{
    this->content_length = t;
}

void    response::set_bool_is_file(std::string l)
{
    if(l == "true")
        this->is_file = true;
    else
        this->is_file = false;
}
bool    response::get_bool_is_file()
{
    return this->is_file;
}

void    response::set_bool_is_file_del(std::string l)
{
    if(l == "true")
        this->is_file_delete = true;
    else
        this->is_file_delete = false;
}
bool    response::get_bool_is_file_del()
{
    return this->is_file_delete;
}

std::string const &response::get_path_before() const
{
    return this->path_before_redirect;
}

void    response::set_extension_get()
{
    std::string extencion = "";
    int pos = this->get_fd_res().find_last_of(".");
    if (pos > 0)
        extencion = this->get_fd_res().substr(pos);
    if(!extencion.empty())
    {
        if (extencion == ".html") set_content_type("text/html");
		else if (extencion == ".htm") set_content_type("text/html");
		else if (extencion == ".shtml") set_content_type("text/html");
		else if (extencion == ".css") set_content_type( "text/css");
		else if (extencion == ".xml") set_content_type( "text/xml");
		else if (extencion == ".csv") set_content_type( "text/csv");
		else if (extencion == ".gif") set_content_type( "image/gif");
		else if (extencion == ".jpeg") set_content_type( "image/jpeg");
		else if (extencion == ".jpg") set_content_type( "image/jpeg");
		else if (extencion == ".js") set_content_type( "application/javascript");
		else if (extencion == ".json") set_content_type( "application/json");
		else if (extencion == ".png") set_content_type( "image/png");
		else if (extencion == ".pdf") set_content_type( "application/pdf");
		else if (extencion == ".txt") set_content_type( "text/plain");
		else if (extencion == ".mp4") set_content_type( "video/mp4");
		else if (extencion == ".mov") set_content_type( "video/quicktime");
		else if (extencion == ".ico") set_content_type( "image/x-icon");
		else if (extencion == ".mp3") set_content_type( "audio/mpeg");
		else if (extencion == ".ra") set_content_type( "audio/x-realaudio");
		else if (extencion == ".pl") set_content_type( "application/x-perl");
		else if (extencion == ".py") set_content_type( "application/x-python");
		else if (extencion == ".php") set_content_type( "application/x-php");
		else if (extencion == ".cpp") set_content_type( "application/x-c++");
		else if (extencion == ".c") set_content_type( "application/x-c");
        
    }
    else
        set_content_type("text/plain");
    this->file_size(this->get_fd_res());
}


bool const &response::get_bool_defaul() const
{
    return this->bool_default;
}

void    response::set_bool_head_done(std::string l)
{
    if(!l.compare("true"))
    {
        this->bool_head_done = true;
    }
    else if(!l.compare("false"))
        this->bool_head_done = false;
}
void    response::set_bool_body_done(std::string l)
{
    if(l == "true")
        this->bool_body_done = true;
    else if(l == "false")
        this->bool_body_done = false;
}

std::string const &response::get_headers() const
{
    return this->headers;
}

long  const &response::get_content_lenght() const
{
    return this->content_length;
}

std::string const &response::get_content_type() const
{
    return this->content_type;
}

std::map<std::string, std::string> const &response::get_res_status() const
{
    return this->res_status;
}

std::string const &response::get_status() const
{
    return this->status; 
}

bool const &response::get_bool_body_done() const
{
    return this->bool_body_done;
}
bool const &response::get_bool_head_done() const
{
    return this->bool_head_done;
}

void    response::set_bool_default(std::string l)
{
    if(l == "true")
        this->bool_default = true;
    else if(l == "false")
        this->bool_default = false;
}

void    response::set_new_file(std::string f_path)
{
    this->new_file = f_path;
}

void    response::set_support_cgi(std::string l)
{
    if(l == "true")
        this->support_cgi = true;
    else if(l == "false")
        this->support_cgi = false;
}

std::string const &response::get_new_file() const
{
    return this->new_file;
}

bool const &response::get_support_cgi() const
{
    return this->support_cgi;
}

long    const &response::get_content_length() const
{
    return this->content_length;
}

void    response::ft_delete(std::string full_path)
{
    struct stat s;
    std::string child_path = "";
    int result = stat(full_path.c_str(), &s);
    if(result == -1)
    {
        this->set_status("404");
    }
    else if (S_ISDIR(s.st_mode))
    {
        if (full_path.back() != '/')
        {
            this->set_status("409");
            return ;
        }
        DIR* dir = opendir(full_path.c_str());
        if (!dir)
        {
            this->set_status("500");
            return ;
        }
        dirent* entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            child_path = full_path + entry->d_name;
            if(stat(child_path.c_str(), &s) != -1)
            {
                if(S_ISDIR(s.st_mode))
                    child_path = full_path + entry->d_name + "/";
            }
            ft_delete(child_path);
        }
        result = rmdir(full_path.c_str());
        closedir(dir);
        if(result == -1)
        {
            if (access(full_path.c_str(), W_OK) != 0)
                this->set_status("500");
            else
            {
                this->set_status("403");
            }
        }
        else
            this->set_status("204");
    }
    else if (S_ISREG(s.st_mode))
    {
        if (access(full_path.c_str(), W_OK) != 0)
        {
            this->set_status("403");
        }
        else
        {
            remove(full_path.c_str());
            this->set_status("204");
        }
    }
    else
        this->set_status("500");
}


void    response::set_first_cgi(std::string l)
{
    if(!l.compare("true"))
        this->first_cgi = true;
    else if (!l.compare("false"))
        this->first_cgi = false;
}

bool response::get_first_cgi()
{
    return this->first_cgi;
}

void response::exetention_cgi(std::string path_cgi)
{
    int pos = path_cgi.find_last_of(".");
    std::string ex = path_cgi.substr(pos);
    if(!ex.compare(".php") || !ex.compare(".py"))
    {
        this->set_support_cgi("true");
        this->set_first_cgi("true");
    }
}

void response::content_type_from_php(std::string s)
{
    int pos = s.find("Content-type: ");
    int pos2 = s.find(";");
    pos = pos + 14;
    int pos3 = pos2 - pos;
    std::string st = s.substr(pos, pos3);
    set_content_type(st);
}

void response::ft_get(Servdata *serv)
{
    struct stat s;
    if(stat(serv->get_request().get_header_req().get_full_path().c_str(), &s) == 0 )
    {
        if(S_ISDIR(s.st_mode))
        {
            std::map<std::string, Locationdata> it = serv->get_loc();
            if(serv->get_request().get_header_req().get_full_path()[serv->get_request().get_header_req().get_full_path().size() - 1] == '/')
            {
                if(it[serv->get_request().get_best_location()].get_default().empty()) 
                {
                    if (!it[serv->get_request().get_best_location()].get_autoindex().compare("off"))
                        this->set_status("403");
                    
                }
                else if(!it[serv->get_request().get_best_location()].get_default().empty())
                {
                    std::string f_path = serv->get_request().get_header_req().get_full_path() + it[serv->get_request().get_best_location()].get_default();
                    if(stat(f_path.c_str(), &s) == 0)
                    {
                        this->set_bool_default("true");
                        this->set_bool_is_file("true");
                        this->set_new_file(f_path);
                        exetention_cgi(f_path);
                    }
                    else
                    {
                        if (!it[serv->get_request().get_best_location()].get_autoindex().compare("off"))
                        {
                            this->set_status("403");
                            
                        }
                        else
                        {
                            this->set_bool_default("false");
                            this->set_bool_is_file("false");
                        }
                    }
                }
            }
            else
            {
                this->set_status("301");
                this->set_bool_is_file("false");
            }
        }
        else
        {
            this->set_bool_is_file("true");
            exetention_cgi(serv->get_request().get_header_req().get_full_path());
        }
    }
    else
    {
        this->set_bool_is_file("true");
        this->set_status("404");
    }
}


bool    const &response::get_bool_redec() const
{
    return this->bool_redec;
}

void    response::set_bool_redec(std::string l)
{
    if(!l.compare("false"))
        this->bool_redec = false;
    else
         this->bool_redec = true;
}

void    response::check_error(Servdata *serv)
{
    struct stat s;
    if(!serv->get_request().get_header_req().get_method().compare("POST") && serv->get_request().get_header_req().get_bool_encoding() == true && serv->get_request().get_header_req().get_transfer_encoding().compare("chunked"))
        this->set_status("501");
    else if(!serv->get_request().get_header_req().get_method().compare("POST") && ((serv->get_request().get_header_req().get_bool_encoding() == false && serv->get_request().get_header_req().get_bool_length() == false) ||  (serv->get_request().get_header_req().get_bool_encoding() == true && serv->get_request().get_header_req().get_bool_length() == true)))
        this->set_status("400");
    else if(!serv->get_request().get_header_req().get_method().compare("POST") && serv->get_request().get_header_req().get_bool_length() == true && serv->get_request().get_header_req().get_bool_type() == false)
        this->set_status("400");
    else if(serv->get_request().get_header_req().get_path().length() > 2048)
        this->set_status("414");
    else if(serv->get_request().get_header_req().get_content_length() > atoi(serv->get_limit().c_str()))
        this->set_status("413");
    else if(serv->get_meth() == false)
        this->set_status("405");
    else if(serv->get_request().get_header_req().get_version().compare("HTTP/1.1") != 0)
        this->set_status("505");
    else if(access(serv->get_request().get_header_req().get_full_path().c_str(), F_OK) == -1)
    {
        this->set_status("404");
    }
    else
        this->set_status("200");

    std::map<std::string, Locationdata> ite = serv->get_loc();
    if(!serv->get_request().get_header_req().get_method().compare("POST") && !this->get_status().compare("200"))
    {
        if(!ite[serv->get_request().get_best_location()].get_upload().empty())
        {
            this->set_status("201");
        }
        else if(stat(serv->get_request().get_header_req().get_full_path().c_str(), &s) != 0)
        {
            this->set_status("404");
        }
        else if(ite[serv->get_request().get_best_location()].get_upload().empty())
        {
            ft_get(serv);
            if(serv->get_res().get_support_cgi() == false)
                this->set_status("500");
        }
    }
    if(!serv->get_request().get_header_req().get_method().compare("GET") && !this->get_status().compare("200"))
        ft_get(serv);
    if(!serv->get_request().get_header_req().get_method().compare("DELETE") && !this->get_status().compare("200"))
    {
        ft_delete(serv->get_request().get_header_req().get_full_path());
    }
    if(!ite[serv->get_request().get_best_location()].get_redirect().empty())
    {
        this->set_status("301");
        this->set_bool_is_file("false");
        this->set_bool_redec("true");
    }
    if(!serv->get_request().get_header_req().get_path().empty())
    {
        if(serv->get_request().get_header_req().check_uri_char() == false)
        {
            this->set_status("400");
        }
    }
    this->set_res_status(serv->get_request(), serv->get_error());
    this->set_extension_get();

}