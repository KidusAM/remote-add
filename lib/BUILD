load("@com_github_grpc_grpc//bazel:python_rules.bzl", "py_grpc_library", "py_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")

proto_library(
    name = "remoteadd_proto",
    srcs = ["remoteadd.proto"],
)

py_proto_library(
    name = "remoteadd_py_pb2",
    deps = [":remoteadd_proto"],
    visibility = ["//visibility:public"],
)

py_grpc_library(
    name = "remoteadd_py_pb2_grpc",
    srcs = [":remoteadd_proto"],
    deps = [":remoteadd_py_pb2"],
    visibility = ["//visibility:public"],
)

cc_proto_library(
    name = "remoteadd_cc_pb2",
    deps = [":remoteadd_proto"]
)

cc_grpc_library(
    name = "remoteadd_cc_grpc",
    srcs = [":remoteadd_proto"],
    deps = [":remoteadd_cc_pb2"],
    grpc_only = True,
    generate_mocks = True,
    visibility = ["//visibility:public"]
)
