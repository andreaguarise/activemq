/*
 * HelloWorldProducer.h
 *
 *  Created on: Oct 18, 2012
 *      Author: root
 */

#ifndef HELLOWORLDPRODUCER_H_
#define HELLOWORLDPRODUCER_H_

#include "GeneralHeader.h"

using namespace activemq::core;
using namespace decaf::util::concurrent;
using namespace decaf::util;
using namespace decaf::lang;
using namespace cms;
using namespace std;

namespace activemqappl {
class HelloWorldProducer : public Runnable {
private:

    Connection* connection;
    Session* session;
    Destination* destination;
    MessageProducer* producer;
    int numMessages;
    bool useTopic;
    bool sessionTransacted;
    string brokerURI;
    string text;

    HelloWorldProducer(const HelloWorldProducer&);
    HelloWorldProducer& operator=(const HelloWorldProducer&);
    void cleanup();

public:

    HelloWorldProducer(const std::string& brokerURI, int numMessages, bool useTopic = false, bool sessionTransacted = false) :
        connection(NULL),
        session(NULL),
        destination(NULL),
        producer(NULL),
        numMessages(numMessages),
        useTopic(useTopic),
        sessionTransacted(sessionTransacted),
        brokerURI(brokerURI) {
    }

    virtual ~HelloWorldProducer() throw();

    void close();

    virtual void run();

    void setText(string test);
    string getText();


};

} /* namespace activemqappl */
#endif /* HELLOWORLDPRODUCER_H_ */
