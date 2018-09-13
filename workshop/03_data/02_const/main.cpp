
#include <functional>
#include <string>
#include <iostream>
#include <mutex>

class test {
public:
    test()
    {
    }

    // const member functions need to leave the object bit-by-bit unchanged
    // or the changes need to be synchronized
    std::string data() const
    {
        std::lock_guard<std::mutex> lock(m_data_lock);
        // ... some expensive initialization
        return m_data;
    }

private:
    mutable std::mutex m_data_lock;
    mutable std::string m_data;
};


int main(int argc, char *argv[])
{
}

