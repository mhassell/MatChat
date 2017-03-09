# playing with non-blocking sockets in python

import socket
import select
import sys

HOST = ''
SOCKET_LIST = []
RECV_BUFFER = 4096
PORT = 9001  # it's over 9000

def host():

	server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   # usual socket stuff
	server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR,1)  # make it non-blocking
	server_socket.bind(HOST,PORT) # bind the socket to our IP and port
	server_socket.listen(10) #listen for up to 10 connections

	SOCKET_LIST.append(server_socket) # add the host to the list of all sockets

	print "Chat server started on port " + str(PORT)

	while 1: #shivers!

		# select goes through the list of sockets and, well, selects the ones from 
		# SOCKET_LIST that are ready to read and places them in READY_TO READ
		# the first argument to select is sockets that we want to read from
		# the second argument is sockets we want to write to
		# the third argument is sockets that we check for exceptional conditions (OS dependent)
		# the last parameter is a timeout - setting it to zero means we just sweep and never wait
		ready_to_read,ready_to_write,in_error = select.select(SOCKET_LIST,[],[],0)

		for sock in ready_to_read:
			# we have a new connection request 
			# (does the host only have something to read if someone connects?) (played with in 
			# console - yes, host reports it has something to read if someone connects)
			if sock == server_socket:
				sockfd, addr = server_socket.accept()
				SOCKET_LIST.append(sockfd)
				print "Client (%s, %s) connected" % addr

				# let everyone know someone signed in
				broadcast(server_socket, sockfd, "[%s:%s] entered our chatting room\n" % addr)

			# message from a client
			else:
                # process data recieved from client, 
                try:
                    # receiving data from the socket.
                    data = sock.recv(RECV_BUFFER)
                    if data:
                        # there is something in the socket
                        broadcast(server_socket, sock, "\r" + '[' + str(sock.getpeername()) + '] ' + data)  
                    else:
                        # remove the socket that's broken    
                        if sock in SOCKET_LIST:
                            SOCKET_LIST.remove(sock)

                        # at this stage, no data means probably the connection has been broken
                        broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr) 

                # exception 
                except:
                    broadcast(server_socket, sock, "Client (%s, %s) is offline\n" % addr)
                    continue

    server_socket.close()

def broadcast(server_socket, sock, message):
	for socket in SOCKET_LIST:
        # send the message only to peer
        if socket != server_socket and socket != sock :
            try :
                socket.send(message)
            except :
                # broken socket connection
                socket.close()
                # broken socket, remove it
                if socket in SOCKET_LIST:
                    SOCKET_LIST.remove(socket)
 
if __name__ == "__main__":

    sys.exit(chat_server())