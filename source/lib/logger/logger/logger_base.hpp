#ifndef BRAWL_MASTERS_LOGGER_BASE_HPP
#define BRAWL_MASTERS_LOGGER_BASE_HPP

#include <filesystem>
#include <string>

#include "logger/logger_facade.hpp"

class logger_base {
protected:
  explicit logger_base(const std::string &name, std::filesystem::path path) { logger = std::make_unique<logger_decorator>(name, path); }
  logger_base() = delete;

  virtual ~logger_base() {}
  std::unique_ptr<logger_decorator> logger;
};

#endif // BRAWL_MASTERS_LOGGER_BASE_HPP