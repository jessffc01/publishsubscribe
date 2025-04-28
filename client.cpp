#include "pubsub.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;

using pubsub::Message;
using pubsub::PublishRequest;
using pubsub::PublishResponse;
using pubsub::PubSub;
using pubsub::SubscriptionRequest;

class PubSubClient
{
public:
    PubSubClient(std::shared_ptr<Channel> channel)
        : stub_(PubSub::NewStub(channel)) {}

    bool Publish(const std::string &topic, const std::string &content)
    {
        PublishRequest request;
        request.set_topic(topic);
        request.set_content(content);

        PublishResponse response;
        ClientContext context;

        Status status = stub_->Publish(&context, request, &response);
        if (status.ok())
        {
            std::cout << "Mensagem publicada com sucesso.\n";
            return response.success();
        }
        else
        {
            std::cout << "Erro ao publicar: " << status.error_message() << "\n";
            return false;
        }
    }

    void Subscribe(const std::string &topic)
    {
        SubscriptionRequest request;
        request.set_topic(topic);

        ClientContext context;
        std::unique_ptr<ClientReader<Message>> reader(stub_->Subscribe(&context, request));

        Message msg;
        while (reader->Read(&msg))
        {
            std::cout << "[Mensagem recebida]: " << msg.message() << "\n";
        }

        Status status = reader->Finish();
        if (!status.ok())
        {
            std::cout << "Erro na assinatura: " << status.error_message() << "\n";
        }
    }

private:
    std::unique_ptr<PubSub::Stub> stub_;
};

int main()
{
    PubSubClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    std::string topic = "tech";

    std::thread subscriber_thread([&]()
                                  { client.Subscribe(topic); });

    std::string content;
    while (true)
    {
        std::cout << "Digite uma mensagem para o tópico '" << topic << "': ";
        std::getline(std::cin, content);
        if (content == "exit")
            break;
        client.Publish(topic, content);
    }

    subscriber_thread.join();
    return 0;
}
