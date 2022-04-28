#include <iostream>
#include <string>
#include <optional>
#include "client/remoteadd-client-lib.h"

#define TARGET "localhost:12345"

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

    RemoteAddClient adder(
            grpc::CreateChannel(TARGET, grpc::InsecureChannelCredentials()));

    std::optional<int> result = adder.Add(arg1, arg2);
    if (result) {
        std::cout << arg1 << " + " << arg2 << " =\n";
        std::cout << *result << std::endl;
    } else {
        std::cerr << "Request failed" << std::endl;
    }

    return 0;
}
