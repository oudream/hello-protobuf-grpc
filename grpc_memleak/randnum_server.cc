#include <iostream>
#include <memory>
#include <string>
#include <random>

#include <grpc++/grpc++.h>

#include "randnum.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using randnum::EmptyRequest;
using randnum::Number;
using randnum::RandomNumbers;

// Logic and data behind the server's behavior.
class RandomNumbersServiceImpl final : public RandomNumbers::Service {
  Status GetNext(ServerContext* context, const EmptyRequest* request, ServerWriter<Number>* writer)
  {
    std::default_random_engine generator;
    std::normal_distribution<double> dist(5.0,2.0);
    Number num;
    while(1){
	num.set_value(dist(generator));
	if(!writer->Write(num)) {
	  std::cout << "Client disconnected." << std::endl;
	  break;
	}
    }
    return Status::OK;
  }

};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  RandomNumbersServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
