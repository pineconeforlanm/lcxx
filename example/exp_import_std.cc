//
// Created by lanm on 2025/8/6.
//
#include <yaml-cpp/yaml.h>
#include <ylt/struct_yaml/yaml_reader.h>
#include <ylt/struct_yaml/yaml_writer.h>

#include <cstdlib>
#include <ylt/easylog.hpp>

#define LEXICAL_CAST_YAML(Type)                              \
  template <>                                                \
  class lcxx::base::config::LexicalCast<std::string, Type> { \
   public:                                                   \
    auto operator()(const std::string& str) const -> Type {  \
      Type type;                                             \
      struct_yaml::from_yaml(type, str);                     \
      return type;                                           \
    };                                                       \
  };                                                         \
                                                             \
  template <>                                                \
  class lcxx::base::config::LexicalCast<Type, std::string> { \
   public:                                                   \
    auto operator()(const Type& type) const -> std::string { \
      std::string str;                                       \
      struct_yaml::to_yaml(type, str);                       \
      return str;                                            \
    };                                                       \
  }

import lcxx.base.config;
import lcxx.base.utils;
import std;

struct ConfigPerson {
  std::string name;
  int age;
  // ConfigPerson(std::string n, int a) : name(std::move(n)), age(a) {}
  auto operator==(const ConfigPerson& rhs) const -> bool { return name == rhs.name && age == rhs.age; }
};
YLT_REFL(ConfigPerson, name, age);

class Person {
 public:
  std::string name;
  int age = 0;
  bool sex = false;
  Person() = default;
  auto toString() const -> std::string {
    std::stringstream ss;
    ss << "[Person name=" << name << " age=" << age << " sex=" << sex << "]";
    return ss.str();
  }

  bool operator==(const Person& oth) const { return name == oth.name && age == oth.age && sex == oth.sex; }
};
YLT_REFL(Person, name, age, sex);

class Pinecone {
 public:
  Pinecone() = default;

  ~Pinecone() = default;

  Pinecone(const std::string_view& name, const int age) : name_(name), age_(age) {}

  friend auto operator<<(std::ostream& os, const Pinecone& pinecone) -> std::ostream& {
    os << pinecone.name_ << " " << pinecone.age_;
    return os;
  }

  auto operator==(const Pinecone& rhs) const -> bool { return name_ == rhs.name_ && age_ == rhs.age_; }

  static constexpr auto get_alias_field_names(Pinecone*) {
    return std::array{ylt::reflection::field_alias_t{"name", 0}, ylt::reflection::field_alias_t{"age", 1}};
  }
  YLT_REFL(Pinecone, name_, age_);

 private:
  std::string name_;
  int age_{};
};

LEXICAL_CAST_YAML(ConfigPerson);
LEXICAL_CAST_YAML(Person);
LEXICAL_CAST_YAML(Pinecone);

auto g_person_val_config =
    lcxx::base::config::Config::Lookup("root.ref.family.person", ConfigPerson("bob", 36), "system ref family person");

auto g_pinecone_val_config =
    lcxx::base::config::Config::Lookup("root.ref.family.pinecone", Pinecone{"body", 366}, "system ref family pinecone");

auto g_no_int_config_var = lcxx::base::config::Config::Lookup("system.no_int", 8080, "system no_int");

auto g_no_double_config_var = lcxx::base::config::Config::Lookup("double", 6.3699, "double");

auto g_person = lcxx::base::config::Config::Lookup("class.person", Person(), "system person");

auto exp_import_std_main(int argc, char** argv) -> int {
  try {
    std::println("this is exp_import_std_main, argc: {}, argv[0]: {}", argc, argv[0]);

    std::println("lcxx.utils version: {}", lcxx::base::utils::version());

    std::println("boost version: {}", lcxx::base::utils::boost::lib_version());

    ELOGI << g_no_int_config_var->GetValue();
    ELOGI << g_no_double_config_var->GetValue();
    ELOGI << g_pinecone_val_config->GetValue();
    ELOGI << g_person_val_config->GetValue().name << ":" << g_person_val_config->GetValue().age;
    ELOGI << g_person->GetValue().toString();
    lcxx::base::config::Config::LoadFromFile("./config/test_config.yaml");
    ELOGI << g_no_int_config_var->GetValue();
    ELOGI << g_no_double_config_var->GetValue();
    ELOGI << g_pinecone_val_config->GetValue();
    ELOGI << g_person_val_config->GetValue().name << ":" << g_person_val_config->GetValue().age;
    ELOGI << g_person->GetValue().toString();
  } catch (std::exception& exp) {
    std::cerr << "Main Exception:" << exp.what() << '\n';
  }
  return EXIT_SUCCESS;
}

auto real_main(const int argc, char** argv) -> int {
  try {
    return exp_import_std_main(argc, argv);
  } catch (const std::exception& exp) {
    std::cerr << exp.what() << '\n';
  }
  return 0;
}

auto main(const int argc, char** argv) -> int { return real_main(argc, argv); }