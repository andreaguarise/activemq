/*
 * helloWorldConsumer.h
 *
 *  Created on: Oct 16, 2012
 *      Author: root
 */

#ifndef HELLOWORLSCONSUMER_H_
#define HELLOWORLSCONSUMER_H_

#include "GeneralHeader.h"

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

namespace activemqappl{

class HelloWorldConsumer : public ExceptionListener,
                           public MessageListener,
                           public Runnable {
private:

    CountDownLatch latch;
    CountDownLatch doneLatch;
    Connection* connection;
    Session* session;
    MessageConsumer* consumer;
    long waitMillis;
    bool useTopic;
    bool sessionTransacted;
    std::string brokerURI;

    HelloWorldConsumer(const HelloWorldConsumer&);
    HelloWorldConsumer& operator=(const HelloWorldConsumer&);
    void cleanup();


public:

    HelloWorldConsumer(const string& brokerURI, int numMessages, bool useTopic = false, bool sessionTransacted = false, int waitMillis  = 30000)
    : latch(1),
    doneLatch(numMessages),
    connection(NULL),
    session(NULL),
    consumer(NULL),
    waitMillis(waitMillis),
    useTopic(useTopic),
    sessionTransacted(sessionTransacted),
    brokerURI(brokerURI){}


	virtual ~HelloWorldConsumer() throw();
    void close();
    void waitUntilReady();
    virtual void run();
    virtual void onMessage(const Message* message) throw();
    virtual void onException(const CMSException& ex AMQCPP_UNUSED);
};
}
#endif /* HELLOWORLSCONSUMER_H_ */
