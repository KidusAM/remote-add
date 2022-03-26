from lib.remoteadd_pb2_grpc import RemoteAdd, add_RemoteAddServicer_to_server
from lib.remoteadd_pb2 import AdditionArgs, AdditionResults

from concurrent import futures

import grpc

RPC_PORT = "12345"

class Adder(RemoteAdd):
    def Add(self, request : AdditionArgs, context) -> AdditionResults:
        print("Add call with ", (request.arg1, request.arg2))
        res = request.arg1 + request.arg2
        return AdditionResults(sum=res)

def main():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    add_RemoteAddServicer_to_server(Adder(), server)
    server.add_insecure_port('[::]:' + RPC_PORT)
    server.start()
    server.wait_for_termination()

if __name__ == '__main__':
    main()
