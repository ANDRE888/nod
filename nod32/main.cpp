#include <iostream>    //cout
#include <stdio.h> //printf
#include <string.h>    //strlen
#include <string>  //string
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <netdb.h> //hostent
#include <algorithm>
#include <unistd.h>

#include <stdlib.h>
#include <vector>
#include <fstream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <vector>
#include <fstream>

#include <algorithm>
#include <regex>
#include <openssl/md5.h> // библиотеки подключены 32 версией
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#define default_http_port 80

using namespace std;
using namespace boost::asio;
io_service service;
//----------------------------------------------------------

unsigned long GetTickCount()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return (tv.tv_sec*1000+tv.tv_usec/1000);
}

#define default_http_port 80


/**
    TCP Client class
*/
class tcp_client
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    tcp_client();
    bool conn(string, int);
    bool send_data(string data);
    string receive(long);
};


tcp_client::tcp_client()
{
    sock = -1;
    port = 0;
    address = "";
}
/**
    Connect to a host on a certain port number
*/
bool tcp_client::conn(string address , int port)
{
    //create socket if it is not already created
    if(sock == -1)
    {
        //Create socket
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1)
        {
            perror("Could not create socket");
        }

        cout<<"Socket created\n";
    }
    else    {   /* OK , nothing */  }

    //setup address structure
    if(inet_addr(address.c_str()) == -1)
    {
        struct hostent *he;
        struct in_addr **addr_list;

        //resolve the hostname, its not an ip address
        if ( (he = gethostbyname( address.c_str() ) ) == NULL)
        {
            //gethostbyname failed
            herror("gethostbyname");
            cout<<"Failed to resolve hostname\n";

            return false;
        }

        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
        addr_list = (struct in_addr **) he->h_addr_list;

        for(int i = 0; addr_list[i] != NULL; i++)
        {
            //strcpy(ip , inet_ntoa(*addr_list[i]) );
            server.sin_addr = *addr_list[i];

            cout<<address<<" resolved to "<<inet_ntoa(*addr_list[i])<<endl;

            break;
        }
    }

    //plain ip address
    else
    {
        server.sin_addr.s_addr = inet_addr( address.c_str() );
    }

    server.sin_family = AF_INET;
    server.sin_port = htons( port );

    //Connect to remote server
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("connect failed. Error");
        return 1;
    }

    // cout<<"Connected\n";
    return true;
}

/**
    Send data to the connected host
*/
bool tcp_client::send_data(string data)
{
    //Send some data
    if( send(sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
    {
        perror("Send failed : ");
        return false;
    }
    cout<<"Data send\n";

    return true;
}

/**
    Receive data from the connected host
*/
string tcp_client::receive(long int size=650000)
{
    char buffer[size];
    string reply;

    //Receive a reply from the server
    if( recv(sock , buffer , sizeof(buffer) , 0) < 0)
    {
        puts("recv failed");
    }

    reply = buffer;
    return reply;
}


inline int Sleep(long int time_sleep)
{
    time_sleep=(time_sleep*1000);
    usleep(time_sleep);
    return 0;
}

int write_data_to_log(int type_write, string filename, string* data_to_write)
{
    //type_write 1-дозапись;2-Удаление содержимого и запись с начала
    ofstream ofs;

    switch(type_write)
    {
    case 1://дозапись в файл
        ofs.open(filename,ios_base::app);
        ofs << *data_to_write << endl;
        break;
    case 2://перезапись файла
        ofs.open(filename,ios_base::out);
        ofs << *data_to_write << endl;
        break;
    default://Неверный тип записи в файл
        cout<< "Error type_write"<<endl;
        break;
    }

    ofs.close();
    return 0;
}

int http_head_content_size (string header, int type_content)
{
    // 1 content-lenght
    // 2 chunke
    if(type_content==1)
    {
        // поиск контент
    }
    else if(type_content==2)
    {
        // content 2
    }

    else
    {
        return -1; // return error
    }

    return 0;//content_size;
}

int http_header_status(string header)
{
    cout << "Zawel v func header status" << endl;



    return 0;
}


int main()
{
    cout << "Loading test page Google" << endl;
    //usleep(1000*1000);
    tcp_client c;

    c.conn("google.ru",default_http_port);
    c.send_data("GET / HTTP/1.1\r\n\r\n");

    //receive and echo reply
    cout<<"----------------------------\n\n";
    string recive_page;
    recive_page = c.receive(65000);
    cout << recive_page << endl;
    http_header_status(recive_page);
    //cout<<c.receive(10204);


    getchar();
    //usleep(1000*1000);
    return 0;
}

