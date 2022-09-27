
py_binary(
    name = "remoteadd-server",
    srcs = ["remoteadd-server.py"],
    python_version = "PY3",
    deps = [
        "//lib:remoteadd_py_pb2_grpc",
        "//lib:remoteadd_py_pb2",
    ]
)

java_binary(
    name = "RemoteAddServerRunner",
    srcs = ["java/RemoteAddServerRunner.java"],
    deps = [
        "//lib:remoteadd_java_proto",
        "//lib:remoteadd_java_grpc",
        ],
)
