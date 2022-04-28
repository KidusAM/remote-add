#include "client/remoteadd-client-lib.h"

std::optional<int> RemoteAddClient::Add(int n1, int n2) {
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

