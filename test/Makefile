ALL:client server

client:udpclient.c config.h
	gcc -o $@ $< 

server:udp.c config.h
	gcc -o $@ $< 

clean:
	rm -fr client server *.o .log
