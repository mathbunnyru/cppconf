
#include <functional>
#include <string>
#include <iostream>


class test {
public:
    test(std::string data)
        : m_data(data)
    {
        std::cout
            << "default constructor"
            << std::endl;
    }

    test(const test &original) = delete;

    test(test &&original)
    {
        std::swap(m_data, original.m_data);
        std::cout
            << "move constructor"
            << std::endl;
    }

    // We do not want to have mutation, setters are banned
    // void set_data(const std::string &data)
    // {
    //     m_data = data;
    // }

    // test with_appended_data(const std::string &new_data) const &
    // {
    //     // We can not implement this because we blocked
    //     // copying by deleting the copy constructor
    //     return {};
    // }

    test with_appended_data(const std::string &new_data) &&
    {
        m_data += " " + new_data;
        return std::move(*this);
    }

private:
    std::string m_data;
};


test test_fn(bool t)
{
    return t ? test("true")
             : test("false")
             ;
}


int main(int argc, char *argv[])
{
    std::cout << "t1:\n";
    test t1("first");

    // std::cout << "t2:\n";
    // test t2{t1}; // error: copy constructor is deleted

    std::cout << "t3:\n";
    test t3(test("third"));

    std::cout << "t4:\n";
    test t4{std::move(t1)};

    std::cout << "t5:\n";
    // Works on r-values
    test t5 = test_fn(true).with_appended_data("D2");

    std::cout << "t6:\n";
    // Can not be called on l-values
    // test t6 = t1.with_appended_data("D2");
    test t6 = std::move(t1).with_appended_data("D2");

    return 0;
}

