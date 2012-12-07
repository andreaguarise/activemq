/*
 * main.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: root
 */

#include "GeneralHeader.h"
#include "HelloWorldConsumer.h"
#include "HelloWorldProducer.h"

using namespace std;
using namespace decaf::lang;

using namespace activemqappl;

int main(int argc, char* argv[] ){
	    activemq::library::ActiveMQCPP::initializeLibrary();
	     {
	     std::cout << "=====================================================\n";
	     std::cout << "Starting the example:" << std::endl;
	     std::cout << "-----------------------------------------------------\n";


	     // Set the URI to point to the IP Address of your broker.
	     // add any optional params to the url to enable things like
	     // tightMarshalling or tcp logging etc.  See the CMS web site for
	     // a full list of configuration options.
	     //
	     //  http://activemq.apache.org/cms/
	     //
	     // Wire Format Options:
	     // =========================
	     // Use either stomp or openwire, the default ports are different for each
	     //
	     // Examples:
	     //    tcp://127.0.0.1:61616                      default to openwire
	     //    tcp://127.0.0.1:61616?wireFormat=openwire  same as above
	     //    tcp://127.0.0.1:61613?wireFormat=stomp     use stomp instead
	     //
	     // SSL:
	     // =========================
	     // To use SSL you need to specify the location of the trusted Root CA or the
	     // certificate for the broker you want to connect to.  Using the Root CA allows
	     // you to use failover with multiple servers all using certificates signed by
	     // the trusted root.  If using client authentication you also need to specify
	     // the location of the client Certificate.
	     //
	     //     System::setProperty( "decaf.net.ssl.keyStore", "<path>/client.pem" );
	     //     System::setProperty( "decaf.net.ssl.keyStorePassword", "password" );
	     //     System::setProperty( "decaf.net.ssl.trustStore", "<path>/rootCA.pem" );
	     //
	     // The you just specify the ssl transport in the URI, for example:
	     //
	     //     ssl://localhost:61617
	     //
	     std::string brokerURI =
	         "failover:(tcp://dgas-dev-28.to.infn.it:61616"
	 //        "?wireFormat=openwire"
	 //        "&transport.useInactivityMonitor=false"
	 //        "&connection.alwaysSyncSend=true"
	 //        "&connection.useAsyncSend=true"
	 //        "?transport.commandTracingEnabled=true"
	 //        "&transport.tcpTracingEnabled=true"
	 //        "&wireFormat.tightEncodingEnabled=true"
	         ")";

	     //============================================================
	     // set to true to use topics instead of queues
	     // Note in the code above that this causes createTopic or
	     // createQueue to be used in both consumer an producer.
	     //============================================================
	     bool useTopics = true;
	     bool sessionTransacted = false;
	     int numMessages = -1;
	     string text;

	     if(argc == 3){
	    	 numMessages = atoi(argv[1]);
	    	 text = argv[2];
	     }else{
	    	 cout << "No input messages, using 10 and 'Hello world' as default values " << endl;
	    	 numMessages = 10;
	    	 text = "Hello World!!! ";
	     }
	     HelloWorldProducer producer(brokerURI, numMessages, useTopics);
	     HelloWorldConsumer consumer(brokerURI, numMessages, useTopics, sessionTransacted);
	     producer.setText(text);
	     // Start the consumer thread.
	     Thread consumerThread(&consumer);
	     consumerThread.start();


	     // Wait for the consumer to indicate that its ready to go.
	     consumer.waitUntilReady();

	     // Start the producer thread.
	     Thread producerThread(&producer);
	     producerThread.start();

	     // Wait for the threads to complete.
	     producerThread.join();
	     consumerThread.join();

	  //   long long endTime = System::currentTimeMillis();
	 //    double totalTime = (double)(endTime - startTime) / 1000.0;

	     consumer.close();
	     producer.close();

	  //   std::cout << "Time to completion = " << totalTime << " seconds." << std::endl;
	     std::cout << "-----------------------------------------------------\n";
	     std::cout << "Finished with the example." << std::endl;
	     std::cout << "=====================================================\n";

	     }
	     activemq::library::ActiveMQCPP::shutdownLibrary();



}



