# 📬 PublishSubscribe gRPC

Uma implementação simples e eficiente do modelo **Publish-Subscribe** utilizando **gRPC** e **C++**.

## 🚀 Visão geral
Este projeto demonstra como clientes podem **publicar** mensagens e **assinar** tópicos para receber atualizações em tempo real, usando comunicação remota via **gRPC**.

Ideal para estudos de sistemas distribuídos, comunicação assíncrona e arquitetura orientada a eventos.

## 🛠️ Tecnologias e Ferramentas
- **C++17**
- **gRPC** (Google Remote Procedure Calls)
- **Protocol Buffers (Protobuf)**
- **CMake** para build
- **Linux** (desenvolvido no Mint)
## 📂 Estrutura do projeto
```
publishsubscribe/
├── pubsub.proto   # Definições dos serviços e mensagens
├── server.cpp     # Código-fonte do servidor
├── client.cpp     # Código-fonte do cliente
├── CMakeLists.txt # Configuração do projeto
└── build/         # Diretório de build (gerado após compilação)
```

---

## 🧹 Como configurar e rodar

### 1. Clone o repositório
```bash
git clone git@github.com:jessffc01/publishsubscribe.git
cd publishsubscribe
```

### 2. Gere os arquivos gRPC e Protobuf
```bash
protoc -I . --cpp_out=. --grpc_out=. --plugin=protoc-gen-grpc=$(which grpc_cpp_plugin) pubsub.proto
```

### 3. Compile o projeto
```bash
mkdir build
cd build
cmake ..
make
```

### 4. Execute o servidor
```bash
./server
```

### 5. Em outro terminal, execute o cliente
```bash
./client
``
## ⛔️ Pré-requisitos
- **gRPC** instalado no sistema
- **Protobuf** instalado
- **CMake** instalado
- **Compilador g++** com suporte a C++17
> Se precisar, verifique o guia oficial de instalação do [gRPC C++](https://grpc.io/docs/languages/cpp/quickstart/).
## 📌 Observações
- Sempre que alterar o arquivo `.proto`, gere novamente os arquivos `.pb.h`, `.pb.cc`, `.grpc.pb.h` e `.grpc.pb.cc`.
- O projeto pode ser expandido para múltiplos tópicos, autenticação de clientes e persistência de mensagens.
## 📞 Contato

Feito com carinho por [@jessffc01](https://github.com/jessffc01) 💙  
📧 Email: jessicaffc@id.uff.br
# 🚀 Let's Publish and Subscribe!
