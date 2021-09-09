#include "WSServer.h"
#include <QtCore/QObject>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QMainWindow>
#include <obs-frontend-api.h>
#include "WSRequest.h"
#include "../plugin-macros.generated.h"
#include <QtCore/QString>

QT_USE_NAMESPACE
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

WSServer::WSServer()
{
    _server.get_alog().clear_channels(websocketpp::log::alevel::frame_header | websocketpp::log::alevel::frame_payload | websocketpp::log::alevel::control);
    _server.init_asio();
    _server.set_reuse_addr(true);
    _server.set_open_handler(bind(&WSServer::onOpen, this, ::_1));
    // _server.set_close_handler(bind(&WSServer::onClose, this, ::_1));
    _server.set_message_handler(bind(&WSServer::onMessage, this, ::_1, ::_2));
}

WSServer::~WSServer()
{
    stop();
}

void WSServer::serverRunner()
{
	blog(LOG_INFO, "IO thread started.");
	try {
		_server.run();
	} catch (websocketpp::exception const & e) {
		blog(LOG_ERROR, "websocketpp instance returned an error: %s", e.what());
	} catch (const std::exception & e) {
		blog(LOG_ERROR, "websocketpp instance returned an error: %s", e.what());
	} catch (...) {
		blog(LOG_ERROR, "websocketpp instance returned an error");
	}
	blog(LOG_INFO, "IO thread exited.");
}

void WSServer::start(int port)
{
    if (_server.is_listening())
    {
        blog(LOG_INFO, "WSServer::start: server already on this port and protocol mode. no restart needed");
        return;
    }

    if (_server.is_listening())
    {
        stop();
    }

    _server.reset();

    _serverPort = port;

    websocketpp::lib::error_code errorCode;

    blog(LOG_INFO, "WSServer::start: Not locked to IPv4 bindings");
    _server.listen(_serverPort, errorCode);

    if (errorCode)
    {
        std::string errorCodeMessage = errorCode.message();
        blog(LOG_INFO, "server: listen failed: %s", errorCodeMessage.c_str());

        obs_frontend_push_ui_translation(obs_module_get_string);
        QString errorTitle =  QObject::tr("OBSWebsocket.Server.StartFailed.Title");
        QString errorMessage =  QObject::tr("OBSWebsocket.Server.StartFailed.Message").arg(_serverPort).arg(errorCodeMessage.c_str());
        obs_frontend_pop_ui_translation();

        QMainWindow *mainWindow = reinterpret_cast<QMainWindow *>(obs_frontend_get_main_window());
        QMessageBox::warning(mainWindow, errorTitle, errorMessage);

        return;
    }

    _server.start_accept();

    _serverThread = std::thread(&WSServer::serverRunner, this);

    blog(LOG_INFO, "server started successfully on port %d", _serverPort);
}

void WSServer::onOpen(connection_hdl hdl)
{
    QString clientIp = getRemoteEndpoint(hdl);
    blog(LOG_INFO, "new client connection from %s", clientIp.toUtf8().constData());
}

void WSServer::onMessage(connection_hdl hdl, server::message_ptr msg)
{
    blog(LOG_INFO, "onMessage called with hdl: %s and message %s", hdl.lock().get(), msg->get_payload());
    std::string response = WSRequest::processMessage(msg->get_payload());
    try
    {
        _server.send(hdl, response, msg->get_opcode());
    }
    catch (websocketpp::exception const &e)
    {
        blog(LOG_INFO, "Echo failed because %s", e.what());
    }
}

QString WSServer::getRemoteEndpoint(connection_hdl hdl)
{
    auto conn = _server.get_con_from_hdl(hdl);
    return QString::fromStdString(conn->get_remote_endpoint());
}

void WSServer::stop()
{
	if (!_server.is_listening()) {
		return;
	}

	_server.stop_listening();
	_serverThread.join();
	blog(LOG_INFO, "server stopped successfully");
}