#include <string>

namespace my_namespace
{
    class test_class
    {
    public:
        test_class (const std::string& pippo, const std::string& pluto, const std::string& paperino) :
            m_pippo(pippo),
            m_pluto(pluto),
            m_paperino(paperino)
        {}

        [[nodiscard]] std::string get_pippo () const
        {
            return m_pippo;
        }

        [[nodiscard]] std::string get_pluto () const
        {
            return m_pluto;
        }

        [[nodiscard]] std::string get_paperino () const
        {
            return m_paperino;
        }


    private:
        std::string pippo_;
        std::string pluto_;
        std::string paperino_;
    }
}        // namespace my_namespace
