#include "CServer.h"
#include "HttpConnection.h"
#include "AsioIOServicePool.h"
CServer::CServer(boost::asio::io_context& ioc, unsigned short& port) :_ioc(ioc),
_acceptor(ioc, tcp::endpoint(tcp::v4(), port)) {

}
// ==================== 异步接受连接 ====================
/*void CServer::DoAccept() {
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
}*/

void CServer::Start()
{	

	auto self = shared_from_this();

	auto& io_context = AsioIOServicePool::GetInstance()->GetIOService();
	std::shared_ptr<HttpConnection> new_con = std::make_shared<HttpConnection>(io_context);
	_acceptor.async_accept(new_con->GetSocket(), [self, new_con](beast::error_code ec) {
		try {
			//出错则放弃这个连接，继续监听新链接
			if (ec) {
				self->Start();
				return;
			}

			//处理新链接，创建HpptConnection类管理新连接
			new_con->Start();
			//继续监听
			self->Start();
		}
		catch (std::exception& exp) {
			std::cout << "exception is " << exp.what() << std::endl;
			self->Start();
		}
	});
}