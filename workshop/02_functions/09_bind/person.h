
#ifndef PERSON_H
#define PERSON_H

class person {
public:
    person(std::string name,
           std::string surname)
        : m_name(name)
        , m_surname(surname)
    {
    }

    std::string name() const
    {
        return m_name;
    }

    std::string surname() const
    {
        return m_surname;
    }

private:
    std::string m_name;
    std::string m_surname;

};

#endif /* !PERSON_H */

