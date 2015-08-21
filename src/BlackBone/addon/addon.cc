#include <iostream>
#include <nan.h>
#include <string>

#include "../Config.h"
#include "../Process/Process.h"

using namespace blackbone;

/// Take this proc outside
/// functions so we can reuse it
Process proc;

void searchProcess(const Nan::FunctionCallbackInfo<v8::Value>& info) {

  LPCWSTR processName = (LPCWSTR) * v8::String::Value(info[0]->ToString());

  std::wcout << L"\r\nSearching for process...\n";

  std::vector<DWORD> found;
  Process::EnumByName( processName, found );

  if (found.size() > 0)
  {
      std::wcout << L"\nProcess Found. Attaching to process " << std::dec << found.front() << std::endl;

      if (proc.Attach( found.front() ) != STATUS_SUCCESS)
      {
          std::wcout << L"\nCan't attach to process, status code " << LastNtStatus() << " aborting\n\n";
          return;
      }

      info.GetReturnValue().Set(true);
  } else {
    info.GetReturnValue().SetUndefined();
  }

}

void readData(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	std::wcout << L"\nSearching for Data... ";

	int rtnValue = 0;
	proc.memory().Read(0x7FF97E7D1BD8, sizeof(rtnValue), &rtnValue);

	std::wcout << L"\nTHIS IS THE DATA " << std::dec << rtnValue << std::endl;

	info.GetReturnValue().Set(rtnValue);
}

void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("searchProcess").ToLocalChecked(),
	  Nan::New<v8::FunctionTemplate>(searchProcess)->GetFunction());
  exports->Set(Nan::New("readData").ToLocalChecked(),
	  Nan::New<v8::FunctionTemplate>(readData)->GetFunction());
}

NODE_MODULE(addon, Init)
