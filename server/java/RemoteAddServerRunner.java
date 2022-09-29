import io.grpc.demo.remoteadddemo.*;
import io.grpc.demo.remoteadddemo.Remoteadd;
import io.grpc.stub.StreamObserver;
import io.grpc.Server;
import io.grpc.ServerBuilder;


public class RemoteAddServerRunner {
    private final static int SERVER_PORT = 12345;

    public static void main(String args[]) {
        System.out.println("Server main method");
        Server server = ServerBuilder
            .forPort(SERVER_PORT)
            .addService(new RemoteAddImpl())
            .build();
        try {
            server.start();
            server.awaitTermination();
        } catch (Exception e) {
            System.err.println("Server exiting");
        }
    }

    private static class RemoteAddImpl extends RemoteAddGrpc.RemoteAddImplBase {
        @Override
        public void add(Remoteadd.AdditionArgs args,
                StreamObserver<Remoteadd.AdditionResults> responseObserver) {
            System.out.println("server called with: " + args);
            // TODO(KidusAM): separate out the addition implementation
            responseObserver.onNext(AddImpl(args));
            responseObserver.onCompleted();
        }

        private Remoteadd.AdditionResults AddImpl(Remoteadd.AdditionArgs arg) {
            return Remoteadd.AdditionResults.newBuilder().setSum(arg.getArg1() +
                    arg.getArg2()).build();
        }
    }
}
