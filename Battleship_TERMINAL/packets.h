
#ifndef _PACKETS_H_
#define _PACKETS_H_
#include <netinet/in.h>

#define P_SRV_PORT 22244	
#define P_NAME_LEN 128		
#define MSG_SHUTDOWN 	-1
#define MSG_ERROR     	 0
#define MSG_NOTIFY    	 1
#define MSG_ACK       	 2
#define MSG_DIRREQ    	 3
#define MSG_DIRHDR		 4
#define MSG_TURN		 8
 
typedef struct msg_notify
{
	int         m_type;	 			// = MSG_NOTIFY
	char        m_name[P_NAME_LEN + 1];		
	in_addr_t   m_addr;				// client's IP address
	in_port_t   m_port;				// client's perceived port
}
msg_notify_t;


typedef struct msg_ack
{
	int         m_type;				// = MSG_ACK
	in_port_t   m_port;				// client's assigned port
	in_addr_t   m_addr;
}
msg_ack_t;

typedef struct msg_ack_turn
{
	int         m_type;				// = MSG_TURN
	int 		m_swap;				
}
msg_ack_turn_t;

typedef struct msg_dirhdr
{
	int         m_type;				// = MSG_DIRHDR
	int         m_count;			
}
msg_dirhdr_t;


typedef struct msg_shutdown
{
	int         m_type;				// = MSG_SHUTDOWN
}
msg_shutdown_t;

#endif
