/************************************************************************
Copyright 2017-2019 eBay Inc.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**************************************************************************/

#include <libjungle/jungle.h>

// For removing directory purpose, not needed in practice.
#include "test_common.h"

using namespace jungle;

int main() {
    const static std::string path = "./db_example_get_set_del";

    // Remove existing DB first.
    TestSuite::clearTestFile(path);

    // Initialize global resources with default config.
    jungle::init(GlobalConfig());

    // Open an instance at the given path, with default config.
    DB* db = nullptr;
    DB::open(&db, path, DBConfig());

    // Set {"hello", "world"} pair.
    db->set( KV("hello", "world") );

    // Search key "hello", should return "world".
    SizedBuf value_out;
    Status s;
    s = db->get( SizedBuf("hello"), value_out );
    std::cout << "return code " << s << ", "
              << value_out.toString() << std::endl;
    // Should free the memory of value after use.
    value_out.free();

    // Delete a pair corresponding to key "hello".
    db->del( SizedBuf("hello") );

    // Search key "hello", should return error.
    s = db->get( SizedBuf("hello"), value_out );
    std::cout << "return code " << s << std::endl;

    // Close and free DB instance.
    DB::close(db);

    // Release global resources.
    jungle::shutdown();

    return 0;
}

