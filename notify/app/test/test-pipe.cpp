
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "utils/pipe.hpp"

class mock_pipe : public Pipe 
{
public:
	void lock_it(void) { _mutex.lock(); }
	void unlock_it(void) { _mutex.unlock(); }
};

class test_pipe : public ::testing::Test
{
public:
	Pipe::ShPtr _spPipe;
	virtual void SetUp() {
		PipeEntry::ShPtr spEntry;
		_spPipe = Pipe::ShPtr(new mock_pipe);
		_spPipe->setMaxCount(1, Pipe::BLOCKING, NULL);
		spEntry = PipeEntry::ShPtr(new PipeEntry);
		_spPipe->pushBack(spEntry);
	}
	virtual void TearDown() {}
};

TEST_F(test_pipe, empty_nonblocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(false, _spPipe->isEmpty(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	itWorked = false;
	ASSERT_EQ(true, _spPipe->isEmpty(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, count_nonblocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(1, _spPipe->getSize(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	itWorked = false;
	ASSERT_EQ(0, _spPipe->getSize(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, empty_nonblocking_but_blocked)
{
	bool itWorked;
	reinterpret_cast<mock_pipe*>(_spPipe.get())->lock_it();
	itWorked = true;
	ASSERT_EQ(false, _spPipe->isEmpty(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(false, itWorked);
	itWorked = true;
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	ASSERT_EQ(false, itWorked);
	reinterpret_cast<mock_pipe*>(_spPipe.get())->unlock_it();
}

TEST_F(test_pipe, count_nonblocking_but_blocked)
{
	bool itWorked;
	reinterpret_cast<mock_pipe*>(_spPipe.get())->lock_it();
	itWorked = true;
	ASSERT_EQ(-1, _spPipe->getSize(Pipe::NONBLOCKING, &itWorked));
	ASSERT_EQ(false, itWorked);
	itWorked = true;
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::NONBLOCKING, &itWorked);
	ASSERT_EQ(false, itWorked);
	reinterpret_cast<mock_pipe*>(_spPipe.get())->unlock_it();
}

TEST_F(test_pipe, empty_blocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(false, _spPipe->isEmpty(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	itWorked = false;
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::BLOCKING, &itWorked);
	ASSERT_EQ(true, _spPipe->isEmpty(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

TEST_F(test_pipe, count_blocking)
{
	bool itWorked;
	itWorked = false;
	ASSERT_EQ(1, _spPipe->getSize(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
	PipeEntry::ShPtr spEntry = _spPipe->popFront(Pipe::BLOCKING, &itWorked);
	itWorked = false;
	ASSERT_EQ(0, _spPipe->getSize(Pipe::BLOCKING, &itWorked));
	ASSERT_EQ(true, itWorked);
}

