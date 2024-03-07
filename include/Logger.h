#include <iostream>


namespace gbc
{
class Logger
{
    std::ostream *mOut; 
    bool          mOwner;
public:
    Logger()
    {

    }
  
    virtual ~Logger()
    {
        setStream(0, false);
    }

    void setStream( std::ostream* stream, bool owner )
    {
        if(mOwner)
            delete mOut;
        mOut = stream;
        mOwner = owner;
    }
    template<class T>
    Logger& operator << (const T& object)
    {
        if(!mOut)
            throw std::runtime_error("No stream set for Logger class");
        (*mOut) << object;
        return *this;
    }

};

class LogSingleton
{
    public:
    static Logger& Instance()
    {
        static auto logger = std::make_shared<Logger>();
        return *logger;
    }
};

#define INIT_LOGGER(stream, val) LogSingleton::Instance().setStream(stream, val)
#define LOG_STREAM LogSingleton::Instance()
#define LOG_END '\n'
}