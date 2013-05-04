#include <getopt.h>
#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/OlaCallbackClient.h>
#include <ola/OlaClientWrapper.h>
#include <ola/io/SelectServer.h>
#include <iostream>
#include <string>
#include <vector>

using ola::NewSingleCallback;
using ola::OlaCallbackClient;
using ola::OlaCallbackClientWrapper;
using ola::OlaInputPort;
using ola::io::SelectServer;
using std::cout;
using std::endl;
using std::setw;
using std::string;
using std::vector;


int SendDmx(OlaCallbackClientWrapper *wrapper) {
  SelectServer *ss = wrapper->GetSelectServer();
  OlaCallbackClient *client = wrapper->GetClient();
  ola::DmxBuffer buffer;
  int i;
  for(i=0;i<20;i++)
  {buffer.SetChannel(i,i);}

  if (!client->SendDmx(1, buffer)) {
    cout << "Send DMX failed" << endl;
    return 1;
  }
  return 0;
}

void PatchComplete(SelectServer *ss, const string &error) {
  if (!error.empty())
    cout << error << endl;
  ss->Terminate();
  }

void Patch(OlaCallbackClientWrapper *wrapper) {
  SelectServer *ss = wrapper->GetSelectServer();
  OlaCallbackClient *client = wrapper->GetClient();
 
  client->Patch(0,0,ola::INPUT_PORT,ola::PATCH, 1,NewSingleCallback(&PatchComplete, ss));
}

int main(int argc, char *argv[]) {
  ola::InitLogging(ola::OLA_LOG_WARN, ola::OLA_LOG_STDERR);
  OlaCallbackClientWrapper ola_client;

   if (!ola_client.Setup())
    return -1;
  
  Patch(&ola_client);

  SendDmx(&ola_client);
 
return 0;
}
