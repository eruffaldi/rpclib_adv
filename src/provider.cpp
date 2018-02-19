#include "rpc/server.h"
#include "rpcreg_client.hpp"

int main() {
    rpc::server srv((uint16_t)0);

    rpcProvider srvpro(srv,"echo"); // deregister on exist

    srv.bind("echo", [](std::string const& s) {
        return s;
    });

    srv.run();
    return 0;
}
