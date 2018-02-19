#include <memory>
#include <tuple>
#include <vector>
#include "rpcreg_client.hpp"
#include <iostream>

struct Service
{
	int id;
	std::string ip;
	int port;
};

int main() {
	int uniqueid = 0;
	std::map<std::string,Service> services;
    rpc::server srv(12345); // TODO environmental varibale

    std::cout << "core started on port " << srv.port() << std::endl;

    srv.bind("registerService", [&](std::string const& service, std::string const & ip, int port) -> int  {
    	auto it = services.find(service);
    	if(it != services.end())
    	{
    		// override polocy
    		it->second.ip = ip;
    		it->second.port = port;
    		std::cout << "service override " << service << " to " << ip << ":" << port << " as id " << it->second.id << std::endl;
    		return it->second.id;
    	}
    	else
    	{
    		Service s;
    		s.id = ++uniqueid;
    		s.port = port;
    		s.ip = ip;	
    		services[service] = s;
    		std::cout << "service registration " << service << " to " << ip << ":" << port << " as id " << s.id << std::endl;
	    	return s.id;
    	}
    });

    srv.bind("unregisterService", [&](std::string const& service, int id) -> int  {
    	if(id > 0)
    	{
	    	auto it = services.find(service);
	    	if(it != services.end() && it->second.id == id)
	    	{
	    		std::cout << "service deregistration " << service << " as is " << id << std::endl;
	    		services.erase(it);
	    		return 0;
	    	}
	    	else
	    	{
	    		return 0;
	    	}
    	}
    	else
    	{
	        return 0;
    	}
    });

    srv.bind("lookupService", [&](std::string const& service) -> std::tuple<std::string,int>  {

    	auto it = services.find(service);
    	if (it == services.end())
    	{
			std::cout << "service lookup not found " << service << std::endl;
    		return std::make_tuple(std::string(),0);
    	}
    	else
    	{
			std::cout << "service lookup found " << service << " as " << it->second.ip << ":" << it->second.port << std::endl;
	        return std::make_tuple(it->second.ip,it->second.port);
    	}
    });

    srv.bind("listServices", [&]() -> std::vector<std::string> {
    	std::vector<std::string> r;
    	for(auto & kv : services)
    	{
    		r.push_back(kv.first);
    	}
        return r;
    });

    srv.run();
    return 0;
}
