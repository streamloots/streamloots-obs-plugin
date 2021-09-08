
#pragma once
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <QString>
#include <obs-module.h>
#include <obs-frontend-api.h>

using websocketpp::connection_hdl;
typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;

class WSServer{

    public:
        explicit WSServer();
        virtual ~WSServer();
        void start(int port);
        void stop();

    private:
        server _server;
        std::thread _serverThread;
        int _serverPort;

        void onOpen(connection_hdl hdl);
        void onMessage(connection_hdl hdl, message_ptr msg);
        QString getRemoteEndpoint(connection_hdl hdl);

        void serverRunner();

};