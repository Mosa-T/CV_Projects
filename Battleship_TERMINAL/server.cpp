#include "server.h"
#include <stdio.h>
#include "packets.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <sys/mman.h>
#define MAX_SHAREABLE 100

int add_to_port = 1;
msg_notify_t notify_msg;
msg_ack_t msg_ack;
int sockList[2] = {-1,-1};
int size_fs = 0;
msg_dirhdr_t turn_holder;
int first_round = 0;
int num_players;
bool flag_threads_created = false;
int m_count = 1;
void error(const char* str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void* connection_handler(void* socket_desc)
{
	msg_dirhdr_t handler;
	int sock;
	int other_sock;
	msg_ack_t turn_ack;
	while(!flag_threads_created){}
	sock = *(int*)socket_desc;
	other_sock = *((int*)socket_desc+1);
	printf("\nsockList[0] = %d, sockList[1] = %d\n",sock,other_sock);
	printf("\nFirst turn setting\n");
	turn_holder.m_type = MSG_DIRHDR;
	printf("\nturn_holder= %d\n",turn_holder.m_count);
	turn_holder.m_count = 0;
	printf("\nturn_holder2= %d\n",turn_holder.m_count);
	
	/////////
	msg_ack_t ackk;
	if(recv(sock,&ackk,sizeof(ackk),0)<0){
			error("\nServer - Error: couldn't receive turn msg\n");
	}
	ackk.m_type = MSG_ACK;
	if(write(sock, &turn_holder,sizeof(turn_holder)) < 0){ 
		error("\naaaaa1\n");
	}
	if(recv(other_sock,&ackk,sizeof(ackk),0)<0){
			error("\nServer - Error: couldn't receive turn msg\n");
	}
	ackk.m_type = MSG_ACK;
	if(write(other_sock, &turn_holder,sizeof(turn_holder)) < 0){ 
		error("\naaaaa1\n");
	}
	////////////
	if(write(sock, &turn_holder,sizeof(turn_holder)) < 0){ 
		error("\naaaaa1\n");
	}
	turn_holder.m_count = 1;
	if(write(other_sock, &turn_holder,sizeof(turn_holder)) < 0){ 
		error("\naaaaa1\n");
	}
	int read_size;
	while ((read_size = recv(sock, &notify_msg, sizeof(notify_msg), 0)) > 0)
	{
		printf("\nServer - receiving msg of sorts from socket[%d]\n",sock);
		switch (notify_msg.m_type)
		{
		case MSG_NOTIFY:{
			printf("\n1\n");
			printf("\nServer - notify : receiving MSG_NOTIFY\n");
			msg_ack.m_type = MSG_ACK;
			printf("\nServer - notify: sending MSG_ACK\n");
			printf("\nCoordinates: %s\n",notify_msg.m_name);
			if (write(sock, &msg_ack, sizeof(msg_ack)) < 0){ 
				error("\nServer - MSG_ACK failed\n");
			}
			msg_notify_t notify_other;
			strcpy(notify_other.m_name,notify_msg.m_name);
			notify_other.m_type = MSG_NOTIFY;
			printf("\nServer - Send Coordinates to other socket[%d] \n",other_sock);
			if(write(other_sock, &notify_other,sizeof(notify_other)) < 0){
				error("\naaaaa\n");
			}
			printf("\nServer - waiting on other_sock[%d] hit or miss\n",other_sock); 
			if(recv(other_sock,&handler,sizeof(handler),0) < 0){
				error("\nAAAAAA\n");
				}
				printf("\nServer - received if hit or miss\n");
				printf("\nServer - send if hit or miss to attacking socket\n");
				if(write(sock, &handler,sizeof(handler)) < 0){
					error("aaaaa\n");
				}

		}
		break;
			
		case MSG_DIRREQ:{
			printf("\nMSG_DIRREQ\n");
		}
		break;

		case MSG_SHUTDOWN:{
			printf("\n3\n");
			printf("\nshutting down server\n");
			close(sock);
			exit(1);
		}
		break;
		
		case MSG_ACK:{
			printf("\nServer - waiting to ack both clients\n");
			turn_ack.m_type = MSG_ACK;
			if(write(sock, &turn_ack,sizeof(turn_ack)) < 0){
					error("aaaaa\n");
			}
			if(write(other_sock, &turn_ack,sizeof(turn_ack)) < 0){
					error("aaaaa\n");
			}
			printf("\n4\n");
			printf("\nACKED CLIENTS\n");
		}
		break;

		case MSG_TURN:{
			printf("\n5\n");
			printf("\nTurn setting\n");
			printf("\nServer- sending turn update to sockets\n");
			if(sockList[0] == sock){
				turn_holder.m_count = 1;
				printf("\nServer - sending socket[%d] turn value %d\n",sock,turn_holder.m_count);
				if(write(sock, &turn_holder,sizeof(turn_holder)) < 0){
					error("\naaaaa1\n");
				}
				if(recv(sock,&turn_ack,sizeof(turn_ack),0)<0){
					error("\nServer - Error: couldn't receive turn msg");
				}
				printf("\nServer - received turn_ack from socket[%d]\n",sock);
				printf("\nServer- sending turn update to other_sock\n");
				turn_holder.m_count = 0;
				printf("\nServer - sending socket[%d] turn value %d\n",other_sock,turn_holder.m_count);
				if(write(other_sock, &turn_holder,sizeof(turn_holder)) < 0){
					error("\naaaaa1\n");
				}
				if(recv(other_sock,&turn_ack,sizeof(turn_ack),0)<0){
					error("\nServer - Error: couldn't receive turn msg");
				}
				other_sock = *(int*)socket_desc;
				sock = *((int*)socket_desc+1);
				break;
			} else if(sockList[1] == sock){
				turn_holder.m_count = 1;
				printf("\nServer - sending socket[%d] turn value %d\n",sock,turn_holder.m_count);
				if(write(sock, &turn_holder,sizeof(turn_holder)) < 0){
					error("\naaaaa1\n");
				}
				if(recv(sock,&turn_ack,sizeof(turn_ack),0)<0){
					error("\nServer - Error: couldn't receive turn msg");
				}
				printf("\nServer- sending turn update to other_sock\n");
				turn_holder.m_count = 0;
				printf("\nServer - sending socket[%d] turn value %d\n",other_sock,turn_holder.m_count);
				if(write(other_sock, &turn_holder,sizeof(turn_holder)) < 0){
					error("\naaaaa1\n");
				}
				if(recv(other_sock,&turn_ack,sizeof(turn_ack),0)<0){
					error("\nServer - Error: couldn't receive turn msg\n");
				}
				sock = *(int*)socket_desc;
				other_sock = *((int*)socket_desc+1);
				break;
			}
			printf("\nWE FUCKED UP\n"); 
		}
		break;
		
		default:{
			printf("\nError! m_type is not correct %d in socket[%d]\n",notify_msg.m_type,sock);
		}
		break;
		}
	}
	if (read_size == 0)
	{
		puts("\nServer - notify: Client disconnected\n");
	}
	return 0;
}





int main(int argc, char* argv[])
{
	num_players = 0;
	turn_holder.m_count = 1;
	pthread_t thread_id;
	int opt = 1;
	struct sockaddr_in s_info;
	struct sockaddr_in cli_addr;
	int   sock_fd, client_sock;
	int sizeC;
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("socket");
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
		error("Server - setsockopt failed");
	printf("\nServer - server: opening socket on 127.0.0.1:%d\n", P_SRV_PORT);
	s_info.sin_family = AF_INET;
	s_info.sin_port = P_SRV_PORT-3;
	s_info.sin_addr.s_addr = INADDR_ANY;
	if (bind(sock_fd, (struct sockaddr*) &s_info, sizeof(s_info)) < 0)
		error("Server - binding failed");
	printf("\nbind successful \n");
	listen(sock_fd, 20);
	sizeC = sizeof(struct sockaddr_in);
	while ((client_sock = accept(sock_fd, (struct sockaddr*) & cli_addr, (socklen_t*)&sizeC)))
	{
		if (flag_threads_created == true){
			continue;
		}
		sockList[num_players] = client_sock;
		printf("\nServer - waiting on second client\n");
		if(num_players == 1){
			printf("\n Server - second client connected.\n");
		} else {
			num_players++;
			continue;
			}
		if (pthread_create(&thread_id, NULL, connection_handler, (void*)&sockList) < 0)
		{
			error("\nServer - could not create thread_0\n");
		}
		if (sockList[0] < 0 || sockList[1] < 0)
		{
			error("\nServer - accept failed\n");
		}
		flag_threads_created = true;
		//break;
	}
	printf("\n Server - reached end\n");
	//connection_handler((void*)&sockList[0]);
	printf("\n Server - reached end2\n");
	close(sock_fd);
	return 0;
}

