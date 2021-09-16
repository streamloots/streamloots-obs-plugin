#ifndef WSServer_hpp
#define WSServer_hpp
#include <string>
#include <QString>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <obs-module.h>
#include <obs-frontend-api.h>

using websocketpp::connection_hdl;

namespace server {
    typedef websocketpp::server<websocketpp::config::asio> server;
    typedef server::message_ptr message_ptr;

    class WSServer{

        public:
            explicit WSServer();
            virtual ~WSServer();
            void start();
            void stop();

        private:
            const static int START_PORT;
            const static int END_PORT;
            server _server;
            std::thread _serverThread;
            int _serverPort;
            std::map<QString, connection_hdl> _connectionList;

            void onOpen(connection_hdl hdl);
            void onClose(connection_hdl hdl);
            void onMessage(connection_hdl hdl, message_ptr msg);
            QString getRemoteEndpoint(connection_hdl hdl);

            void serverRunner();
    };
}
#endif