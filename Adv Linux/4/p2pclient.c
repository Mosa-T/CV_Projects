#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "p2p.h"
#include<pthread.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
void error( char *str );
int check_files(char *name);
size_t findfileSize(char f_n[]);
void *handle_recv(void *socket_desc);
void start_server(in_port_t port);
void *share_file(void *argp);
void m_shutdown(int sock_fd);
void m_leech(int sock_fd);


char **list;
int size_list;

struct thread_SN {
    int socket;
    char name[P_NAME_LEN];
};

void error( char *str )
{
    perror( str );
    exit( EXIT_FAILURE );
}


int check_files(char *name)
{
    int i; 
    for (i =0; i < size_list ; i++)
    {
        if(strcmp(name,list[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

size_t findfileSize(char f_n[]) {
   FILE* fp = fopen(f_n, "r"); // opening a file in read mode
   if (fp == NULL) {// checking whether the file exists or not {
      printf("File Not Found!\n");
      return -1;
   }
   fseek(fp, 0, SEEK_END);
   size_t length = ftell(fp); //counting the size of the file
   fclose(fp); //closing the file
   return length;

   
}


void *share_file(void *argp)
{
    struct thread_SN *args =(struct thread_SN *) argp;
    char name[P_NAME_LEN]; 
    strcpy(name,args->name);
    int sock = args->socket;
    msg_notify_t temp;
    msg_ack_t temp_ack;
    temp.m_type = MSG_NOTIFY;
    strcpy(temp.m_name,name);
    temp.m_addr = inet_addr( "127.0.0.1" );
    temp.m_port = 0;
    if( write(sock,&temp,sizeof(temp)) < 0 )
        error("sending notify");
    if( recv(sock,&temp_ack,sizeof(temp_ack),0) <0 )
         error("recv from Client error");
	 printf("\nClient - share: sending MSG_NOTIFY for ""%s"" @ 127.0.0.1:%d\n",name,temp_ack.m_port);
    printf("Client - share: receiving MSG_ACK\n");
    if( temp_ack.m_type != MSG_ACK)
            error("type recived not msg ack\n");
    
    in_port_t newPort = temp_ack.m_port;
	printf("Client - share: set port to %d\n",newPort);
    start_server(newPort);
    free(args);
}



void start_server(in_port_t port)
{
    printf("Peer - start_server: starting peer server\n");
    pthread_t thread_id; 
    struct sockaddr_in my_server,cli_addr;
    int sock_fd,client_sock;
    int sizeC;
    if( ( sock_fd = socket( AF_INET, SOCK_STREAM , 0 ) ) < 0 )
         error( "socket" );
    my_server.sin_family = AF_INET;
    my_server.sin_port = port;
    my_server.sin_addr.s_addr = INADDR_ANY;
    if( bind( sock_fd, (struct sockaddr *) &my_server, sizeof( my_server ) ) < 0 )
        error( "bind in Client seeder " );
	 printf("Peer - start_server: opened socket\n");
    listen(sock_fd , 20);
    printf("Peer - start_server: bound socket to port %d\n",my_server.sin_port);
    sizeC = sizeof(struct sockaddr_in);
    printf("Peer - start_server: listning on socket\n");
    while(client_sock = accept(sock_fd,(struct sockaddr *) &cli_addr,(socklen_t*) &sizeC))
    {
		
        if( pthread_create( &thread_id , NULL ,  handle_recv , (void*) &client_sock) < 0)
            {
                error("could not create thread");
            }
        if (client_sock < 0)
        {
            error("accept failed");
        }
    }
}



void *handle_recv(void *socket_desc)
{
    msg_filereq_t req_temp;
    msg_filesrv_t fileSrv_temp; 
    int sock = *(int*)socket_desc;
    int read_size;
    char buff[P_BUFF_SIZE];
    int buffbyte;
    int i; 
    while( (read_size = recv(sock, &req_temp, sizeof(req_temp) , 0)) > 0)
    {
        if(req_temp.m_type == MSG_FILEREQ)
        {

            if( check_files(req_temp.m_name) < 0 )
            {
                error("file not found in seeded files list\n");
            }

            fileSrv_temp.m_type = MSG_FILESRV;
            i = findfileSize(req_temp.m_name);
			if(i < 0 ){
				
				fileSrv_temp.m_type = MSG_DUMP;
                write(sock,&fileSrv_temp,sizeof(fileSrv_temp));
				printf("Client - file size couldnt be read %s\n",req_temp.m_name);
				continue;
				
			}
            fileSrv_temp.m_file_size = i;
            if (write(sock, &fileSrv_temp, sizeof(fileSrv_temp))  < 0 )
                error("Client - couldnt send to Client MSG_FILESRV \n");
            int file_fd = open(req_temp.m_name, O_RDONLY);
            if( file_fd < 0){
                printf("Client - file cant be opened\n");
					fileSrv_temp.m_type = MSG_DUMP;
                write(sock,&fileSrv_temp,sizeof(fileSrv_temp));
				printf("Client - file size couldnt be read %s\n",req_temp.m_name);
				exit(1);
			}
            while( (buffbyte = read(file_fd,buff,sizeof(buff))) !=0)
	        {
		        if(buffbyte == -1)
			        error("Client couldnt read file \n ");
		        if( ( write( sock, buff , buffbyte) ) == -1 )
			    error("Client - couldnt send the file \n");
	        }
	        if(close(file_fd) == -1)
                error("Client - couldn't close the file uploaded \n");
        } 
        if(req_temp.m_type == MSG_SHUTDOWN)
        {
			close(sock);
            exit(1);
        }
    }
}


void m_shutdown(int sock_fd){
	file_ent_t file_shared;
		msg_dirhdr_t dir_holder;
		msg_dirreq_t dir_req;
		msg_shutdown_t shtdwn_msg;	
		shtdwn_msg.m_type = MSG_SHUTDOWN;
        dir_req.m_type = MSG_DIRREQ;
		int sock_s;
		int i;
		struct sockaddr_in client_addr;
		 if( write(sock_fd,&dir_req,sizeof(dir_req)) < 0)
            error("Client - cant send requset directory files \n ");
		if(recv(sock_fd, &dir_holder, sizeof(dir_holder),0) < 0)
			error("didnt recv dir holder in shtdown\n");	
		
		for(i =0; i < dir_holder.m_count; i++){
			if(recv(sock_fd,&file_shared,sizeof(file_shared),0) < 0)
                    error("Client - rec file error in shutdown");
				client_addr.sin_family = AF_INET;
				client_addr.sin_port = file_shared.fe_port;
				client_addr.sin_addr.s_addr = file_shared.fe_addr;
				printf("Client - get_list: received MSG_DIRENT for ""%s"" @ 127.0.0.1:%d\n",file_shared.fe_name,file_shared.fe_port);
				if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
						error("Socket creation error \n"); 
				if (connect(sock_s, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) 
						error("Connection Failed client already shutdown\n"); 
				printf("Client - sending MSG_SHUTDOWN to peer at 127.0.0.1:%d\n",client_addr.sin_port);
				write(sock_s,&shtdwn_msg,sizeof(shtdwn_msg));
		}
		
		printf("Client - sending MSG_SHUTDOWN to server at 127.0.0.1:%d\n",P_SRV_PORT);
		if(write(sock_fd,&shtdwn_msg,sizeof(shtdwn_msg)) < 0)
              error("Client - send shutdown msg\n");
		close(sock_fd);
		printf("Client - shutting down ./client shutdown\n");
		exit(1);
}

void m_leech(int sock_fd){
	msg_dirreq_t dir_req;
        msg_dirhdr_t dir_holder;
        msg_filereq_t filReq_temp; 
        msg_filesrv_t fileSrv_temp; 
		char *buff = malloc(P_BUFF_SIZE);
        int buffbyte;
        int i = 0;
        int sock_s,file_fd;
		struct sockaddr_in peerAddr;
        dir_req.m_type = MSG_DIRREQ;
		file_ent_t temp;
        printf("Client - sending MSG_DIRREQ to the server\n");
        if( write(sock_fd,&dir_req,sizeof(dir_req)) < 0)
            error("Client - cant send requset directory files \n ");
        printf("Client - pending for MSG_DIRHDR from server\n");
        if( recv(sock_fd, &dir_holder, sizeof(dir_holder),0) < 0 )
            error("Client - couldn't receive MSG_DIRHDR\n");
        if(dir_holder.m_type == MSG_DIRHDR)// got a hold of list now neew to download them then start uploading
        {
            printf("Client - get_list: receiving MSG_DIRHDR with %d items\n",dir_holder.m_count);
            for( i = 0; i < dir_holder.m_count ; i++) 
            {
                if(recv(sock_fd,&temp,sizeof(temp),0) < 0){
                    printf("Client - file is unaccessable\n");
					continue;
				}
                if(check_files(temp.fe_name) != -1 ) //get file name and receive whatever is written inside
                {
                    peerAddr.sin_family = AF_INET;
                    peerAddr.sin_port = temp.fe_port;
                    peerAddr.sin_addr.s_addr = temp.fe_addr;
                    if ((sock_s = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
                        error("Client - Socket creation error \n"); 
                    printf("Client - connecting to peer on port %d\n", peerAddr.sin_port);
                    if (connect(sock_s, (struct sockaddr *)&peerAddr, sizeof(peerAddr)) < 0) 
						error("Client - to connect to seeder \n");  
                     filReq_temp.m_type = MSG_FILEREQ;
                     strcpy(filReq_temp.m_name,temp.fe_name);
                     printf("Client - requseting file from peer\n");
                    if (write(sock_s, &filReq_temp,sizeof(filReq_temp)) < 0 )
                        error("Client - couldnt send file req to peer \n");
					printf("Client - get_file_from_client: sent MSG_FILEREQ\n");
                    if ( recv(sock_s, &fileSrv_temp, sizeof(fileSrv_temp),0) < 0)
						error("Client - recv sock_s");
                    printf("Client - get_file_from_client: received MSG_FILESRV: file size : %d\n",fileSrv_temp.m_file_size);
					if(fileSrv_temp.m_type == MSG_DUMP){
						printf("received MSG_DUMP\n");
						close(sock_s);
						continue;
					}	
					file_fd = open(temp.fe_name,O_WRONLY | O_CREAT,0644);
					printf("Client - get_file_from_client: opened file <%s>\n",filReq_temp.m_name);
					if(file_fd < 0)
                        error("Client - couldnt open  file to write or create\n");
                    while((buffbyte = recv(sock_s,buff,2,0))>0)
                    {
                        if( buffbyte == -1)
                            error("Client - recv error, buffbyte was -1\n");
						if( write(file_fd,buff,buffbyte) == -1)
                            error("Client - error writing into file\n");
						if(buffbyte == 1) break;
					}
                    printf("Client - download from peer finished\n");
                    if(close(file_fd) < 0 )
                        error("Client - couldnt close propely the file \n");       
                }
                close(sock_s);
            }
        }
        else 
            error("Client - server response wasnt for directory files \n"); 
}

int main( int argc, char *argv[] )
{
    
    if(argc >2)
    {
        list = (argv+2); 
        size_list = argc-2;
    }
    
    if(!(strcmp(argv[1],"seed")==0 || strcmp(argv[1],"leech")==0 || strcmp(argv[1],"shutdown")==0))
    {
        error("invalid argments");
    }
    struct sockaddr_in srv_addr;
    int   sock_fd;
    int   i;
	pthread_t thread_id; 
    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = P_SRV_PORT;
    srv_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        error("Socket creation error \n"); 
    if (connect(sock_fd, (struct sockaddr *)&srv_addr, sizeof(srv_addr)) < 0) 
        error("Connection Failed \n"); 
	
   	if(strcmp(argv[1],"shutdown") ==0){	
		m_shutdown(sock_fd);
    }
	
    if(strcmp(argv[1],"leech") ==0)
    {
		m_leech(sock_fd);
    }

    /*Seeders and finshed leechers seed by making a thread for each file that will listen for any activitiy*/
    for( i=0; i < size_list; i++)
    {
        struct thread_SN *args = malloc(sizeof *args);
        strcpy(args->name,argv[i+2]);
        args->socket = sock_fd;
        if (pthread_create(&thread_id,NULL,share_file,args) < 0)
            error("could not create thread for to share file\n");
    }
    while(1);
    return 0;
}
