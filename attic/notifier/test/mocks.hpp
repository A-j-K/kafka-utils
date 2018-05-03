#pragma once

#include <memory>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#ifdef SORTED_OUT_MOCKING_RDKAFKA
#include <librdkafka/rdkafkacpp.h>
class MockRdKafkaTopic : public RdKafka::Topic
{
public:
	MOCK_CONST_METHOD0(name, const std::string());
	MOCK_CONST_METHOD1(partition_available, bool(int32_t));
	MOCK_CONST_METHOD2(offset_store, RdKafka::ErrorCode(int32_t, int64_t));
	//MOCK_CONST_METHOD0(c_ptr, struct RdKafka::rd_kafka_topic_s*());
};

class MockRdKafkaMessage : public RdKafka::Message
{
public:
	MOCK_CONST_METHOD0(errstr, std::string());	
	MOCK_CONST_METHOD0(err, RdKafka::ErrorCode());
	MOCK_CONST_METHOD0(topic, RdKafka::Topic());
	MOCK_CONST_METHOD0(topic_name, std::string());
	MOCK_CONST_METHOD0(partition, int32_t());
	MOCK_CONST_METHOD0(payload, void*());
	MOCK_CONST_METHOD0(len, size_t());
	MOCK_CONST_METHOD0(key, const std::string*());
	MOCK_CONST_METHOD0(key_pointer, const void*());
	MOCK_CONST_METHOD0(key_len, size_t());
	MOCK_CONST_METHOD0(offset, int64_t());
	MOCK_CONST_METHOD0(latency, int64_t());
	MOCK_CONST_METHOD0(timestamp, RdKafka::MessageTimestamp());
	MOCK_CONST_METHOD0(msg_opaque, void*());
};
#endif

#include "pipe.hpp"
class MockPipe : public Pipe
{
public:
	typedef std::shared_ptr<MockPipe> ShPtr;
	MOCK_METHOD2(pushBack, bool(PipeEntry::ShPtr entry, bool try_lock));
};

class MockPipeEntry : public PipeEntry
{
public:
	typedef std::shared_ptr<MockPipeEntry> ShPtr;
	MOCK_METHOD0(getMessagePtr, const RdKafka::Message*());
	MOCK_METHOD0(getType, msgType());
};

#include "absconfig.hpp"
class MockAbsConfig : public AbsConfig
{
public:
	typedef std::shared_ptr<MockAbsConfig> ShPtr;
	MOCK_METHOD0(getPartition, int());
	MOCK_METHOD0(getTopic, std::string());
	MOCK_METHOD0(getConsumerGroup, std::string());
	MOCK_METHOD0(getBrokers, const Utils::StringVector&());
	MOCK_METHOD0(getClientOptions, const Utils::KeyValue&());
	MOCK_METHOD0(getBrokersAsString, std::string());
	MOCK_METHOD0(getExpectResponseCode, int());
	MOCK_METHOD0(getApiUrl, const std::string&());
	MOCK_METHOD0(getRequestHeaders, const Utils::KeyValue&());
	MOCK_METHOD0(getHttpVerb, const std::string());
	MOCK_METHOD0(getContentType, const std::string());
};

#include "curler.hpp"
class MockCurler : public Curler
{
public:
	typedef std::shared_ptr<MockCurler> ShPtr;
	MOCK_METHOD1(xlateCode2str, std::string(CURLcode));
	MOCK_METHOD3(send, CurlerRval::ShPtr(char *p, int len, Utils::StringVector& pHeaders));
};

