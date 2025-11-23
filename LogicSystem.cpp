#include "LogicSystem.h"
#include "HttpConnection.h"
void LogicSystem::RegGet(std::string url, HttpHandler handler) {
    _get_handlers.insert(make_pair(url, handler));
}
LogicSystem::~LogicSystem() {

}
LogicSystem::LogicSystem() {
    RegGet("/get_test", [](std::shared_ptr<HttpConnection> connection) {
        beast::ostream(connection->_response.body()) << "receive get_test req " << std::endl;
        int i = 0;
        beast::ostream(connection->_response.body()) << "no params" << std::endl;
        for (auto& elem : connection->_get_params) {
            i++;
            beast::ostream(connection->_response.body()) << "param" << i << "key is" << elem.first << std::endl;
            beast::ostream(connection->_response.body()) << "param" << i << "value is" << elem.second;
        }
        });
}
bool LogicSystem::HandleGet(std::string path, std::shared_ptr<HttpConnection> con) {
    if (_get_handlers.find(path) == _get_handlers.end()) {
        return false;
    }

    _get_handlers[path](con);
    return true;
}
