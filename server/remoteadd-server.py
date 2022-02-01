from lib.remoteadd_pb2 import AdditionArgs, AdditionResults
import socketserver

# receives the binary protobuf data for the AdditionArgs and returns
# the raw protobuf data with the sum in an AdditionResults
def doAdd(args_pb):
    args = AdditionArgs()
    args.ParseFromString(args_pb)
    print("Got request:", args)

    res = AdditionResults()
    res.sum = args.arg1 + args.arg2

    return res.SerializeToString()

# handler for server requests
class AddRequestHandler(socketserver.BaseRequestHandler):
    def handle(self):
        req_raw = self.request.recv(1024)

        result = doAdd(req_raw)

        self.request.sendall(result)

def main():
    HOSTNAME, PORT = "localhost", 12345
    with socketserver.TCPServer((HOSTNAME, PORT), AddRequestHandler) as server:
        print("Starting server")
        server.serve_forever()

main()
