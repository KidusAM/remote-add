#include <array>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lib/remoteadd.pb.h"
#include "lib/remoteadd_mock.grpc.pb.h"
#include "client/remoteadd-client-lib.h"

// simulates the server responding
class RemoteAddStubLive : public MockRemoteAddStub {
    grpc::Status Add(grpc::ClientContext *context, const AdditionArgs& args, AdditionResults *reply) override {
        reply->set_sum(add(args.arg1(), args.arg2()));
        return grpc::Status(grpc::Status::OK);
    }

public:
    // the test can use this function to verify the return value of the
    // RemoteAddClient is the same as the one the server computed
    static int add(int n1, int n2) { return n1 + n2; }
};

class RemoteAddStubFail : public MockRemoteAddStub {
    grpc::Status Add(grpc::ClientContext *context, const AdditionArgs& args, AdditionResults *reply) override {
        reply->set_sum(args.arg1() + args.arg2());
        return grpc::Status(grpc::Status::CANCELLED);
    }
};

TEST(RemoteAddTest, CorrectReturns) {
    // make sure the client returns the sum when the server is working
    std::optional<int> result;
    RemoteAddClient working(std::make_unique<RemoteAddStubLive>());
    const std::vector<std::pair<int,int>> test_cases = {
        {1,2},
        {-20, 411},
    };

    for (const auto& test_pair : test_cases) {
        result = working.Add(test_pair.first, test_pair.second);
        EXPECT_NE(result, std::nullopt);
        EXPECT_EQ(*result, RemoteAddStubLive::add(test_pair.first,
                    test_pair.second));
    }

    // make sure the client doesn't return a value when the server doesn't
    // respond
    RemoteAddClient not_working(std::make_unique<RemoteAddStubFail>());
    for (const auto& test_pair : test_cases) {
        result = not_working.Add(test_pair.first, test_pair.second);
        EXPECT_EQ(result, std::nullopt);
    }
}
