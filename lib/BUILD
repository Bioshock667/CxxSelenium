load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "CppSelenium",
    srcs = ["By.cpp", "Capabilities.cpp", "WebDriver.cpp","WebDriverCommandExecutor.cpp", "LocalServerExecutor.cpp",
	"FirefoxDriverExecutor.cpp", "ChromeDriverExecutor.cpp","IEDriverExecutor.cpp","JsonWireClient.cpp", "HttpClient.cpp", "WebDriverException.cpp", "WebElement.cpp", "SeleniumGridCommandExecutor.cpp"],
    hdrs = ["By.h", "Capabilities.h", "WebDriver.h", "WebDriverCommandExecutor.h", "LocalServerExecutor.h",
	"FirefoxDriverExecutor.h", "ChromeDriverExecutor.h", "IEDriverExecutor.h", "JsonWireClient.h", "HttpClient.h", "WebDriverException.h", "WebElement.h", "SeleniumGridCommandExecutor.h"],
	includes = ["../include"],
	deps = ["@boost//:beast","@boost//:log", "@boost//:asio"],
	visibility = ["//visibility:public"]
)
