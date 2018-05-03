
#include <string>
#include "mocks.hpp"
#include "callback.hpp"

/*
	Not in CMakeLists.txt until figure out how to GMock the RdKafkaCpp interfaces.
*/

class test_callback : public ::testing::Test
{
public:
	Callback::ShPtr _spCallback;
	Pipe::ShPtr _spPipe;
	Curler::ShPtr _spCurler;
	AbsConfig::ShPtr _spAbsConfig;
	virtual void SetUp() {
		_spPipe = Pipe::ShPtr(new MockPipe);
		_spCurler = Curler::ShPtr(new MockCurler);
		_spAbsConfig = AbsConfig::ShPtr(new MockAbsConfig);
		_spCallback = Callback::ShPtr(new Callback(_spAbsConfig, _spCurler, _spPipe));
	}
	virtual void TearDown() {}
};

TEST_F(test_callback, test1)
{
	bool rval = false;
	Callback *c = _spCallback.get();
	MockRdKafkaMessage *pMockMsg = new MockRdKafkaMessage;	
	rval = Callback::static_run_once(c, false);
	ASSERT_EQ(true, rval);
	delete pMockMsg;
}

