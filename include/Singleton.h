#include <memory>

template<class t>
class Singleton
{
    public:
        Singleton(){};
        ~Singleton(){};


        inline static std::shared_ptr<T> Instance()
        {
         //   static std::shared_ptr<T> inst = std::make_shared<T>(T());
           // return inst;
        }

};