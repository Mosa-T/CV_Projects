#include <stdio.h>
#include "p2p.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<pthread.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_SHAREABLE 100

int add_to_port = 1;
msg_notify_t notify_msg;
msg_ack_t msg_ack;
file_ent_t *file_shared;
int size_fs=0;

void error( char *str )
{
    perror( str );
    exit( EXIT_FAILURE );
}

void *connection_handler(void *socket_desc)
{
    msg_dirhdr_t handler;
    int sock = *(int*)socket_desc;
    int read_size;
    while( (read_size = read(sock , &notify_msg , sizeof(notify_msg))) > 0 )
    {
        switch(notify_msg.m_type)
                {
                    case MSG_NOTIFY:
                        printf("Server - notify : receiving MSG_NOTIFY\n");
                        if(notify_msg.m_port == 0)
                        {
							
                            printf("Server - notify: assigned port %d\n",P_SRV_PORT + add_to_port);
                            notify_msg.m_port = P_SRV_PORT + add_to_port;
                            msg_ack.m_type =MSG_ACK;
                            msg_ack.m_port = P_SRV_PORT + add_to_port;
                            printf("Server - notify: sending MSG_ACK\n");
                            if(size_fs ==0)
                            {
                                file_shared = (file_ent_t *)malloc(sizeof(file_ent_t));
                                strcpy(file_shared[0].fe_name,notify_msg.m_name);            
                                file_shared[0].fe_addr = notify_msg.m_addr;
                                file_shared[0].fe_port = notify_msg.m_port;
                                size_fs++;
                            }
                            else {
                                file_ent_t *temp_new;
                                size_fs++;
                                temp_new =(file_ent_t *)realloc(file_shared,sizeof(file_ent_t)*size_fs);
                                if(!temp_new)
                                    error("Server - realloc failed");
                                file_shared = temp_new;
                                strcpy(file_shared[size_fs -1].fe_name,notify_msg.m_name);
                                file_shared[size_fs -1].fe_addr = notify_msg.m_addr;
                                file_shared[size_fs -1].fe_port = notify_msg.m_port;   
                            }
                            if (write(sock,&msg_ack,sizeof(msg_ack)) <0 )
                                error("Server - MSG_ACK failed\n");
                        }
                        add_to_port++;
                    break;


                    case MSG_DIRREQ: 

                        handler.m_count= size_fs;
                        handler.m_type = MSG_DIRHDR; 
                        printf("Server - dirreq: Receiving MSG_DIRREQ\n"); 
                        write(sock,&handler,sizeof(handler));
                        int i; 
                        file_ent_t temp;
                        printf("Server - dirreq: sending MSG_DIRHDR with count=%d\n",size_fs);
                        for( i = 0 ; i < size_fs; i++)
                        {
                            strcpy(temp.fe_name, file_shared[i].fe_name);              
                            temp.fe_addr = file_shared[i].fe_addr;
                            temp.fe_port = file_shared[i].fe_port;
                            write(sock,&temp,sizeof(temp));
                        }
                    break;

                    case MSG_SHUTDOWN: 
                        {
						printf("\nshutting down server\n");
							close(sock);
								exit(1);
						}
                    break;
                }
    }
    if(read_size == 0)
    {
        puts("Server - notify: Client disconnected");
    }
    return 0;
} 




int main(int argc,char *argv[])
{
    pthread_t thread_id;
    struct sockaddr_in s_info;
    struct sockaddr_in cli_addr;
    int   sock_fd,client_sock;
    int sizeC;
    if( ( sock_fd = socket( AF_INET, SOCK_STREAM , 0 ) ) < 0 )
        error( "socket" );
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
		error("Server - setsockopt failed");
    printf("\nServer - server: opening socket on 127.0.0.1:%d\n",P_SRV_PORT);
    s_info.sin_family = AF_INET;
    s_info.sin_port = P_SRV_PORT;
    s_info.sin_addr.s_addr = INADDR_ANY;
    if( bind( sock_fd, (struct sockaddr *) &s_info, sizeof( s_info ) ) < 0 )
        error( "Server - binding failed" );
    listen(sock_fd , 20);
    sizeC = sizeof(struct sockaddr_in);
    pthread_t sniffer_thread;
    while(client_sock = accept(sock_fd,(struct sockaddr *) &cli_addr,(socklen_t*) &sizeC))
    {
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
            {
                error("Server - could not create thread");
            }
        if (client_sock < 0)
        {
            error("Server - accept failed");
        }
    }
    close( sock_fd );
    return 0;
}