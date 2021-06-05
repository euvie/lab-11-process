#ifndef INCLUDE_BUILDER_HPP_
#define INCLUDE_BUILDER_HPP_
#include "boost/process.hpp"
#include "async++.h"
#include "iostream"
#include "string"
#include "memory"
#include "condition_variable"
#include "mutex"

class builder {
 public:
  builder();
  explicit builder(const size_t& ms_timeout);
  void run();
  void set_build(const std::string &_config);
  void set_install();
  void set_pack();
  ~builder();

 private:
  std::function<void()>* build_func;
  std::function<void()>* install_func;
  std::function<void()>* pack_func;
  std::function<void()>* wait_for_timeout;
  std::atomic_bool timeout_flag;
  std::atomic_bool processes_completed;
  std::atomic_bool process_failed;
  std::unique_ptr<boost::process::child> current_process;
  std::string cmake_path;
  std::string config;
};

#endif  // INCLUDE_BUILDER_HPP_