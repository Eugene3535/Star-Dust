#pragma once

#include <string>
#include <filesystem>

#include "GfxApiExport.hpp"


class GFX_API FileProvider
{
public:
    explicit FileProvider(const char* argv) noexcept;

    static std::filesystem::path findPathToFile(const std::string& filename) noexcept;

private:
    std::filesystem::path m_exeDir;
};