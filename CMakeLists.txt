cmake_minimum_required(VERSION 3.20)
project(NodeClang)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_JS_VERSION "7.3.0")
set(CMAKE_JS_INC
    "${CMAKE_CURRENT_LIST_DIR}/node_modules/node-api-headers/include;${CMAKE_CURRENT_LIST_DIR}/node_modules/node-addon-api"
)

if(WIN32)
    set(CMAKE_JS_SRC "${CMAKE_CURRENT_LIST_DIR}/node_modules/cmake-js/lib/cpp/win_delay_load_hook.cc")
endif()

set(NODE_RUNTIME "node")
set(NODE_RUNTIMEVERSION "20.11.1")

# set(NODE_ARCH "x64")
if(WIN32)
    set(CMAKE_JS_LIB "${CMAKE_BINARY_DIR}/node.lib")
    set(CMAKE_JS_NODELIB_DEF "${CMAKE_CURRENT_LIST_DIR}/node_modules/node-api-headers/def/node_api.def")
    set(CMAKE_JS_NODELIB_TARGET ${CMAKE_JS_LIB})
endif()

if(WIN32)
    set(CMAKE_SHARED_LINKER_FLAGS "/delayload:node.exe")
    link_libraries(delayimp)
elseif(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "-undefined dynamic_lookup")
endif()

add_definitions(-DNAPI_VERSION=8)
add_definitions(-DNODE_API_NO_EXTERNAL_BUFFERS_ALLOWED)

if(WIN32
   AND CMAKE_JS_NODELIB_DEF
   AND CMAKE_JS_NODELIB_TARGET)
    # Generate node.lib
    if(MSVC)
        execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET}
                                ${CMAKE_STATIC_LINKER_FLAGS})
    else()
        execute_process(COMMAND ${CMAKE_LINKER} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET}
                                ${CMAKE_STATIC_LINKER_FLAGS})
    endif()
endif()

set(NodeClang_src
    src/main.cpp
    src/api/index.cpp
    src/api/tu.cpp
    src/enums/enums.cpp
    src/enums/CXCursorKind.cpp
)

add_library(NodeClang SHARED ${CMAKE_JS_SRC} ${NodeClang_src})
set_target_properties(NodeClang PROPERTIES PREFIX "" SUFFIX ".node")
target_compile_definitions(NodeClang PRIVATE NODE_ADDON_API_ENABLE_TYPE_CHECK_ON_AS)
target_include_directories(NodeClang PRIVATE ${CMAKE_JS_INC} third_party)
target_link_libraries(NodeClang PRIVATE ${CMAKE_JS_LIB})