text: text-client text-server

text-client:
	gcc -o text-client text-client.c

text-server:
	gcc -o text-server text-server.c

clean:
	rm -rf text-client text-server *.o