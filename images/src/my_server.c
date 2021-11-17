#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_QUEUE 5
#define PORT 3945
#define XSTR( x ) STR( x )
#define STR( a ) #a
#ifndef VERSION
	#define VERSION 1.0.1
#endif


int get_tcp_socket ( struct sockaddr_in ) ;
void execute_task ( int, int ) ;
void run_server ( int, struct sockaddr_in ) ;
void send_info ( int ) ;


// {{{ MAIN - - -
int
main ( int argc, char **argv ) {

	struct sockaddr_in server_addr;

	server_addr.sin_port = htons( PORT );
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl( INADDR_ANY );

	int server_fd = get_tcp_socket( server_addr );

	run_server( server_fd, server_addr );

	return 0;

}
// }}}


// {{{ get_tcp_socket --
int
get_tcp_socket ( struct sockaddr_in addr ) {

	int server_fd;

	// Create socket
	if (( server_fd = socket( addr.sin_family, SOCK_STREAM, IPPROTO_TCP )) < 0 ) {
		fprintf( stderr, "socket failed to create\n" );
		exit( -1 );
	}

	return server_fd;

}
// }}}

// {{{ execute_task --
void
execute_task ( int task_id, int client_fd ) {

	char *msg = malloc( 1024 * sizeof( *msg ) );

	sprintf( msg, "executing task n%02d", task_id );
	send( client_fd, msg, strlen( msg ), 0 );

	strcpy( msg, "." );
	for ( int i = 0; i < 10; i ++ ) {
		send( client_fd, msg, strlen( msg ), 0 );
		sleep( 1 );
	}

	strcpy( msg, "\ntask done!\n" );
	send( client_fd, msg, strlen( msg ), 0 );

}
// }}}

// {{{ send_info --
void
send_info ( int client_fd ) {

	char *msg = malloc( 1024 * sizeof( *msg ) );
	char hostname[256];

	// send http header
	strcpy( msg, "HTTP/1.1 200 OK\r\n\n" );
	send( client_fd, msg, strlen( msg ), 0 );

	// send info
	gethostname( hostname, sizeof( hostname ) );
	sprintf( msg, "I'm hostname %s (v%s)\n", hostname, XSTR(VERSION) );
	send( client_fd, msg, strlen( msg ), 0 );

}
// }}}

// {{{ run_server --
void
run_server ( int server_fd, struct sockaddr_in server_addr ) {

	int new_fd, count = 0;
	struct sockaddr_in *new_addr;
	socklen_t addrlen = sizeof( *new_addr );

	// Bind socket to PORT
	if ( bind( server_fd, ( struct sockaddr * ) &server_addr, sizeof( server_addr ) ) < 0 )  {
		fprintf( stderr, "socket failed to bind\n" );
		exit( -1 );
	}

	// Listen on socket
	if ( listen( server_fd, MAX_QUEUE ) < 0 ) {
		fprintf( stderr, "error creating listening queue\n" );
		exit( -1 );
	}

	printf( "Server listening on port %d\n", ntohs( server_addr.sin_port ) );

	while ( 1 ) {
 		
		// Accept connection
		new_fd = accept( server_fd, (struct sockaddr *) &new_addr, (socklen_t *) &addrlen );
		if ( new_fd < 0 ) {
			fprintf( stderr, "error accepting connection\n" );
			continue;
		}

		printf( "server: new connection\n" );
		count++;

		// Execute new task on children
		if ( !fork() ) {

			close( server_fd );	// close server socket

			//execute_task( count, new_fd );
			send_info( new_fd );

			close( new_fd ); // close client socket before exiting
			exit( 0 );

		}

		close( new_fd ); // father closes client socket, already used by children

	}

}
// }}}

