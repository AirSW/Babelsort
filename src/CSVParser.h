#include <nan.h>
#include <string>

class CSVParser : public Nan::AsyncWorker
{
private:
    Nan::Persistent<v8::Promise::Resolver>* promiseResolver;
    std::string csvPath;
    std::vector<std::string> csvRecords;
    v8::Local<v8::Array> result;
public:
    static NAN_METHOD(Init);
    virtual void Execute() override;
    virtual void HandleOKCallback() override;
    CSVParser(std::string csvPath, Nan::Persistent<v8::Promise::Resolver>* promiseResolver);
    ~CSVParser();
};
