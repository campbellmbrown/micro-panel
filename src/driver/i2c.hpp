#pragma once

#include <cstddef>
#include <cstdint>

namespace i2c
{
void init();
void transfer_blocking(std::uint8_t address, std::uint8_t *data, std::size_t length);
} // namespace i2c
