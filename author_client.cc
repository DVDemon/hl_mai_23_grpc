/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/helloworld.grpc.pb.h"
#else
#include "author.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using author::Author;
using author::AuthorReply;
using author::AuthorRequest;

class AuthorClient {
 public:
  AuthorClient(std::shared_ptr<Channel> channel)
      : stub_(Author::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string GetAuthor(const int id) {
    // Data we are sending to the server.
    AuthorRequest request;
    request.set_id(id);

    // Container for the data we expect from the server.
    AuthorReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetAuthor(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.first_name();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

 private:
  std::unique_ptr<Author::Stub> stub_;
};

int main(int argc, char** argv) {
  
  AuthorClient greeter(
      grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  auto reply = greeter.GetAuthor(1);
  std::cout << "Greeter received: " << reply << std::endl;

  return 0;
}
