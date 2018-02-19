#include "rpcreg_client.hpp"
#include <iostream>

int main() {
    std::shared_ptr<rpc::client> pc = rpcLookup("echo");

    if(!pc)
    {
    	std::cout << "service not found service";
    	return -1;
    }

    rpc::client & c = *pc;

	std::cout << "enter text:\n";
    std::string text;
    while (std::getline(std::cin, text)) {
        if (!text.empty()) {
            std::string result(c.call("echo", text).as<std::string>());
            std::cout << "> " <<  result << std::endl;
        }
    }
}
