#include "unity.h"
#include "ArduinoFake.h"
#include "EventBuffer.h"

void test_empty_buffer()
{
  EventBuffer eb(10);
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_one_event()
{
  EventBuffer eb(10);
  eb.emit(42);
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(42, eb.get());
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_two_events()
{
  EventBuffer eb(10);
  eb.emit(42);
  eb.emit(99);
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(42, eb.get());
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(99, eb.get());
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_reset()
{
  EventBuffer eb(10);
  eb.emit(42);
  eb.emit(99);
  eb.reset();
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_wraparound()
{
  EventBuffer eb(2);
  eb.emit(42);
  eb.emit(99);
  TEST_ASSERT_EQUAL(42, eb.get());
  eb.emit(11);
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(99, eb.get());
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(11, eb.get());
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_get_when_empty()
{
  EventBuffer eb(10);
  TEST_ASSERT_EQUAL(__INT32_MAX__, eb.get());
  TEST_ASSERT_FALSE(eb.has_event());
}

void test_emit_when_full()
{
  EventBuffer eb(2);
  eb.emit(42);
  eb.emit(99);
  eb.emit(11);
  TEST_ASSERT_EQUAL(42, eb.get());
  TEST_ASSERT_TRUE(eb.has_event());
  TEST_ASSERT_EQUAL(99, eb.get());
  TEST_ASSERT_FALSE(eb.has_event());
  TEST_ASSERT_EQUAL(__INT32_MAX__, eb.get());
}

int runUnityTests(void) 
{
  UNITY_BEGIN();
  RUN_TEST(test_empty_buffer);
  RUN_TEST(test_one_event);
  RUN_TEST(test_two_events);
  RUN_TEST(test_reset);
  RUN_TEST(test_wraparound);
  RUN_TEST(test_get_when_empty);
  RUN_TEST(test_emit_when_full);
  return UNITY_END();
}

int main(void) 
{
  return runUnityTests();
}