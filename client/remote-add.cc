#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lib/remoteadd.pb.h"

#define SERVER_PORT 12345

int main(int argc, char **argv)
{
    int arg1, arg2;

    // check arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " arg1 arg2\n";
        return 1;
    }

    // extract arguments
    arg1 = std::stoi(argv[1]);
    arg2 = std::stoi(argv[2]);

    std::cout << arg1 << " + " << arg2 << " =\n";

    // construct request arguments
    auto to_be_added = AdditionArgs();
    to_be_added.set_arg1(arg1);
    to_be_added.set_arg2(arg2);
    std::string serialized_args;
    to_be_added.SerializeToString(&serialized_args);

    // setup socket
    auto die = [](const char *msg){
        perror(msg);
        exit(1);
    };

    // first the sockaddr
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        die("socket() failed");
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        die("connect() failed");
    }

    // send the request
    if (send(sock, &serialized_args[0], serialized_args.size(), 0)
            != (ssize_t) serialized_args.size()) {
        die("send() failed");
    }

    // receive the response
    AdditionResults res;
    char buf[1024]; // should be enough for this example
    memset(buf, 0, sizeof(buf));
    int response_size;
    if ( (response_size = recv(sock, buf, sizeof(buf), 0)) < 0) {
        die("recv() failed");
    }

    // setup the string
    std::string result_serialized(buf, response_size);
    // now parse the response
    res.ParseFromString(result_serialized);

    std::cout << res.sum() << std::endl;


    return 0;
}
