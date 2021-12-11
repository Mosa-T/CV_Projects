#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "p2p.h"
#include <pthread.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "Battleship.h"
#include <iostream>
void error(char* str);
void turn_handle(int sock);
void m_shutdown(int sock_fd);


void error(const char* str)
{
	perror(str);
	exit(EXIT_FAILURE);
}



void m_shutdown(int sock_fd) {
	printf("\n We here now boy\n");
	file_ent_t file_shared;
	msg_dirhdr_t dir_holder;
	msg_dirreq_t dir_req;
	msg_shutdown_t shtdwn_msg;
	shtdwn_msg.m_type = MSG_SHUTDOWN;
	dir_req.m_type = MSG_DIRREQ;
	int sock_s;
	int i;
	struct sockaddr_in client_addr;
	
	
	if (write(sock_fd, &dir_req, sizeof(dir_req)) < 0)
		error("Client - cant send requset directory files \n ");
	if (recv(sock_fd, &dir_holder, sizeof(dir_holder), 0) < 0)
		error("didnt recv dir holder in shtdown\n");

	for (i = 0; i < dir_holder.m_count; i++) {
		if (recv(sock_fd, &file_shared, sizeof(file_shared), 0) < 0)
			error("Client - rec file error in shutdown");
		client_addr.sin_family = AF_INET;
		client_addr.sin_port = file_shared.fe_port;
		client_addr.sin_addr.s_addr = file_shared.fe_addr;
		printf("Client - get_list: received MSG_DIRENT for ""%s"" @ 127.0.0.1:%d\n", file_shared.fe_name, file_shared.fe_port);
		if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
			error("Socket creation error \n");
		if (connect(sock_s, (struct sockaddr*) & client_addr, sizeof(client_addr)) < 0)
			error("Connection Failed client already shutdown\n");
		printf("Client - sending MSG_SHUTDOWN to peer at 127.0.0.1:%d\n", client_addr.sin_port);
		write(sock_s, &shtdwn_msg, sizeof(shtdwn_msg));
	}

	printf("Client - sending MSG_SHUTDOWN to server at 127.0.0.1:%d\n", P_SRV_PORT);
	if (write(sock_fd, &shtdwn_msg, sizeof(shtdwn_msg)) < 0)
		error("Client - send shutdown msg\n");
	close(sock_fd);
	printf("Client - shutting down ./client shutdown\n");
	exit(1);
}










void turn_handle(int sock)
{
	msg_dirhdr_t turn;
	msg_ack_turn_t turn_ack;
	msg_notify_t attacked_notify;
	msg_dirhdr_t hit_or_miss;
	msg_ack_t ack_back;
	ack_back.m_type = MSG_ACK;
	turn_ack.m_type = MSG_TURN;
	printf("\nClient - Socket number [%d]\n",sock);
	printf("\nClient - Waiting for turn setup\n");
    if(recv(sock,&turn,sizeof(turn),0)<0){
		error("\nClient - Error: couldn't receive turn msg\n");
	}
	printf("\nClient - received turn setup\n");
	while(1){
		printf("\nturn signal = %d\n",turn.m_count);
		printf("\nClient - received turn msg \n");
		if(turn.m_type != MSG_DIRHDR){
			printf("\n turn.m_type = %d \n",turn.m_type);
			error("\nClient - turn msg type wrong\n");
		}
		if(turn.m_count == 1){
			printf("\nWait for your turn\n");
			if(recv(sock,&attacked_notify,sizeof(attacked_notify),0)<0){
				error("\nClient - attacked_notify error\n");
			}
			printf("\nClient - received attack coordinates\n");
			hit_or_miss.m_count = 0; //MISS!
			if(write(sock,&hit_or_miss,sizeof(hit_or_miss))<0){
				error("\nClient - hit_or_miss error\n");
			}
			printf("\nClient - sent hit_or_miss\n");
			if(recv(sock,&turn,sizeof(turn),0)<0){
				error("\nrecv from Client error\n"); 				
			}
			printf("\nClient - received turn update\n");
			turn_ack.m_type = MSG_TURN;
			printf("\nClient - send ack for received turn update to server\n");
			if(write(sock,&ack_back,sizeof(ack_back))<0){ 
				error("\nClient - Error sending turn_ack\n");
			}
			printf("\nClient - sent ack for received turn update to server\n");
		}
		if(turn.m_count == 1){
			error("\nClient - Error switching turn.m_count value\n");
		}
		printf("\nYour turn now!\n");
		char name[P_NAME_LEN];
		printf("\nEnter a coordinate to hit: ");
		scanf("%s", name);
		printf("\nYour coordiante is %s.\n", name);
		msg_notify_t temp;
		msg_ack_t temp_ack;
		temp.m_type = MSG_NOTIFY;
		strcpy(temp.m_name,name);
		temp.m_addr = inet_addr( "127.0.0.1" );
		temp.m_port = 0;
		printf("\nClient - sending MSG_NOTIFY\n");
		if( write(sock,&temp,sizeof(temp)) < 0 ){
			error("\nsending notify\n");
		}
		printf("\nClient - sent MSG_NOTIFY\n");
		if( recv(sock,&temp_ack,sizeof(temp_ack),0) <0 )
			error("\nrecv from Client error\n");
		printf("\nClient - share: receiving MSG_ACK\n");
		if( temp_ack.m_type != MSG_ACK){
			error("\ntype recived not msg ack\n");
        }
		msg_dirhdr_t attack_bool;	
		printf("\nClient - waiting to receive if hit or miss\n");
		if( recv(sock,&attack_bool,sizeof(attack_bool),0) <0 ){
			error("\nrecv from Client error\n");
		}
		if(attack_bool.m_count == 0){
			printf("\n MISSED! \n");
		} else if(attack_bool.m_count == 1){
			 printf("\n HIT!! \n");
		} 
		turn_ack.m_type = MSG_TURN;
		printf("\nClient - Send MSG_TURN to server\n");
		if(write(sock,&turn_ack,sizeof(turn_ack))<0){
			error("\nClient- Error sending turn_ack\n");
		}
		if(recv(sock,&turn,sizeof(turn),0)<0){
			error("\nClient - Error: couldn't receive turn msg\n");
		}
		printf("\nClient - received MSG_DIRHDR - turn swap\n");
	
		printf("\nClient - send MSG_ACK for MSG_DIRHDR\n");
		if(write(sock,&ack_back,sizeof(ack_back))<0){
			error("\nClient- Error sending turn_ack\n");
		}
		printf("\nClient - sent MSG_ACK for MSG_DIRHDR\n");
	}
	return;
}





int main(int argc, char* argv[])
{
	struct sockaddr_in srv_addr;
	int   sock_fd;
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = P_SRV_PORT-3;
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Client - Socket creation error \n");
	printf("\nClient - Socket created\n");
	if (connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0)
		error("\nClient - Connection Failed \n");
	printf("\nClient - Connection succeeded\n");
	while(1){
		turn_handle(sock_fd);
	}
	//m_shutdown(sock_fd);
	return 0;
}
