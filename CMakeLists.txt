


add_definitions(--std=c++11)
include_directories(include)
# include only
add_library(rpclibreg INTERFACE)
#target_sources(rpclibreg INTERFACE include/rpcreg_client.hpp)
set_property(TARGET rpclibreg PROPERTY INTERFACE_LINK_LIBRARIES rpc)


#target_link_libraries(rpclibreg rpc)

# core
add_executable(rpccore src/rpccore.cpp)
target_link_libraries(rpccore rpc)

# example
add_executable(client src/client.cpp)
target_link_libraries(client rpclibreg)

# example
add_executable(provider src/provider.cpp)
target_link_libraries(provider rpclibreg)