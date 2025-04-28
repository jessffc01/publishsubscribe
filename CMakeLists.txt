cmake_minimum_required(VERSION 3.14)

project(pubsub_grpc)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

# Lista de arquivos gerados
set(PROTO_SRCS
    pubsub.pb.cc
    pubsub.grpc.pb.cc
)

set(PROTO_HDRS
    pubsub.pb.h
    pubsub.grpc.pb.h
)

add_library(pubsub_proto
    ${PROTO_SRCS}
    ${PROTO_HDRS}
)

target_link_libraries(pubsub_proto
    gRPC::grpc++
    protobuf::libprotobuf
)

add_executable(server server.cpp)
target_link_libraries(server pubsub_proto)

add_executable(client client.cpp)
target_link_libraries(client pubsub_proto)

