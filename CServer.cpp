#include "CServer.h"

CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _socket(ioc) {

}

// ==================== 启动服务器 ====================
void CServer::Start()
{
    auto self = shared_from_this();
    _acceptor.async_accept(_socket, [self](beast::error_code ec) {
        try {
            //出错则放弃这个连接，继续监听新链接
            if (ec) {
                self->Start();
                return;
            }

            //处理新链接，创建HpptConnection类管理新连接
            std::make_shared<HttpConnection>(std::move(self->_socket))->Start();
            //继续监听
            self->Start();
        }
        catch (std::exception& exp) {
            std::cout << "exception is " << exp.what() << std::endl;
            self->Start();
        }
        });
}
// ==================== 异步接受连接 ====================
void CServer::DoAccept() {
    // 异步等待客户端连接
    _acceptor.async_accept(_socket,
        [this](boost::system::error_code ec) {
            if (!ec) {
                // 创建HttpConnection处理新连接
                std::make_shared<HttpConnection>(std::move(_socket))->Start();
            }
            // 继续接受下一个连接（递归调用）
            DoAccept();
        }
    );
}
