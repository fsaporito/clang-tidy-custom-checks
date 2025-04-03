#include <string>

namespace my_namespace
{
    class test_class
    {
    public:
        test_class (const std::string& pippo, const std::string& pluto, const std::string& paperino) :
            pippo_(pippo),
            pluto_(pluto),
            paperino_(paperino)
        {}

        [[nodiscard]] std::string get_pippo () const
        {
            return pippo_;
        }

        [[nodiscard]] std::string get_pluto () const
        {
            return pluto_;
        }

        [[nodiscard]] std::string get_paperino () const
        {
            return paperino_;
        }


    private:
        std::string pippo_;
        std::string pluto_;
        std::string paperino_;
    }
}        // namespace my_namespace
