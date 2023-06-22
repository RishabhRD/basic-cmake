#include "optional.hpp"
#include "schema.hpp"
#include "schema_serializers/json_serializer.hpp"
#include <doctest/doctest.h>
#include <iostream>
#include <string>

using json = nlohmann::json;

TEST_CASE("Can serialize conversation") {
  rd::schema_t schema;
  schema.metadata = {
      .id = "playstore_enterpret.txt",
      .source = "File",
      .country = "India",
      .app_version = "4.1.2",
  };
  schema.feedback = rd::conversation{
      {rd::user_1{}, "Hello"},
      {rd::user_1{}, "Can you Help me"},
      {rd::user_2{}, "Yes How can I help you?"},
  };

  json expected = {
      {"metadata",
       json{
           {"id", "playstore_enterpret.txt"},
           {"source", "File"},
           {"country", "India"},
           {"app_version", "4.1.2"},
       }},
      {"feedback",
       {{"feedback_type", "conversation"},
        {"data",
         json{
             json{{"user", "user1"}, {"message", "Hello"}},
             json{{"user", "user1"}, {"message", "Can you Help me"}},
             json{{"user", "user2"}, {"message", "Yes How can I help you?"}},
         }}}},
  };

  REQUIRE_EQ(rd::serialize_to_json(schema), expected);
}

TEST_CASE("Can serialize review") {
  rd::schema_t schema;
  schema.metadata = {
      .id = "playstore_enterpret.txt",
      .source = "File",
      .country = "India",
      .app_version = "4.1.2",
  };
  schema.feedback = rd::review{"A great app, must use!"};

  json expected = {
      {"metadata",
       json{
           {"id", "playstore_enterpret.txt"},
           {"source", "File"},
           {"country", "India"},
           {"app_version", "4.1.2"},
       }},
      {"feedback",
       {{"feedback_type", "review"}, {"data", "A great app, must use!"}}},
  };

  REQUIRE_EQ(rd::serialize_to_json(schema), expected);
}

TEST_CASE("Is skipping null field") {
  rd::schema_t schema;
  schema.metadata = {
      .id = "playstore_enterpret.txt",
      .source = "File",
      .country = "India",
      .app_version = tl::nullopt,
  };
  schema.feedback = rd::review{"A great app, must use!"};

  json expected = {
      {"metadata",
       json{
           {"id", "playstore_enterpret.txt"},
           {"source", "File"},
           {"country", "India"},
       }},
      {"feedback",
       {{"feedback_type", "review"}, {"data", "A great app, must use!"}}},
  };

  REQUIRE_EQ(rd::serialize_to_json(schema), expected);
}
