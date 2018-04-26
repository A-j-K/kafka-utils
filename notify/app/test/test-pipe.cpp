
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/pipe.hpp"

class test_pipe : public ::testing::Test
{
public:
	Pipe::ShPtr _spPipe;
	virtual void SetUp() {
		PipeEntry::ShPtr spEntry;
		_spPipe = Pipe::ShPtr(new Pipe);
		spEntry = PipeEntry::ShPtr(new PipeEntry);
		_spPipe->pushBack(spEntry);
	}
	virtual void TearDown() {}
};

TEST_F(test_pipe, simple_empty_blocking)
{
	bool itWorked = false;
	ASSERT_EQ(false, _spPipe->isEmpty(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::BLOCKING, &itWorked);
	ASSERT_EQ(true, _spPipe->isEmpty(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, simple_count_blocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(1, _spPipe->getSize(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	itWorked = false;
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::BLOCKING, &itWorked);
	ASSERT_EQ(0, _spPipe->getSize(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, simple_empty_nonblocking)
{
	bool itWorked = false;
	ASSERT_EQ(false, _spPipe->isEmpty(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	ASSERT_EQ(true, _spPipe->isEmpty(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, simple_count_nonblocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(1, _spPipe->getSize(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	itWorked = false;
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	ASSERT_EQ(0, _spPipe->getSize(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

