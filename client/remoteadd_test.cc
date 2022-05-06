#include <array>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "lib/remoteadd.pb.h"
#include "lib/remoteadd_mock.grpc.pb.h"
#include "client/remoteadd-client-lib.h"

TEST(RemoteAddTest, CorrectReturns) {
    std::optional<int> result;
    const std::vector<std::pair<int,int>> test_cases = {
        {1,2},
        {-20, 411},
    };

    for (const auto& test_pair : test_cases) {
        std::shared_ptr mock_stub = std::make_shared<MockRemoteAddStub>();
        int sum = test_pair.first + test_pair.second;

        EXPECT_CALL(*mock_stub, Add)
            .Times(1)
            .WillOnce(
                [sum](auto, auto, AdditionResults *reply) {
                    reply->set_sum(sum);
                    return grpc::Status::OK;
                }
            );

        RemoteAddClient client(mock_stub);

        // ensure the client returns the right value when the server is live
        result = client.Add(test_pair.first, test_pair.second);
        ASSERT_NE(result, std::nullopt);
        EXPECT_EQ(*result, sum);

        // make sure the client doesn't return a result when the server fails
        EXPECT_CALL(*mock_stub, Add)
            .Times(1)
            .WillOnce(testing::Return(grpc::Status::CANCELLED));

        result = client.Add(test_pair.first, test_pair.second);
        EXPECT_EQ(result, std::nullopt);
    }
}
