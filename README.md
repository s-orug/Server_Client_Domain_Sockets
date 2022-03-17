# README
## Objective
The objective of this project is to process large text file and transmit lines of text containing the given string between server/client using Unix Domain Sockets.
## Included Files
The project includes the following files:
-   makefile
-   text-server.c
-   text-client.c
-   README.md
## Makefile
When `make` is executed in the terminal. The make file executes two commands.

`gcc -o text-client text-client.c`

`gcc -o text-server text-server.c`

When `make clean` is executed in the terminal. The make file removes any executable or intermediary build files created by `make`. It is done using the following command in bash.

`rm -rf text-client text-server *.o`

## Server
To run the server a command in the following format must be entered.

`./text-server domain_socket_file_name`

The server will start and display the number of clients it can accept.

Everytime a client connects:
-   The server will read a filename and a specific string from the client.
-   Then everyline containing the string is sent to the client.
-   The number of bytes sent to the client is then logged.

## Client
A client can be started by entering a command in the following format.

`./text-client domain_socket_file_name dat/dante.txt "the journey"`


The server will start and display the number of clients it can accept.

Everytime a client connects:
-   The client will send a filename and a specific string to the server.
-   After the server finishes parsing through text, the client will receive the text.
-   The received text is printed out to the user and the number of bytes received is logged.