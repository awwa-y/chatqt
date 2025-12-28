#pragma once
#include "const.h"

class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
    friend class LogicSystem;
    HttpConnection(boost::asio::io_context &ioc);
    ~HttpConnection();
    tcp::socket& GetSocket();
    void Start();

private:
    void CheckDeadline();
    void WriteResponse();
    void HandleReq();
    void PreParseGetParam();
    tcp::socket  _socket;
    std::unordered_map<std::string, std::string> _get_params;
    std::string _get_url;
    beast::flat_buffer  _buffer{ 8192 };

    http::request<http::dynamic_body> _request;

    http::response<http::dynamic_body> _response;

    // The timer for putting a deadline on connection processing.
    net::steady_timer deadline_{
       _socket.get_executor(),std::chrono::seconds(60)
    };
    
};
