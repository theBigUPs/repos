#http://127.0.0.1:8000/hello.html

import socket
import sys # In order to terminate the program
serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

SERVER_HOST = '0.0.0.0'
SERVER_PORT = 8000

serverSocket.bind((SERVER_HOST , SERVER_PORT))
serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
serverSocket.listen(1)
while True:
    #Establish the connection
    
    print('Ready to serve...')
    connectionSocket, addr = serverSocket.accept()#Fill in start #Fill in end
    try:
        message = connectionSocket.recv(1024) #Fill in start #Fill in end
        filename = message.split()[1]
        f = open(filename[1:])
        outputdata = f.read()#Fill in start #Fill in end
        #Send one HTTP header line into socket
         #Fill in start
        connectionSocket.send('HTTP/1.1 200 OK\nContent-Type: text/html\n\n'.encode('utf-8'))
        #Fill in end
        #Send the content of the requested file to the client

        for i in range(0, len(outputdata)):
            connectionSocket.send(outputdata[i].encode())
        connectionSocket.send("\r\n".encode())

        connectionSocket.close()
        
        if connectionSocket.fileno() == -1:
            break
    except IOError:
        connectionSocket.send('HTTP/1.1 404 file not found\nContent-Type: text/html\n\n'.encode('utf-8')) 
        connectionSocket.close();
        pass
    pass

serverSocket.close()


