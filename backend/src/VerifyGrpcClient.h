#pragma once
#include<grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include "message.pb.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;


class VerifyGrpcClient
{
	friend class Singleton < VerifyGrpcClient>;
public:
	GetVarifyRsp GetVarifyReq(std::string email) {
		ClientContext context;
	}
};

