#pragma once
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <memory>   
#include <iostream>
#include "Singleton.h"
#include <map>
#include <functional>
#include <unordered_map>
#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "hiredis.h"
#include <cassert>
#include <atomic>
// 命名空间声明
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

enum ErrorCodes {
    Success = 0,
    Error_Json = 1001,
    RPCFailed = 1002,

};
class ConfigMgr;
extern ConfigMgr gCfgMgr;