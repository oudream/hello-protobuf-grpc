#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "randnum.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using randnum::EmptyRequest;
using randnum::Number;
using randnum::RandomNumbers;

class RandomNumbersClient {
 public:
  RandomNumbersClient(std::shared_ptr<Channel> channel)
      : stub_(RandomNumbers::NewStub(channel)) {} 

  void GetNumbers() {
    Number num;
    ClientContext context;
    EmptyRequest req;

    std::unique_ptr<ClientReader<Number> > reader(
        stub_->GetNext(&context, req));
    int count = 0;
    while (reader->Read(&num)) {
      if(count % 10000 == 0)
      {
        std::cout << num.value() << std::endl;
        count = 0;
      } 
      ++count;
    }
  }

 private:
  std::unique_ptr<RandomNumbers::Stub> stub_;
};

int main(int argc, char** argv) {
  RandomNumbersClient client(
    grpc::CreateChannel("localhost:50051", 
    grpc::InsecureChannelCredentials()));
  client.GetNumbers();
  return 0;
}
