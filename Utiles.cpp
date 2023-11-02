/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utiles.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-mach <iel-mach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:26:05 by iel-mach          #+#    #+#             */
/*   Updated: 2023/05/14 01:01:26 by iel-mach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utiles.hpp"

std::string get_file(const std::string &av)
{
    std::ifstream fileconf;
    std::string file_name = av;
    size_t find = file_name.find_last_of(".");
    std::string str;
    if (find == std::string::npos)
    {
        std::cout << "Error: The file has no extension." << std::endl;
        exit(0);
    }
    std::string extension = file_name.substr(find + 1);
    if (extension.compare("conf"))
    {
        std::cout << "Error: Extension invalide." << std::endl;
        exit(0);
    }
    fileconf.open(file_name, std::ifstream::in);
    if (fileconf.fail())
    {
        std::cout << "Error: Check file." << std::endl;
        exit(0);
    }
    std::string lop;
    while(getline(fileconf, str))
    {
        lop += (str + "\n");
    }
    return lop;
}


void    check_syntax(std::string const &lop)
{
    int x = 0;
    int is = 0;
    int isa = 0;
    int issa = 0;
    int ia = 0;
    while (lop[x])
    {
        if (lop[x] == '{')
            is++;
        if (lop[x] == '}')
            isa++;
        if (lop[x] == '[')
            issa++;
        if (lop[x] == ']')
            ia++;
        x++;
    }
    if ((is != isa) || (issa != ia))
    {
        std::cout << "Syntax Error\n";
        exit(0);
    }
}

std::vector<std::vector<std::string> >  ret_vector(const std::string &av)
{
    std::string lop = get_file(av);
    check_syntax(lop);
    std::stringstream ss(lop);
    std::vector<std::string> result;
    std::string token;
    while (std::getline(ss, token, '\n')) {
        if (token != "") {
            result.push_back(token);
        }
    }
    std::vector<std::string>::iterator it = result.begin();
    std::vector<std::string>::iterator ite = result.end();
    std::vector<std::string> sub_vec;
    std::vector<std::vector<std::string> > r;
    for (; it != ite; it++)
    {
        std::stringstream ss(*it);
        while (std::getline(ss, token, '=')) {
            token = trim(token);
            sub_vec.push_back(token);
        }
        r.push_back(sub_vec);
        sub_vec.clear();
    }
    return r;
}

std::vector<Servdata> parsing(std::vector<std::vector<std::string> > r, int s)
{
    std::vector<Servdata> servs(s);
    unsigned long l = 0;
    unsigned long j = l;
    std::string a;
    for (int i = 0; i < s; i++)
    {
        int size = 0;
        Locationdata m;
        for (; j <= (r.size() - 1); j++)
        {
            if (size > 1)
            {
                servs[i].set_loc(a, m);
                m.init_attribt();
                size = 0;
            }
            if (j != l && r[j][0].compare("server {") == 0)
            {
                break;
            }
            if (r[j][0].compare("port") == 0)
                servs[i].set_port(r[j][1]);
            if (r[j][0].compare("host") == 0)
                servs[i].set_host(r[j][1]);
            if (r[j][0].compare("server_name") == 0)
                servs[i].set_name(r[j][1]);
            if (r[j][0].compare("body_size_limit") == 0)
                servs[i].set_limit(r[j][1]);
            if (r[j][0].compare("error_page") == 0)
                servs[i].set_error(r[j][1]);
            if (r[j][0].compare("cgi") == 0)
            {
                std::stringstream ss(r[j][1]);
                std::string key, value;
                if (ss >> key >> value)
                    servs[i].set_cgi(key, value);
            }
            if (r[j][0].compare("location") == 0)
            {
                std::stringstream ss(r[j][1]);
                ss >> a;
                size++;
            }
            if (r[j][0].compare("method") == 0)
            {
                std::string token;
                std::stringstream ss(r[j][1]);
                while (std::getline(ss, token, ' '))
                    m.set_meth(token);
            }
            if (r[j][0].compare("redirect") == 0)
            {
                m.set_redirect(r[j][1]);
            }
            if (r[j][0].compare("root") == 0)
            {
                m.set_root(r[j][1]);
            }
            if (r[j][0].compare("autoindex") == 0)
            {       
                m.set_autoindex(r[j][1]);
            }
            if (r[j][0].compare("default") == 0)
            {
                m.set_default(r[j][1]);
            }
            if (r[j][0].compare("upload") == 0)
            {
                m.set_upload(r[j][1]);
            }
            if (r[j][0].compare("]") == 0)
                size++;
        }
        l = j;
    }
    return (servs);
}

int count_server(std::vector<std::vector<std::string> > r)
{
    int s = 0;
    for (std::vector<std::vector<std::string> >::iterator it = r.begin(); it != r.end(); ++it)
    {
        for (std::vector<std::string>::iterator ite = it->begin(); ite != it->end(); ++ite)
        {
            if ((*ite).compare("server {") == 0)
                s++;
        }
    }
    return s;
}

int create_socket(int po)
{
	int server_fd = 0;
    int optval = 1;
    struct sockaddr_in address;
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("In socket");
		exit(EXIT_FAILURE);
	}
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    fcntl(server_fd, F_SETFL, O_NONBLOCK);
    address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(po);
    int bind_result = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
	if (bind_result < 0)
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 1000) < 0)
    {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	return server_fd;
}

std::vector<std::string> pars_header(char *buffer)
{
    std::vector<std::string> req;
    std::stringstream ss(buffer);
    std::string meth;
    std::string loca;
    std::string v;
    getline(ss, meth, ' ');
    req.push_back(meth);
    getline(ss, loca, ' ');
    req.push_back(loca);
    getline(ss, v, '\n');
    req.push_back(v);
    return(req);
    
}


int strleng(std::string s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\r' && s[i + 1] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

bool check_uri_char (std::string path)
{
    std::string char_uri = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 ._~:/?#[]@!$&'()*+,;=%";
    for (std::size_t i = 0; i < path.length(); i++) {
        if (char_uri.find(path[i]) != std::string::npos)
            return true;
    }
    return false;
}

std::string find_file_name(std::string boundary)
{
    int pos_filename = boundary.find("filename=");
    pos_filename += 10;
    std::string filename = "";
    while(boundary[pos_filename] != '"')
    {
        filename += boundary[pos_filename];
        pos_filename++;
    }
    return(filename);
}

int remove_file(const char* file_name)
{
    int fd_file;
    std::ifstream file(file_name);
    if (access(file_name, F_OK) != -1)
    {
        std::ofstream out(file_name, std::ios::out | std::ios::trunc);
        out.close();
        fd_file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
        return fd_file;
    }
    else
    {
       fd_file = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0777);
       return fd_file;
    }   
}

int check_fds(int fd)
{
    if(fd == 3)
        return(0);
    else if(fd == 4)
        return(1);
    else if(fd == 5)
        return(2);
    return(-1);
}


void change_socket(std::map<int, Servdata> &fds_server, int fileD, int newSocket)
{
    Servdata tmp = fds_server[fileD];
    fds_server.insert(std::make_pair(newSocket, tmp));
    fds_server[newSocket].set_fd_req(newSocket);
}

std::map<int, Servdata> ft_fds(std::vector<Servdata> &servers)
{
    std::map<int, Servdata> fds;
    for (size_t i = 0; i < servers.size(); i++)
        fds.insert(std::make_pair(i, servers[i]));
    return fds;
}

void loop(_socket sock)
{
    int new_socket;
    std::map<int, Servdata> serv = sock.get_serv_fds();
    int tmp = 1;
	while (1)
	{
        sock.set_masters();
        int d = sock.selec();
		if (d == -1)
			exit(0);
		for (int fd = 0; fd <= sock.get_max_fds(); fd++)
		{
			if (sock.fd_iset(fd, "read") || sock.fd_iset(fd, "write"))
			{
                if (sock.fd_iset(fd, "read"))
                {
                    if (sock.get_arr(fd) == 0)
                    {
                        
                        new_socket = accept(fd, NULL, NULL);
                        fcntl(new_socket, F_SETFL, O_NONBLOCK);
                        setsockopt(new_socket, SOL_SOCKET, SO_NOSIGPIPE, &tmp, sizeof(tmp));
                        sock.set_r(new_socket);
                        sock.set_arr_one(new_socket);
                        Servdata tmp = serv[fd];
                        serv.insert(std::make_pair(new_socket, tmp));
                        serv[new_socket].set_fd_req(new_socket);
                        if (new_socket > sock.get_max_fds())
                            sock.set_max_fds(new_socket);
                        continue;
                    }
                    else
                    {
                        serv[fd].read_req();
                        if (serv[fd].get_bool_error() == true)
                        {
                            perror("read: ");
                            sock.clear_fd_r(fd);
                            close(fd);
                        }
                        else if(serv[fd].get_req_done() == true)
                        {
                            serv[fd].set_res_done();
                            sock.clear_fd_r(fd);
                            sock.set_w(fd);
                        }
                    }
                }
                else if (sock.fd_iset(fd, "write"))
                {
                    if(serv[fd].get_res().get_support_cgi() == true)
                        serv[fd].check_cgi();
                    else
                        serv[fd].start_response();
                    if(serv[fd].get_res_done() == true)
                    {
                        serv[fd].set_res_done();
                        sock.clear_fd_w(fd);
                        sock.clear_fd_m_w(fd);
                        sock.clear_fd_r(fd);
                        sock.clear_fd_m_r(fd);
                        serv.erase(fd);
                        close(fd);
                
                    }
                }
            }
		}
	}
}