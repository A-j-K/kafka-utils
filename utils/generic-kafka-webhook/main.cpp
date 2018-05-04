
#include <string>
#include <vector>
#include <iostream>

#include "curler.hpp"
#include "kafka_conf.hpp"
#include "config/config_factory.hpp"
#include "event_cb.hpp"
#include "consume_cb.hpp"


int
main(int argc, char *argv[])
{
	int rval = 0;
	std::string errstr;
	std::vector<std::string> topics;
	Curler::ShPtr spCurler;
	GenericKafkaWebhook::EventCb::ShPtr spEventCb;
	GenericKafkaWebhook::ConsumeCb::ShPtr spConsumeCb;
	RdKafka::Conf *pKafkaConf = 0;
	RdKafka::Conf::ConfResult result;
	AbstractConfig::ShPtr spConfig;

	Curler::startup();
	try {
		spConfig = ConfigFactory::getConfigByFile(std::string("/etc/notifier.json"));
		pKafkaConf = KafkaConf::get(spConfig.get(), 0);
		spEventCb = GenericKafkaWebhook::EventCb::ShPtr(new GenericKafkaWebhook::EventCb());
		spConsumeCb = GenericKafkaWebhook::ConsumeCb::ShPtr(new GenericKafkaWebhook::ConsumeCb());
		result = pKafkaConf->set("consume_cb", spConsumeCb.get(), errstr);
		if(result != 0) {
			std::cout << "Bad callback " << errstr << std::endl;;
			exit(-1);
		}
		result = pKafkaConf->set("event_cb", spEventCb.get(), errstr);
		if(result != 0) {
			std::cout << "Bad callback " << errstr << std::endl;
			exit(-1);
		}
		RdKafka::KafkaConsumer *pConsumer = RdKafka::KafkaConsumer::create(pKafkaConf, errstr);
		if(!pConsumer) {
			std::cout << "Consumer error: " << errstr << "\n";
		}
#if 1
		topics.push_back(spConfig->getTopic());
		pConsumer->subscribe(topics);
		spCurler = Curler::ShPtr(new Curler(spConfig));

		while(true) {
			RdKafka::Message *pmsg;
			GenericKafkaWebhook::ConsumeCb cb;
			if((pmsg = pConsumer->consume(5000))) {
				switch(pmsg->err()) {
					case RdKafka::ERR__TIMED_OUT:
						std::cout << "Main loop timed out waiting for messages." << std::endl;
						break;
					case RdKafka::ERR_NO_ERROR:
						cb.consume_cb(*pmsg, (void*)spCurler.get()); // Hack because callback doesn't fire
						break;
					default:
						//RdKafka::err2str(inEvent.err()) 
						std::cout << "Other " << RdKafka::err2str(pmsg->err()) << std::endl;
						break;
				}
				delete pmsg; // Handled by spConsumeCb callback.
			}
		}
		pConsumer->close();
		delete pConsumer;
#endif
	}
	catch(std::invalid_argument *e) {
		std::cout << "Invald ARG eerror: " << e->what() << "\n";
		rval = -1;
	}
	catch(std::exception e) {
		std::cout << "General Error: " << e.what() << "\n";
		rval = -1;
	}
	Curler::shutdown();

	RdKafka::wait_destroyed(5000);
	std::cout << "Finished.\n";
	return rval;
}

