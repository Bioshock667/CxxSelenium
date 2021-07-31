load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "com_github_nelhage_rules_boost",
    remote = "https://github.com/nelhage/rules_boost",
    branch = "master",
    # commit = "c13a880269cc044c4b5e90046625339836771d77",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()
