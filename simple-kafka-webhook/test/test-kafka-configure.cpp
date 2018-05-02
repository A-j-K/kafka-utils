
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "utils.hpp"
#include "kafka.hpp"

#include "mockrdkafkacpp.hpp"
#include "mockabstractconfig.hpp"

using ::testing::_;
using ::testing::StrEq;
using ::testing::Return; 
using ::testing::AtLeast;
using ::testing::Matcher;
using ::testing::NiceMock;
using ::testing::ReturnRef; 

// Fixture
class test_kafka_configure : public ::testing::Test
{
public:
	Kafka *_pKafka;
	MockRdKafkaConf *_pConf;
	MockRdKafkaConf *_pTopic;
	virtual void SetUp() {
		_pKafka = new Kafka;
		_pConf  = new NiceMock<MockRdKafkaConf>;
		_pTopic = new NiceMock<MockRdKafkaConf>;
	}
	virtual void TearDown() {
		delete _pKafka;
		delete _pConf;
		delete _pTopic;
	}
};

TEST_F(test_kafka_configure, no_options_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

TEST_F(test_kafka_configure, one_option_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

TEST_F(test_kafka_configure, two_option_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";
	options["uncle"] = "david";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("uncle"), 
		Matcher<const std::string&>("david"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

TEST_F(test_kafka_configure, one_topic_option_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["topic.father"] = "ted";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>("father"), 
		Matcher<const std::string&>("ted"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

TEST_F(test_kafka_configure, one_of_each_option_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["topic.father"] = "ted";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("aunty"), 
		Matcher<const std::string&>("alice"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("uncle"), 
		Matcher<const std::string&>("david"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>("father"), // expect "topic." stripped
		Matcher<const std::string&>("ted"), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

TEST_F(test_kafka_configure, anon_test_options_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["topic.father"] = "ted";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
	.Times(2);

	EXPECT_CALL(*_pTopic, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
	.Times(1);

	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_pTopic), 
		StrEq("")))
	.Times(1);

	_pKafka->configure(&Config, _pConf, _pTopic);
}

