#pragma once
#include "rpc/server.h"
#include "rpc/client.h"
#include "rpc/rpc_error.h"
#include <memory>
#include <tuple>
#include <iostream>

class rpcProvider
{
public:
	rpcProvider(rpc::server & srv, const std::string name): name_(name),core("127.0.0.1",(uint16_t)12345)
	{
		try
		{
			id_ = core.call("registerService",name_,"127.0.0.1",srv.port()).as<int>();
		}
		catch (rpc::rpc_error &e) {
		    std::cout << std::endl << e.what() << std::endl;
    		std::cout << "in function " << e.get_function_name() << ": ";
    		using err_t = std::tuple<int, std::string>;
		    auto err = e.get_error().as<err_t>();
		    std::cout << "[error " << std::get<0>(err) << "]: " << std::get<1>(err)
		              << std::endl;
    		return;
    	}
    	std::cout << "obtained identifer " << id_ << std::endl;
	}

	~rpcProvider()
	{
		core.call("unregisterService",name_,id_);
	}
	rpc::client core;
	std::string name_;
	int id_;
};

// TODO cache core connection
// TODO use environment va
inline std::shared_ptr<rpc::client> rpcLookup(const std::string what)
{
	rpc::client c("127.0.0.1",(uint16_t)12345);

	std::tuple<std::string,int> result(c.call("lookupService", what).as<std::tuple<std::string,int> >());
	if(std::get<0>(result).empty())
		return std::shared_ptr<rpc::client>();
	else
	{
		std::cout << "found service " << std::get<0>(result) << ":" << std::get<1>(result) << std::endl;
		return std::make_shared<rpc::client>(std::get<0>(result),std::get<1>(result));
	}
}