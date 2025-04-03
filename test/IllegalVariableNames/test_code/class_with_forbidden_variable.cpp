#include <string>

namespace my_namespace
{
    class test_class
    {
    public:
        test_class (const std::string& pippo, const std::string& pluto, const std::string& paperino) :
            pippo(pippo),
            pluto(pluto),
            paperino(paperino)
        {}

        [[nodiscard]] std::string get_pippo () const
        {
            return pippo;
        }

        [[nodiscard]] std::string get_pluto () const
        {
            return pluto;
        }

        [[nodiscard]] std::string get_paperino () const
        {
            return paperino;
        }


    private:
        std::string pippo;
        std::string pluto;
        std::string paperino;
    }
}        // namespace my_namespace
