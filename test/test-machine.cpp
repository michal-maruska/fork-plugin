#include "gmock/gmock.h"
#include <config.h>
#include <gtest/gtest.h>

#include "fork_enums.h"
#include <cstdlib>
#include <memory>
#include <ostream>

#include "../src/machine.h"
#include "../src/platform.h"
#include "empty_last.h"

#include <gmock/gmock.h>

typedef int Time;
typedef int KeyCode;


// I need archived_event
struct test_archived_event
{
  Time time; // never used
  KeyCode key;
  KeyCode forked;
  bool press;                  /* client type? */
};

using testing::Mock;
using testing::Return;
using testing::AnyNumber;

// I need Environment which can convert into test_archived_event
// This is fully under control of our environment:
class TestEvent : test_archived_event {
public:

  TestEvent(const Time time, const KeyCode keycode, bool press = true, const KeyCode forked = 0) :
    test_archived_event{time, keycode, forked, press} {}

  ~TestEvent() {}
};

// I want to mock this:
class testEnvironment final : public forkNS::platformEnvironment<KeyCode, Time,
                                                                 test_archived_event,
                                                                 TestEvent>{
public:
  MOCK_METHOD(bool, press_p, (const TestEvent& event), (const));
  MOCK_METHOD(bool, release_p,(const TestEvent& event), (const));
  MOCK_METHOD(Time, time_of,(const TestEvent& event), (const));
  MOCK_METHOD(KeyCode, detail_of,(const TestEvent& event), (const));

  MOCK_METHOD(bool, ignore_event,(const TestEvent &pevent));

  MOCK_METHOD(bool, output_frozen,());
  MOCK_METHOD(void, relay_event,(const TestEvent &pevent), (const));
  MOCK_METHOD(void, push_time,(Time now));

  void vlog(const char* format, va_list argptr) const override {
    vprintf(format, argptr);
  }

  void log(const char* format...) const override
  {
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
  };
  MOCK_METHOD(void, fmt_event,(const char* message, const TestEvent &event), (const));

  MOCK_METHOD(void, archive_event,(test_archived_event& ae, const TestEvent& event));
  MOCK_METHOD(void, free_event,(TestEvent* pevent), (const));
  MOCK_METHOD(void, rewrite_event,(TestEvent& pevent, KeyCode code));

  MOCK_METHOD(std::unique_ptr<forkNS::event_dumper<test_archived_event>>, get_event_dumper,());
};


using last_events_t = empty_last_events_t<test_archived_event>;
using machineRec = forkNS::forkingMachine<KeyCode, Time,
                                          TestEvent, testEnvironment,
                                          test_archived_event, last_events_t>;
using fork_configuration = machineRec::fork_configuration;

// template instantiation
namespace forkNS {
  template class forkingMachine<KeyCode, Time, TestEvent, testEnvironment, test_archived_event, last_events_t>;
}


class machineTest : public testing::Test {

protected:
    machineTest() : environment(new testEnvironment() ),
                    config (new fork_configuration),
                    fm (new machineRec(environment)) {

      config->debug = 0;
      fm->config.reset(config);
    }

  ~machineTest()
  {
    delete fm;
    delete environment;
  }

  testEnvironment *environment;
  machineRec *fm;
  fork_configuration *config;
};

class TestDumper : public forkNS::event_dumper<test_archived_event> {
public:
    int count = 0;
    void operator()(const test_archived_event& ev) override {
        UNUSED(ev);
        count++;
    }
};

TEST_F(machineTest, AcceptEvent) {
  TestEvent pevent(100L, 56);

  EXPECT_CALL(*environment, relay_event);
  EXPECT_CALL(*environment, detail_of(testing::_))
    .Times(4)
    .WillRepeatedly(testing::Return(56));
  EXPECT_CALL(*environment, time_of).Times(3);
  EXPECT_CALL(*environment, press_p).Times(2);
  EXPECT_CALL(*environment, release_p).Times(2);

  EXPECT_CALL(*environment, output_frozen).Times(AnyNumber()).WillRepeatedly(Return(false));

  Time next = fm->accept_event(pevent);
  UNUSED(next);
  Mock::VerifyAndClearExpectations(environment);
}

TEST_F(machineTest, Configure) {
  KeyCode A = 10;
  KeyCode B = 11;
  fm->configure_key(fork_configure_key_fork, A, B, 1);
  EXPECT_EQ(config->fork_keycode[A], B);

  Mock::VerifyAndClearExpectations(environment);
}

TEST_F(machineTest, DumpLastEvents) {
  TestDumper dumper;
  fm->dump_last_events(&dumper);
  EXPECT_EQ(dumper.count, 0);
}

TEST_F(machineTest, LockingAndDecisionTime) {
  EXPECT_CALL(*environment, output_frozen).Times(AnyNumber()).WillRepeatedly(Return(false));

  // Check initial decision time when normal
  EXPECT_EQ(fm->next_decision_time(), 0);

  // Accept time update under lock
  Time next = fm->accept_time(100);
  EXPECT_EQ(next, 0);

  // Accept confirmation under lock
  fm->accept_confirmation();

  Mock::VerifyAndClearExpectations(environment);
}
