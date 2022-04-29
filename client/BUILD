
cc_library(
    name = "remoteadd-client-lib",
    srcs = ["remoteadd-client-lib.cc"],
    hdrs = ["remoteadd-client-lib.h"],
    deps = [
        "//lib:remoteadd_cc_grpc",
        "@com_github_grpc_grpc//:grpc++",
    ],
    copts = ["-std=c++17"]
)

cc_binary(
    name = "remote-add",
    srcs = ["remote-add.cc"],
    deps = [":remoteadd-client-lib"],
    copts = ["-std=c++17"]
)

cc_test(
    name = "remoteadd_test",
    size = "small",
    srcs = ["remoteadd_test.cc"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "remoteadd-client-lib",
        "//lib:remoteadd_cc_grpc",
    ],
    copts = ["-std=c++17"],
)
