#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <optional>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <grpcpp/grpcpp.h>
#include "lib/remoteadd.pb.h"
#include "lib/remoteadd.grpc.pb.h"

#define TARGET "localhost:12345"

class RemoteAddClient {
public:
    RemoteAddClient(std::shared_ptr<grpc::ChannelInterface> channel)
        : stub_(RemoteAdd::NewStub(channel)) {}

    // Calls the add function on the server
    // returns a boolean that indicates whether the call succeeded, and if that
    // is true, the result of the addition
    std::optional<int> Add(int n1, int n2) {
        AdditionArgs args;
        args.set_arg1(n1);
        args.set_arg2(n2);

        AdditionResults reply;

        grpc::ClientContext context;
        grpc::Status status = stub_->Add(&context, args, &reply);

        if (status.ok()) {
            return reply.sum();
        } else {
            std::cerr << "RemoteAddClient err " << status.error_code() << ": "
                      << status.error_message() << std::endl;
        }

        return std::nullopt;
    }

private:
    std::unique_ptr<RemoteAdd::Stub> stub_;
};

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
