/*
 * HelloWorldProducer.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: root
 */

#include "HelloWorldProducer.h"
using namespace activemqappl;


    HelloWorldProducer::~HelloWorldProducer() throw(){
        cleanup();
    }

    void HelloWorldProducer::close() {
        this->cleanup();
    }

    void HelloWorldProducer::run() {

        try {

            // Create a ConnectionFactory
            auto_ptr<ConnectionFactory> connectionFactory(
                ConnectionFactory::createCMSConnectionFactory(brokerURI));

            // Create a Connection
            connection = connectionFactory->createConnection();
            connection->start();

            // Create a Session
            if (this->sessionTransacted) {
                session = connection->createSession(Session::SESSION_TRANSACTED);
            } else {
                session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
            }

            // Create the destination (Topic or Queue)
            if (useTopic) {
                destination = session->createTopic("TEST.FOO");
            } else {
                destination = session->createQueue("TEST.FOO");
            }

            // Create a MessageProducer from the Session to the Topic or Queue
            producer = session->createProducer(destination);
            producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);

            // Create the Thread Id String
            string threadIdStr = Long::toString(Thread::currentThread()->getId());

            // Create a messages
            string text = (string) getText() + " - " + threadIdStr;

            for (int ix = 0; ix < numMessages; ix++) {
                std::auto_ptr<TextMessage> message(session->createTextMessage(text));
                message->setIntProperty("Integer", ix);
                printf("Sent message #%d from thread %s\n", ix + 1, threadIdStr.c_str());
                producer->send(message.get());
            }

        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }

    void HelloWorldProducer::cleanup() {

        if (connection != NULL) {
            try {
                connection->close();
            } catch (cms::CMSException& ex) {
                ex.printStackTrace();
            }
        }

        // Destroy resources.
        try {
            delete destination;
            destination = NULL;
            delete producer;
            producer = NULL;
            delete session;
            session = NULL;
            delete connection;
            connection = NULL;
        } catch (CMSException& e) {
            e.printStackTrace();
        }
    }
    void HelloWorldProducer::setText(string text) {
    	this->text = text;
    }

    string HelloWorldProducer::getText(){
    	return text;
    }




