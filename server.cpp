#include "pubsub.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <chrono>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using pubsub::Message;
using pubsub::PublishRequest;
using pubsub::PublishResponse;
using pubsub::PubSub;
using pubsub::SubscriptionRequest;

class PubSubServiceImpl final : public PubSub::Service
{
public:
    Status Publish(ServerContext *context, const PublishRequest *request,
                   PublishResponse *response) override
    {
        std::lock_guard<std::mutex> lock(mu_);
        for (auto &subscriber : subscribers_)
        {
            if (subscriber.topic == request->topic())
            {
                Message msg;
                msg.set_message(request->content());
                subscriber.writer->Write(msg);
            }
        }
        response->set_success(true);
        return Status::OK;
    }

    Status Subscribe(ServerContext *context, const SubscriptionRequest *request,
                     ServerWriter<Message> *writer) override
    {
        Subscriber sub;
        sub.topic = request->topic();
        sub.writer = writer;

        {
            std::lock_guard<std::mutex> lock(mu_);
            subscribers_.push_back(sub);
        }

        while (!context->IsCancelled())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        return Status::OK;
    }

private:
    struct Subscriber
    {
        std::string topic;
        ServerWriter<Message> *writer;
    };

    std::vector<Subscriber> subscribers_;
    std::mutex mu_;
};

void RunServer()
{
    std::string server_address("0.0.0.0:50051");
    PubSubServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Servidor rodando em " << server_address << std::endl;
    server->Wait();
}

int main()
{
    RunServer();
    return 0;
}
