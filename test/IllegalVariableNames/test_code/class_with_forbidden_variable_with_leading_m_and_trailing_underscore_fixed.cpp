#include <string>

namespace my_namespace
{
    class test_class
    {
    public:
        test_class (const std::string& pippo, const std::string& pluto, const std::string& paperino) :
            m_pippo_(pippo),
            m_pluto_(pluto),
            m_paperino_(paperino)
        {}

        [[nodiscard]] std::string get_pippo () const
        {
            return m_pippo_;
        }

        [[nodiscard]] std::string get_pluto () const
        {
            return m_pluto_;
        }

        [[nodiscard]] std::string get_paperino () const
        {
            return m_paperino_;
        }


    private:
        std::string m_pippo_;
        std::string m_pluto_;
        std::string m_paperino_;
    }
}        // namespace my_namespace
