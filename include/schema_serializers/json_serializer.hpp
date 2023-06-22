#pragma once

#include "../overload.hpp"
#include "../schema.hpp"
#include <boost/hof.hpp>
#include <nlohmann/json.hpp>
#include <variant>

namespace rd {
namespace __detail {
using json = nlohmann::json;
inline auto serialize_metadata(rd::metadata_t metadata) {
  json j;
  j["id"] = metadata.id;
  j["source"] = metadata.source;
  if (metadata.country)
    j["country"] = metadata.country.value();
  if (metadata.app_version)
    j["app_version"] = metadata.app_version.value();
  return j;
}

inline auto serialize_conversation_entry(rd::conversation_entry_t entry) {
  json j;
  j["message"] = entry.message;
  if (entry.user.index() == 0)
    j["user"] = "user1";
  else
    j["user"] = "user2";
  return j;
}

inline auto serialize_converstion(rd::conversation conversation) {
  json j;
  j["feedback_type"] = "conversation";
  for (auto const &conversation_entry : conversation) {
    j["data"].push_back(serialize_conversation_entry(conversation_entry));
  }
  return j;
}

inline auto serialize_review(rd::review review) {
  json j;
  j["feedback_type"] = "review";
  j["data"] = review;
  return j;
}

inline auto serialize_feedback(rd::feedback_t feedback) {
  return std::visit(
      rd::overloaded{
          BOOST_HOF_LIFT(serialize_converstion),
          BOOST_HOF_LIFT(serialize_review),
      },
      feedback);
}
} // namespace __detail

inline auto serialize_to_json(rd::schema_t schema) {
  using json = nlohmann::json;
  json j;
  j["metadata"] = __detail::serialize_metadata(schema.metadata);
  j["feedback"] = __detail::serialize_feedback(schema.feedback);
  return j;
}
} // namespace rd
