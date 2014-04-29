# @@@LICENSE
#
#      Copyright (c) 2014 LG Electronics, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# LICENSE@@@

include_directories(${CMAKE_SOURCE_DIR}/include/public/luna-service2++)

project(luna-service2++)
webos_add_compiler_flags(ALL -Wall "-std=gnu++0x")

set(SOURCE
    call.cpp
    error.cpp
    message.cpp
    palm_service.cpp
    server_status.cpp
    service.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE})
target_link_libraries(${PROJECT_NAME} luna-service2)

if (WEBOS_CONFIG_BUILD_TESTS)
    add_subdirectory(test)
else()
    message(STATUS "libluna-service2: skipping automatic tests")
endif()

webos_build_library(NAME ${PROJECT_NAME})