#include <iostream>
#include <cassert>
#include <thread>
#include <algorithm>

#include <unistd.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "cppdb/db.h"

#define MAX_CLIENT 6 
#define BUF_SIZE 256

void err(std:: string msg) {
    perror(msg.c_str());
    exit(1);
}

// https://stackoverflow.com/questions/1488775/c-remove-new-line-from-multiline-string
void trimString(std::string& str) {
    str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
}

void handleClient(int clSocket, cppdb::DB& db) {
    char buffer[BUF_SIZE];
    memset(buffer, 0, BUF_SIZE);
    int msgSize = 0, n;
    std::cout << "Client Connected " << std::endl;
    while ((n = read(clSocket, buffer, BUF_SIZE - 1)) > 0) {
        char* command = strtok(buffer, ";");
        char* key = NULL;
        char* value = NULL;
        std::string reply("");
        if (command != NULL) {
            std::string c(command);
            trimString(c);
            key = strtok(NULL, ";");
            if (key == NULL) {
                reply = "Invalid Command";
                continue;
            }
            std::string k(key);
            if (c == "PUT") {
                value = strtok(NULL, ";");
                if (value == NULL) {
                    reply = "Invalid Command";
                    continue;
                } 
                std::string v(value);
                trimString(v);
                db.put(k, v);
                reply = "Added " + k;
            } else if (c == "GET") {
                trimString(k);
                try {
                    std::string result = db.get(k);
                    reply = k + ": " + result;
                } catch (std::string& e) {
                    reply = k + ": " + "not found";
                }
            } else {
                reply = "Invalid Command";
            }
            
        } else {
            reply = "Invalid Command";
        }
        reply = reply + "\n";
        char wBuf[reply.size() + 1];
        reply.copy(wBuf, reply.size() + 1);
        wBuf[reply.size()] = '\0';

        n = write(clSocket, wBuf, reply.size() + 1);
        if (n < 0)
            err("Could not write to Client's socket");
        
        memset(buffer, 0, BUF_SIZE);
    }
    if (n < 0)
        err("Could not read Client's request");
    close(clSocket);
}

int main(int argc, char* argv[]) {
    std::cout << "Starting Server" << std::endl;    

    int servSocket, portNo; 
    int clSocket, clLen;
    struct sockaddr_in servAdd, clAddr;
    socklen_t csLen;
    
    cppdb::DB db;
    db.open("/tmp/server.db");

    if (argc < 2) {
        err("Invalid Usage. ./server <port no> ");
    }
    
    servSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (servSocket < 0)
        err("Server Socket Could Not Be Created");

    memset((char* ) &servAdd, 0, sizeof(servAdd));
    
    portNo = atoi(argv[1]);
    servAdd.sin_family = AF_INET;
    servAdd.sin_addr.s_addr = INADDR_ANY;
    servAdd.sin_port = htons(portNo);

    struct sockaddr* sa = (struct sockaddr * ) &servAdd; 
    if (bind(servSocket, sa, sizeof(servAdd)) < 0)
        err("Socket could not be bound to the server");
    
    listen(servSocket, MAX_CLIENT);
    std::cout << "Server started. Waiting for connections ... " << std::endl;
    clLen = sizeof(clAddr);
    csLen = (socklen_t) clLen;
    struct sockaddr* ca = (struct sockaddr * ) &clAddr; 
    while (true) {
        clSocket = accept(servSocket, ca, &csLen);
        if (clSocket < 0)
            err("Could not accept connection");

        // handleClient(clSocket);
        std::thread t(handleClient, clSocket, std::ref(db));
        t.detach();
    }
}