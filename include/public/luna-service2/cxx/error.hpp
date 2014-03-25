// @@@LICENSE
//
//      Copyright (c) 2014 LG Electronics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// LICENSE@@@

#pragma once

#include <luna-service2/lunaservice.h>
#include <cstring>
#include <iostream>

namespace LS {

class Error
{
public:
    Error()
    {
        LSErrorInit(&_error);
    }

    ~Error()
    {
        LSErrorFree(&_error);
    }

    Error(Error &&other)
    {
        memcpy(&_error, &other._error, sizeof(_error));
        LSErrorInit(&other._error);
    }

    Error &operator=(Error &&other)
    {
        if (this != &other)
        {
            LSErrorFree(&_error);
            memcpy(&_error, &other._error, sizeof(_error));
            LSErrorInit(&other._error);
        }
        return *this;
    }

    // Disable copying from lvalue.
    Error(const Error &) = delete;
    Error& operator=(const Error &) = delete;

    LSError *get() { return &_error; }
    const LSError *get() const { return &_error; }
    LSError *operator->() { return &_error; }
    const LSError *operator->() const { return &_error; }

    bool isSet() const
    {
        return LSErrorIsSet(&_error);
    }

    void print(FILE *out) const
    {
        LSErrorPrint(&_error, out);
    }

    void log(PmLogContext context, const char *message_id)
    {
        LSErrorLog(context, message_id, &_error);
    }

private:
    LSError _error;

    friend std::ostream &operator<<(std::ostream &os, const Error &error)
    {
        return os << "LUNASERVICE ERROR " << error->error_code
                  << ": " << error->message
                  << " (" << error->func
                  << " @ " << error->file << ":" << error->line
                  << ")";
    }
};

} //namespace LS;