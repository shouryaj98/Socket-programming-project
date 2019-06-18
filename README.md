# CHAT AND FILE TRANSFER APPLICATION USING SOCKET PROGRAMMING IN C

### Abstract
The objective of this project is to create a system to facilitate duplex communication between all the nodes in a small Local Area Network (LAN) using Socket Programming. To establish the communication between the client and server, we make use of TCP protocol using socket programming in C. 

### Introduction
TCP is a standard protocol which defines how to establish and maintain a network connection via which application programs can exchange data. TCP works with the Internet Protocol (IP), which defines how computers send packets of data to each other. TCP is a connection-oriented protocol, which means a connection is established and maintained until the application programs at each end have finished exchanging messages. It determines how to break application data into packets that networks can deliver, send packets to and accept the packets from the network layer, manages flow control and because it is meant to provide error-free data transmission handles retransmission of dropped or garbled packet as well as acknowledgment of all the packets which arrive.

### Definition of the various terminologies
**Socket**: Server will get so many hits from different clients, and then the server has to identify each client uniquely to reply every request. To achieve this, we use IP address of client and port number of the process. This is called socket. Any network communication should go through socket. Thus, a socket is a virtual connection between two applications.

**IP Address**: An IP address is a numerical label assigned to each device connected to computer network that uses the Internet Protocol for communication. An IP address serves two principal functions. It identifies the host (its network interface) and it provides the location of the host in the network, and thus the capability of establishing a path to that host.

**Bind**: Bind system call helps the servers to register themselves with the system. It tells the system that any messages received at the particular IP address and the specified port be directed to the system.

**Listen**: This system call is used by a connection-oriented server socket to indicate that it is willing to receive connections from the client. 

**Send**: A connection-oriented client/server can use the send system call to exchange messages between each other.

**Receive**: The receive system call can used to receive messages from a connected socket a client/server.

**Close**: The Unix close system call is used to close a socket.

### How to run
First make sure the nodes are connected to a LAN either wired or wireless. Find out the IP addresses of the nodes in the LAN which need to communicate with each other. The command “ifconfig” can be used for it. These IP addresses should replace the existing IP addresses used in the client.c file. Compile both the server.c and client.c using a C compiler. Run the generated executables in two separate terminals on each of the node. For server running on each node enter a port value that’s acceptable. Use the menu-driven client program to communicate with other nodes.
