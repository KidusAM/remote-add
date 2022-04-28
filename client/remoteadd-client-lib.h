#include <iostream>
#include <memory>
#include <optional>
#include <grpcpp/grpcpp.h>
#include "lib/remoteadd.pb.h"
#include "lib/remoteadd.grpc.pb.h"

class RemoteAddClient {
public:
    RemoteAddClient(std::shared_ptr<grpc::ChannelInterface> channel)
        : stub_(RemoteAdd::NewStub(channel)) {}

    // for testing by passing a non-RPC stub
    RemoteAddClient(std::unique_ptr<RemoteAdd::StubInterface>&& stub)
        : stub_(std::move(stub)) {}

    // calls the Add function on the remote server
    std::optional<int> Add(int n1, int n2);

private:
    std::unique_ptr<RemoteAdd::StubInterface> stub_;
};
