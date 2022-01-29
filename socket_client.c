#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>

void die(char const *err_msg)
{
    perror(err_msg);
    exit(EXIT_FAILURE);
}

int create_tcp_ip4_socket(void)
{
    int df = socket(AF_INET, SOCK_STREAM, AF_UNSPEC);
    if(df < 0) die("create_tcp_ip4_socket");
    return df;
}

void print_file(int fd)
{
    size_t buffer_size = 1023;
    char buffer[buffer_size + 1];
    ssize_t read_ret;

    while((read_ret = read(fd, buffer, buffer_size*sizeof(buffer[0]))) > 0)
    {
        if(read_ret < 0) die("print_file read");
        buffer[read_ret] = '\0';
        printf("%s", buffer);
    }

    return;
}

int main(int argc, char *argv[])
{
    int socket_fd = create_tcp_ip4_socket();

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(13);
    char *ip_address = "129.6.15.28";

    if(argc > 1) ip_address = argv[1];
    printf("ip addres = %s", ip_address);

    if(inet_pton(AF_INET, ip_address, &server_addr.sin_addr) <= 0)
        die("main inet_pton");
    
    if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        die("main connect");

    print_file(socket_fd);

    if(close(socket_fd) < 0)
        die("main close");
}