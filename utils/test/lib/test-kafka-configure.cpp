
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdexcept>
#include <exception>

#include "utils.hpp"
#include "kafka.hpp"

#include "mocks/MockAbstractConfig.hpp"
#include "mocks/rdkafkacpp/MockRdKafkaConf.h"

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
		.Times(0);

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
		.Times(0);

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
		.Times(0);

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

TEST_F(test_kafka_configure, group_id_test_options_supplied)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";
	options["uncle"] = "david";
	options["group.id"] = "mytestgroupid";
	options["topic.father"] = "ted";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));

	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(2); // alice and david
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("group.id"), 
		Matcher<const std::string&>("mytestgroupid"), 
		Matcher<std::string&>(_)))
		.Times(1);
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>("offset.store.method"), 
		Matcher<const std::string&>("broker"), 
		Matcher<std::string&>(_)))
		.Times(1);
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

TEST_F(test_kafka_configure, anon_test_options_supplied_default_conf)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["aunty"] = "alice";
	options["uncle"] = "david";

	// Since we don't suppy the mock topic config in this
	// unit test a standard rdkafka object will be created
	// so to avoid rdkafka exceptions we need to supply a
	// real named conf key and value.
	options["topic.auto.offset.reset"] = "smallest";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(2);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_), 
		StrEq("")))
		.Times(1);

	_pKafka->configure(&Config, _pConf /* no _pTopic this time */);
}

TEST_F(test_kafka_configure, expect_exception_invalid_args)
{
	Utils::KeyValue options;
	NiceMock<MockAbstractConfig> Config;

	options["topic.this"] = "should cause an exception";

	ON_CALL(Config, getClientOptions())
		.WillByDefault(ReturnRef(options));
	EXPECT_CALL(*_pConf, set(
		Matcher<const std::string&>(_), 
		Matcher<const std::string&>(_), 
		Matcher<std::string&>(_)))
		.Times(0);
	EXPECT_CALL(*_pConf, set(
		StrEq("default_topic_conf"), 
		Matcher<const RdKafka::Conf*>(_), 
		StrEq("")))
		.Times(0);

	try {
		_pKafka->configure(&Config, _pConf);
		FAIL() << "expected std::invalid_argument*";
	}
	catch(std::invalid_argument *e) {
		std::string expect("Configure failure at line");
		std::string what(e->what());
		std::string actual = what.substr(0, expect.size());
		ASSERT_EQ(expect, actual);
	}
	catch(...) {
		FAIL() << "Incorrect/unknown exception thrown";
	}
}

