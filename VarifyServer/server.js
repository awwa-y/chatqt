// ============ 导入所有必需的模块 ============
const path = require('path');
const grpc = require('@grpc/grpc-js');
const protoLoader = require('@grpc/proto-loader');
const { v4: uuidv4 } = require('uuid');
const fs = require('fs');
const nodemailer = require('nodemailer');

// ============ 检查模块是否正确加载 ============
console.log('grpc 模块已加载:', typeof grpc !== 'undefined' ? '是' : '否');
console.log('protoLoader 模块已加载:', typeof protoLoader !== 'undefined' ? '是' : '否');
console.log('uuid 模块已加载:', typeof uuidv4 !== 'undefined' ? '是' : '否');

// ============ 读取配置文件 ============
let config;
try {
    config = JSON.parse(fs.readFileSync('config.json', 'utf8'));
    console.log('配置文件已加载');
} catch (error) {
    console.error('加载配置文件失败:', error);
    process.exit(1);
}

// ============ 邮件配置 ============
const email_user = config.email.user;
const email_pass = config.email.pass;

const transport = nodemailer.createTransport({
    host: 'smtp.163.com',
    port: 465,
    secure: true,
    auth: {
        user: email_user,
        pass: email_pass
    }
});

// ============ 发送邮件函数 ============
function SendMail(mailOptions_) {
    return new Promise(function (resolve, reject) {
        transport.sendMail(mailOptions_, function (error, info) {
            if (error) {
                console.log('发送邮件失败:', error);
                reject(error);
            } else {
                console.log('邮件已成功发送:', info.response);
                resolve(info.response);
            }
        });
    });
}

// ============ 加载 Protocol Buffers 定义 ============
const PROTO_PATH = path.join(__dirname, 'message.proto');
console.log('Protocol Buffers 文件路径:', PROTO_PATH);

let message_proto;
try {
    const packageDefinition = protoLoader.loadSync(PROTO_PATH, {
        keepCase: true,
        longs: String,
        enums: String,
        defaults: true,
        oneofs: true
    });
    
    const protoDescriptor = grpc.loadPackageDefinition(packageDefinition);
    message_proto = protoDescriptor.message;
    console.log('Protocol Buffers 定义加载成功');
} catch (error) {
    console.error('加载 Protocol Buffers 定义失败:', error);
    process.exit(1);
}

// ============ 定义错误常量 ============
const Errors = {
    Success: 0,
    RedisErr: 1,
    Exception: 2
};

// ============ gRPC 服务方法 ============
async function GetVarifyCode(call, callback) {
    console.log("收到验证码请求，邮箱:", call.request.email);
    
    try {
        // 生成唯一验证码
        const uniqueId = uuidv4();
        console.log("生成的验证码:", uniqueId);
        
        // 邮件内容
        const text_str = '您的验证码为 ' + uniqueId + '，请三分钟内完成注册';
        
        // 邮件选项
        const mailOptions = {
            from: 'y3358735079@163.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };

        // 发送邮件
        console.log("正在发送邮件...");
        const send_res = await SendMail(mailOptions);
        console.log("邮件发送结果:", send_res);

        // 返回成功响应
        callback(null, {
            email: call.request.email,
            error: Errors.Success,
            code: uniqueId
        });
        
    } catch (error) {
        console.error("处理验证码请求时出错:", error);

        // 返回错误响应
        callback(null, {
            email: call.request.email,
            error: Errors.Exception,
            code: ""
        });
    }
}

// ============ 启动 gRPC 服务器 ============
function main() {
    console.log('正在启动 gRPC 服务器...');
    
    // 检查 grpc 变量是否可用
    if (typeof grpc === 'undefined') {
        console.error('错误: grpc 变量未定义');
        process.exit(1);
    }
    
    console.log('创建 gRPC 服务器实例...');
    const server = new grpc.Server();
    
    // 添加服务
    console.log('添加服务到服务器...');
    server.addService(message_proto.VarifyService.service, { 
        GetVarifyCode: GetVarifyCode 
    });
    
    // 绑定端口并启动服务器
    console.log('绑定端口 50052...');
    server.bindAsync('0.0.0.0:50052', grpc.ServerCredentials.createInsecure(), (error, port) => {
        if (error) {
            console.error('绑定端口失败:', error);
            process.exit(1);
        }
        
        console.log('端口绑定成功，启动服务器...');
        server.start();
        console.log('========================================');
    console.log('✅ gRPC 服务器已成功启动');
    console.log('监听地址: 0.0.0.0:50052');
    console.log('服务: VarifyService.GetVarifyCode');
    console.log('按 Ctrl+C 停止服务器');
    console.log('========================================');
    });
}

// ============ 进程信号处理 ============
process.on('SIGINT', () => {
    console.log('\n收到终止信号，正在关闭服务器...');
    process.exit(0);
});

// ============ 全局异常处理 ============
process.on('uncaughtException', (error) => {
    console.error('未捕获的异常:', error);
    process.exit(1);
});

process.on('unhandledRejection', (reason, promise) => {
    console.error('未处理的 Promise 拒绝:', reason);
    process.exit(1);
});

// ============ 启动服务器 ============
main();