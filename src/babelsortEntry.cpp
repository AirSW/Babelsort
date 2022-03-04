#include <nan.h>
#include "CSVParser.h"

void Method(const Nan::FunctionCallbackInfo<v8::Value>& info){
  std::string csvPath = *Nan::Utf8String(info[0]->ToString(info.GetIsolate()));
  auto resolver = v8::Promise::Resolver::New(info.GetIsolate()->GetCurrentContext());
  auto persistent = new Nan::Persistent<v8::Promise::Resolver>(resolver.ToLocalChecked());
  CSVParser *parser = new CSVParser(csvPath, persistent);
  Nan::AsyncQueueWorker(parser);
  info.GetReturnValue().Set(resolver.ToLocalChecked()->GetPromise());
}

void Init(v8::Local<v8::Object> exports){
  Nan::HandleScope scope;
  Nan::SetMethod(exports, "parseCSV", Method);
}

NODE_MODULE(Parser, Init)