#include <catch.hpp>
#include "Tools/Launcher.h"

TEST_CASE("Without arguments") {
    char* query[] = {const_cast<char*>("./image_processor")};  // NOLINT
    Launcher launcher;
    REQUIRE_NOTHROW(launcher.Start(1, query));
}

void ExceptionMessage(int size, char* query[]) {
    Launcher launcher;
    launcher.Start(size, query);
}

TEST_CASE("Exceptions_Crop") {
    char* query_1[6] = {const_cast<char*>("./image_processor"),                                  // NOLINT
                        const_cast<char*>("/tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                        const_cast<char*>("./"),                                                 // NOLINT
                        const_cast<char*>("-crop"),                                              // NOLINT
                        const_cast<char*>("1000"),                                               // NOLINT
                        const_cast<char*>("-1000")};                                             // NOLINT

    REQUIRE_THROWS_WITH(ExceptionMessage(2, query_1), "ERROR: Not enough arguments");
    REQUIRE_THROWS_WITH(ExceptionMessage(3, query_1), "ERROR: Wrong output path");
    REQUIRE_THROWS_WITH(ExceptionMessage(4, query_1), "ERROR: Not enough arguments for -crop");
    REQUIRE_THROWS_WITH(ExceptionMessage(6, query_1), "ERROR: Wrong argument for -crop");
    query_1[5] = const_cast<char*>("1000");  // NOLINT
    REQUIRE_NOTHROW(ExceptionMessage(6, query_1));
}

TEST_CASE("Exceptions_EdgeDetection") {
    char* query_2[4] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                        const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                        const_cast<char*>("./"),                                                   // NOLINT
                        const_cast<char*>("-edge")};                                               // NOLINT
    REQUIRE_THROWS_WITH(ExceptionMessage(4, query_2), "ERROR: Not enough arguments for -edge");
}

TEST_CASE("Exceptions_GaussianBlur") {
    char* query_3[5] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                        const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                        const_cast<char*>("/Users/macs/CppProjects/PoplachoSpasenii.bmp"),         // NOLINT
                        const_cast<char*>("-blur"),                                                // NOLINT
                        const_cast<char*>("-0.5")};                                                // NOLINT
    REQUIRE_THROWS_WITH(ExceptionMessage(4, query_3), "ERROR: Not enough arguments for -blur");
    REQUIRE_THROWS_WITH(ExceptionMessage(5, query_3), "ERROR: Wrong argument for -blur");
    query_3[4] = const_cast<char*>("0.5");  // NOLINT
    REQUIRE_NOTHROW(ExceptionMessage(5, query_3));
}

TEST_CASE("Exceptions_FishEye") {
    char* query_4[5] = {const_cast<char*>("./image_processor"),                                    // NOLINT
                        const_cast<char*>("../tasks/image_processor/test_script/data/lenna.bmp"),  // NOLINT
                        const_cast<char*>("/Users/macs/CppProjects/PoplachoSpasenii.bmp"),         // NOLINT
                        const_cast<char*>("-fish_eye"),                                            // NOLINT
                        const_cast<char*>("-0.3")};                                                // NOLINT
    REQUIRE_THROWS_WITH(ExceptionMessage(4, query_4), "ERROR: Not enough arguments for -fisheye");
    REQUIRE_THROWS_WITH(ExceptionMessage(5, query_4), "ERROR: Wrong argument for -fisheye");
    query_4[4] = const_cast<char*>("0.3");  // NOLINT
    REQUIRE_NOTHROW(ExceptionMessage(5, query_4));
}