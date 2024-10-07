// OPTION 3 (HARDER) - GREEN SCREEN
// DO NOT SHARE

#include <cstdint>
#include <cstdlib>
#include <vector>
#include <iostream>

// Implement a blitting function which supports color-keyed transparency.

unsigned int const COLOR_KEY{
    0xFF000000};

struct PixelBuffer
{
    uint32_t *pixels; // assuming that it is stored in a one-dimensional array as it is more efficient in time and space
    int width;
    int height;
};

// Copies the entire image from `src` into a destination buffer `dest`.
// The pixel buffers have a top-left origin and are row-major.
// `offsetX` and `offsetY` denote the origin within `dest` where `src` should be copied.
// Any pixel that exactly matches `COLOR_KEY` should be skipped.
// You may assume input buffers are pre-allocated and sufficiently large to complete the requested operation.
void blit(PixelBuffer const *src, PixelBuffer *dest, size_t offsetX, size_t offsetY)
{
    size_t curDestRow = offsetY, curDestCol = offsetX;
    for (size_t row = 0; row < src->height; ++row)
        for (size_t column = 0; column < src->width; ++column)
        {
            // Check if the pixel matches the color key (i.e., it should be transparent)
            if (src->pixels[row * src->width + column] == COLOR_KEY)
                continue;
            curDestRow = offsetY + row;
            curDestCol = offsetX + column;
            dest->pixels[curDestRow * dest->width + curDestCol] = src->pixels[row * src->width + column];
        }
}

void readPixelBufferFromInput(PixelBuffer &buffer)
{
    std::cin >> buffer.width >> buffer.height;
    buffer.pixels = new uint32_t[buffer.width * buffer.height];
    for (int i = 0; i < buffer.width * buffer.height; ++i)
    {
        std::string hexValue;
        std::cin >> hexValue;
        buffer.pixels[i] = static_cast<uint32_t>(std::stoul(hexValue, nullptr, 16));
    }
}

void printBuffer(const PixelBuffer &buffer)
{
    for (int y = 0; y < buffer.height; ++y)
    {
        for (int x = 0; x < buffer.width; ++x)
        {
            std::cout << std::hex << buffer.pixels[y * buffer.width + x] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    size_t n; // number of test cases
    std::cin >> n;
    for (size_t i = 0; i < n; ++i)
    {
        PixelBuffer src, dest;
        readPixelBufferFromInput(src);
        readPixelBufferFromInput(dest);

        size_t offsetX, offsetY;
        std::cin >> offsetX >> offsetY;

        blit(&src, &dest, offsetX, offsetY);

        printBuffer(dest);
    }
    return 0;
}
