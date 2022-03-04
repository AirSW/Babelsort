#include "./CSVParser.h"
#include <fstream>
#include <exception>

std::vector<std::string> split(std::string str, std::string delimiter){
    std::vector<std::string> results;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        results.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    token = str.substr(0, pos);
    results.push_back(token);

    return results;
}

CSVParser::CSVParser(std::string csvPath, Nan::Persistent<v8::Promise::Resolver>* promiseResolver): AsyncWorker(nullptr){
    this->csvPath = csvPath;
    this->promiseResolver = promiseResolver;
}

CSVParser::~CSVParser(){
}

void CSVParser::Execute(){
    std::ifstream f(this->csvPath);
    std::string line;
    while (std::getline(f, line)){
        csvRecords.push_back(line);
    }
}

void CSVParser::HandleOKCallback(){
    Nan::HandleScope scope;
    this->result = Nan::New<v8::Array>(csvRecords.size() - 1);
    v8::Isolate* isolate = Nan::GetCurrentContext()->GetIsolate();
    auto headers = split(csvRecords[0], ",");
    for (int i = 1; i < csvRecords.size(); i ++){
        v8::Local<v8::Object> record = Nan::New<v8::Object>();
        auto values = split(csvRecords[i], ",");
        for (int j = 0; j < headers.size(); j ++){
            record->Set(v8::String::NewFromUtf8(isolate, headers[j].c_str()), Nan::New(values[j]).ToLocalChecked());
        }
        this->result->Set(i - 1, record);
    }
    auto resolver = Nan::New(*this->promiseResolver);
    resolver->Resolve(Nan::GetCurrentContext(), this->result);
}
