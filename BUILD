load("@rules_cc//cc:defs.bzl", "cc_binary")
cc_binary(
	name = "CppSeleniumTest",
	srcs = ["SimpleTest.cpp"],
	includes = ["lib"],
	deps = ["//lib:CppSelenium","@boost//:beast","@boost//:log", "@boost//:asio"]
)

# cc_binary(
# 	name = "CppSeleniumTest",
# 	srcs = ["SimpleTest.cpp","include/static_libs/libboost_date_time-vc142-mt-x64-1_74.lib", "include/static_libs/libboost_regex-vc142-mt-x64-1_74.lib", 
# 	"include/static_libs/libboost_filesystem-vc142-mt-x64-1_74.lib","include/static_libs/libboost_log-vc142-mt-x64-1_74.lib",
# 	"include/static_libs/libboost_thread-vc142-mt-x64-1_74.lib","include/static_libs/libboost_log_setup-vc142-mt-x64-1_74.lib",
# 	"include/static_libs/libboost_chrono-vc142-mt-x64-1_74.lib","include/static_libs/libboost_atomic-vc142-mt-x64-1_74.lib"],
# 	includes = ["lib", "include/boost_libs"],
# 	deps = ["//lib:CppSelenium"]
# )