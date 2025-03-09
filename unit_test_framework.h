#ifndef UNIT_TEST_FRAMEWORK_H
#define UNIT_TEST_FRAMEWORK_H

#include <map>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <memory>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include <cstdlib>
#include <iterator>
#include <algorithm>
#include <exception>
#include <stdexcept>

#include <ciso646>

using Test_func_t = void (*)();

#define TEST(name)                                                            \
    static void name();                                                       \
    static TestRegisterer register_##name((#name), name);                     \
    static void name()

#define TEST_MAIN()                                                           \
    int main(int argc, char** argv) {                                         \
        return TestSuite::get().run_tests(argc, argv);                        \
    }                                                                         \
    TEST_SUITE_INSTANCE();

struct TestCase {
    TestCase(const std::string& name_, Test_func_t test_func_)
        : name(name_), test_func(test_func_) {}

    void run(bool quiet_mode);
    void print(bool quiet_mode);

    std::string name;
    Test_func_t test_func;
    std::string failure_msg{};
    std::string exception_msg{};
};

class TestSuite {
public:
    static TestSuite& get() {
        if (not instance) {
            instance = new TestSuite;
        }
        return *instance;
    }

    void add_test(const std::string& test_name, Test_func_t test) {
        tests_.insert({test_name, TestCase{test_name, test}});
    }

    int run_tests(int argc, char** argv);
    void print_results();

    void enable_quiet_mode() {
        quiet_mode = true;
    }

    std::ostream& print_test_names(std::ostream& os) {
        for (const auto& test_pair : tests_) {
            os << test_pair.first << '\n';
        }
        return os;
    }

    friend class TestSuiteDestroyer;

private:
    TestSuite() {
        auto func = []() {
            if (TestSuite::incomplete) {
                std::cout << "ERROR: premature call to exit()" << std::endl;
                std::abort();
            }
        };
        std::atexit(func);
#ifdef _GLIBCXX_HAVE_AT_QUICK_EXIT
        std::at_quick_exit(func);
#endif
    }
    TestSuite(const TestSuite&) = delete;
    bool operator=(const TestSuite&) = delete;
    ~TestSuite() {}

    std::vector<std::string> get_test_names_to_run(int argc, char** argv);

    static TestSuite* instance;
    std::map<std::string, TestCase> tests_;

    bool quiet_mode = false;
    static bool incomplete;
};

class TestSuiteDestroyer {
public:
    ~TestSuiteDestroyer() {
        delete TestSuite::instance;
    }
};

class TestRegisterer {
public:
    TestRegisterer(const std::string& test_name, Test_func_t test) {
        TestSuite::get().add_test(test_name, test);
    }
};

class TestFailure {
public:
    TestFailure(std::string reason, int line_number, const char* assertion_text)
        : reason_m(std::move(reason)), line_number_m(line_number),
          assertion_text_m(assertion_text) {}

    std::ostream& print(std::ostream& os) const {
        os << "In " << assertion_text_m << ", line " << line_number_m << ":\n"
           << reason_m << '\n';
        return os;
    }

    std::string to_string() const {
        std::ostringstream oss;
        print(oss);
        return oss.str();
    }

private:
    std::string reason_m;
    int line_number_m;
    const char* assertion_text_m;
};
std::ostream& operator<<(std::ostream& os, const TestFailure& test_failure);

#define TEST_SUITE_INSTANCE()                                                 \
    static TestSuiteDestroyer destroyer;                                      \
    bool TestSuite::incomplete = false;                                       \
    TestSuite* TestSuite::instance = &TestSuite::get()

void assert_true(bool value, int line_number, const char* assertion_text) {
    if (value) {
        return;
    }
    std::ostringstream reason;
    reason << "Expected true, but was false";
    throw TestFailure(reason.str(), line_number, assertion_text);
}

void assert_false(bool value, int line_number, const char* assertion_text) {
    if (not value) {
        return;
    }
    std::ostringstream reason;
    reason << "Expected false, but was true";
    throw TestFailure(reason.str(), line_number, assertion_text);
}

#endif  // UNIT_TEST_FRAMEWORK_H
