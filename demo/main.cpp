#include <builder.hpp>
#include "iostream"
#include "boost/program_options.hpp"

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("program options");
  desc.add_options()("config", po::value<std::string>(), "config of build")(
      "install", "to _install dir")(
      "pack", "to tar.gz")(
      "timeout", po::value<size_t>(), "timeout in milliseconds")(
      "help", "learn about program options");
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 0;
  }
  builder *b = nullptr;
  if (vm.count("timeout"))
    b = new builder(vm["timeout"].as<size_t>());
  else
    b = new builder();
  if (vm.count("config"))
    b->set_build(vm["config"].as<std::string>());
  else
    b->set_build("Debug");
  if (vm.count("install")) b->set_install();
  if (vm.count("pack")) b->set_pack();
  b->run();
  delete b;
  return 0;
}