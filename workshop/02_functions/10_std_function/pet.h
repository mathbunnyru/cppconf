
#ifndef PET_H
#define PET_H

class pet {
public:
    pet(std::string name)
        : m_name(name)
    {
    }

    std::string name() const
    {
        return m_name;
    }

private:
    std::string m_name;

};

#endif /* !PET_H */

