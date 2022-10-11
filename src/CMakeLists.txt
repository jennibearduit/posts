project(blogger)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( blogger blogger blogger.cpp )
target_include_directories( blogger PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( blogger ${CMAKE_SOURCE_DIR}/../ricardian )