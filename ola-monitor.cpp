#include <errno.h>
#include <ola/Callback.h>
#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/OlaCallbackClient.h>
#include <ola/OlaClientWrapper.h>
#include <ola/io/SelectServer.h>
#include <string>
#include <iostream>

using ola::DmxBuffer;
using ola::OlaCallbackClientWrapper;
using ola::OlaCallbackClient;

using ola::io::SelectServer;
using std::string;
using std::cout;
using std::endl;

void RegisterComplete(const string &error) {
  if (!error.empty()) {
  
    std::cerr << "Register command failed with " << errno <<
      std::endl;
    ola::OlaCallbackClientWrapper m_client;
    m_client.GetSelectServer()->Terminate();
  }
}


void NewDmx(unsigned int universe,
            const DmxBuffer &data, 
            const std::string &error) {
  OLA_INFO << "Received " << (int) data.Size() <<
    " channels for universe " << (int) universe;
int i;
	for(i=0;i<20;i++)
   cout<<(int)data.Get(i)<<endl;
}

int main() {
  ola::InitLogging(ola::OLA_LOG_INFO, ola::OLA_LOG_STDERR);
  ola::OlaCallbackClientWrapper m_client;

  if (!m_client.Setup())
    return -1;

  ola::OlaCallbackClient *client = m_client.GetClient();
  client->SetDmxCallback(ola::NewCallback(&NewDmx));
  client->RegisterUniverse(1,ola::REGISTER,ola::NewSingleCallback(&RegisterComplete));

  m_client.GetSelectServer()->Run();
}

