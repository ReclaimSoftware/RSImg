#include <RSTest.h>
#include <RSImg.h>
#include <string.h>

void test_RSImgFreadPPMP6Header() {
    DESCRIBE("RSImgFreadPPMP6Header");

    IT("errors for an empty file") {
        uint32_t width, height, headerSize;
        FILE *file = assert_fopen("fixtures/empty_file", "r");
        int ok = RSImgFreadPPMP6Header(file, &width, &height, &headerSize);
        assert_zero(ok);
        fclose(file);
    }

    XIT("errors if the header is a valid P4\n'");
    XIT("errors if the header is a valid P5\n'");
    XIT("errors if the maximum value is not 255\n'");

    IT("freads 1280x720 P6 header") {
        uint32_t width, height, headerSize;
        FILE *file = assert_fopen("fixtures/p6-header-720.txt", "r");
        int ok = RSImgFreadPPMP6Header(file, &width, &height, &headerSize);
        assert_one(ok);
        assert_ints_equal(width, 1280);
        assert_ints_equal(height, 720);
        assert_ints_equal(headerSize, 16);
        fclose(file);
    }

    IT("freads 2880-1800 P6 header") {
        uint32_t width, height, headerSize;
        FILE *file = assert_fopen("fixtures/p6-header-laptop.txt", "r");
        int ok = RSImgFreadPPMP6Header(file, &width, &height, &headerSize);
        assert_one(ok);
        assert_ints_equal(width, 2880);
        assert_ints_equal(height, 1800);
        assert_ints_equal(headerSize, 17);
        fclose(file);
    }

    IT("leaves the FILE at the right position") {
        uint32_t width, height, headerSize;
        FILE *file = assert_fopen("fixtures/p6-header-720.txt", "r");
        RSImgFreadPPMP6Header(file, &width, &height, &headerSize);
        uint32_t size = strlen("...pixels...");
        uint8_t data[size];
        fread(data, size, 1, file);
        assert_data_equal(data, (uint8_t *)"...pixels...", size);
        fclose(file);
    }
}
