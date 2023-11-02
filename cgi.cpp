/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:39:29 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 01:24:49 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi.hpp"
#include "response.hpp"

void    Cgi::set_env(std::string port, request *req)
{
    std::string str;
    if(!req->get_header_req().get_method().compare("POST"))
        this->env = new char *[13];
    else
        this->env = new char *[11];
    str = "PATH_INFO=" + path;
    this->env[0] = new char[str.size() + 1];
    strcpy(this->env[0], str.c_str());
    str.clear();
    str = "SERVER_PORT=" + port;
    this->env[1] = new char[str.size() + 1];
    strcpy(this->env[1], str.c_str());
    str.clear();
    str = "REQUEST_METHOD=" + req->get_header_req().get_method();
    this->env[2] = new char[str.size() + 1];
    strcpy(this->env[2], str.c_str());
    str.clear();
    str = "SCRIPT_FILENAME=" + path;
    this->env[3] = new char[str.size() + 1];
    strcpy(this->env[3], str.c_str());
    str.clear();
    if(!path.substr(path.find_last_of(".")).compare(".php"))
    {
        str = "SCRIPT_NAME=" + path;
        this->env[4] = new char[str.size() + 1];
        strcpy(this->env[4], str.c_str());
        str.clear();
    }
    else
    {
        str = "SCRIPT_NAME=" + this->exec_script;
        this->env[4] = new char[str.size() + 1];
        strcpy(this->env[4], str.c_str());
        str.clear();
    }
    str = "REDIRECT_STATUS=200";
    this->env[5] = new char[str.size() + 1];
    strcpy(this->env[5], str.c_str());
    str.clear();
    str = "REMOTE_ADDR=127.0.0.1";
    this->env[6] = new char[str.size() + 1];
    strcpy(this->env[6], str.c_str());
    str.clear();
    str = "HTTP_COOKIE=" + req->get_header_req().get_cookie();
    this->env[7] = new char[str.size() + 1];
    strcpy(this->env[7], str.c_str());
    str.clear();
    str = "HTTP_USER_AGENT=" + req->get_header_req().get_User_agent();
    this->env[8] = new char[str.size() + 1];
    strcpy(this->env[8], str.c_str());
    str.clear();
    str = "HTTP_HOST=localhost";
    this->env[9] = new char[str.size() + 1];
    strcpy(this->env[9], str.c_str());
    str.clear();
    str = "QUERY_STRING=";
    if (req->get_header_req().get_query().empty() && !req->get_header_req().get_method().compare("POST") && !req->get_header_req().get_content_type().compare(" application/x-www-form-urlencoded\r"))
        this->save_query = this->env_query;
    else if (!req->get_header_req().get_query().empty() && req->get_header_req().get_query().find('&') != std::string::npos && !req->get_header_req().get_method().compare("POST"))
    {
        str += '?';
        this->save_query = req->get_header_req().get_query();
    }
    else
       this->save_query = req->get_header_req().get_query();
    str += this->save_query;
    this->env[10] = new char[str.size() + 1];
    strcpy(this->env[10], str.c_str());
    str.clear();
    if(!req->get_header_req().get_method().compare("POST"))
    {
        std::string type = trim(req->get_header_req().get_content_type());
        str = "CONTENT_TYPE=" + type;
        this->env[11] = new char[str.size() + 1];
        strcpy(this->env[11], str.c_str());
        str.clear();
        std::stringstream ss;
        ss << (req->get_header_req().get_content_length());
        str = "CONTENT_LENGTH=" + ss.str();
        this->env[12] = new char[str.size() + 1];
        strcpy(this->env[12], str.c_str());
        str.clear();
        this->env[13] = NULL;
    }
    else
        this->env[11] = NULL;
}

void   Cgi::set_map_cgi(std::map <std::string, std::string> serv_cgi)
{
    this->map_cgi = serv_cgi;
}

void Cgi::sup_cgi_conf(std::string l)
{
    std::map <std::string, std::string>::const_iterator it = this->map_cgi.begin();
    std::map <std::string, std::string>::const_iterator ite = this->map_cgi.end();
    for(; it != ite; ++it)
    {
        if(!it->first.compare(l))
        {
            this->set_exec_script(it->second);
            return ;
        }
    }
    this->exec_script = "";
}

void   Cgi::set_args(request *reqs, response *resps)
{
    this->args = new char*[3];
    if(!resps->get_new_file().empty())
    {
        this->path = resps->get_new_file();
    }
    else
    {
        this->path = reqs->get_header_req().get_full_path();
    }
    int pos = this->path.find_last_of("."); 
    this->ex = this->path.substr(pos);
    if(!this->ex.compare(".php"))
    {
        this->sup_cgi_conf("php");
        if(!this->exec_script.empty())
        {
            this->args[0] = new char[this->exec_script.size() + 1];
            strcpy(this->args[0], this->exec_script.c_str());
        }
        else
        {
            resps->set_support_cgi("false");
            return ;
        }
    }
    else if(!this->ex.compare(".py"))
    {
        this->sup_cgi_conf("python");
        if(!this->exec_script.empty())
        {
            this->args[0] = new char[this->exec_script.size() + 1];
            strcpy(this->args[0], this->exec_script.c_str());
        }
        else
        {
            resps->set_support_cgi("false");
            return ;
        }
    }
    this->args[1] = new char[this->path.size() + 1];
    strcpy(this->args[1], this->path.c_str());
    this->args[2] = NULL;
}

std::string Cgi::query_post()
{
    this->fd_post = open("./cgi-bin/body.txt", O_RDONLY, 0777);
    char buf_query[1024];
    bzero(buf_query, 1024);
    std::string ap = "";
    if(this->fd_post < 0)
        perror("file query");
    while(int n = read(this->fd_post, buf_query, sizeof(buf_query)) > 0)
    {
        ap.append(buf_query);
    }
    return(ap);
}

void    Cgi::set_env_query(std::string l)
{
    this->env_query = l;
}

void    Cgi::set_cgi_tmp_name(std::string l)
{
    this->cgi_tmp_name = l;
}

void    Cgi::set_exec_script(std::string l)
{
    this->exec_script = l;
}

std::string const   &Cgi::get_cgi_tmp_name() const
{
    return this->cgi_tmp_name;
}

std::string const   &Cgi::get_ex() const
{
    return this->ex;
}

std::string const   &Cgi::get_exec_script() const
{
    return this->exec_script;
}

int const   &Cgi::get_cgi_tmp_fd() const
{
    return this->cgi_tmp_fd;
}

void    Cgi::set_cgi_tmp_fd_bool(std::string l)
{
    if(!l.compare("true"))
        this->cgi_tmp_fd_bool = true;
    else
        this->cgi_tmp_fd_bool = false;
}

bool    const &Cgi::get_cgi_tmp_fd_bool() const
{
    return this->cgi_tmp_fd_bool;
}

void    Cgi::to_fork(request *req, response *res)
{
    this->pid = fork();
    if(this->pid == 0)
    {
        this->cgi_tmp_fd = open(this->cgi_tmp_name.c_str(), O_CREAT | O_RDWR| O_TRUNC, 0777);
        if(!req->get_header_req().get_method().compare("POST"))
        {
            this->fd_post = open("./cgi-bin/body.txt", O_RDONLY, 0777);
            dup2(this->fd_post, 0);
        }
        dup2(this->cgi_tmp_fd, 1);
        if(execve(this->args[0], this->args, this->env) == -1)
            res->set_status("500");
    }
}

void    Cgi::cgi(std::string port, request *req, response *res)
{
    if(res->get_first_cgi() == true)
    {
        this->set_args(req, res);
        if(!req->get_header_req().get_method().compare("POST"))
            this->set_env_query(this->query_post());
        this->set_env(port, req);
       
        if(this->cgi_tmp_fd < 0)
            perror("open ");
        res->set_first_cgi("false");
        set_cgi_tmp_name("/tmp/1.txt");
        this->to_fork(req, res);
    }
    int status = 0;
    int result = waitpid(this->pid, &status, WNOHANG);
    if(result > 0)
    {
        res->set_support_cgi("false");
        res->set_cgi_true("true");
        res->set_first_cgi("true");
        
    }
}