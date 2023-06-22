#pragma once

#include "optional.hpp"
#include <string>
#include <variant>
#include <vector>

namespace rd {

struct user_1 {};
struct user_2 {};

using user_t = std::variant<user_1, user_2>;

struct conversation_entry_t {
  user_t user;
  std::string message;
};

using conversation = std::vector<conversation_entry_t>;
using review = std::string;

using feedback_t = std::variant<conversation, review>;

struct metadata_t {
  std::string id;
  std::string source;
  tl::optional<std::string> country;
  tl::optional<std::string> app_version;
  // NOTE: Can include more optional fields as per more data sources
};

struct schema_t {
  metadata_t metadata;
  feedback_t feedback;
};
} // namespace rd
