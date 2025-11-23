#pragma once

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <memory>
#include "HttpConnection.h"  
#include "const.h"
class CServer :public std::enable_shared_from_this<CServer>
{
public:
    CServer(boost::asio::io_context& ioc, unsigned short& port);
    void Start();
    void DoAccept();
private:
    tcp::acceptor  _acceptor;
    net::io_context& _ioc;
    tcp::socket   _socket;
};