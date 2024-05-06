/**
 * Unit Tests for the class
 **/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

/* Example test
   TEST(GuesserTest, smoke_test)
   {
   ASSERT_EQ( 1+1, 2 );
   }
   */


TEST(GuesserTest, Match_SimpleCorrectGuess) {
	Guesser my_guesser("epic");
	bool actual = my_guesser.match("epic");
	ASSERT_EQ(1, actual);
}

TEST(GuesserTest, Match_SimpleIncorrectGuess) {
	Guesser my_guesser("epic");
	bool actual = my_guesser.match("not_epic");
	ASSERT_EQ(0, actual);
}

TEST(GuesserTest, Match_ExactMatch) {
	Guesser guesser("hello");
	ASSERT_TRUE(guesser.match("hello"));
}

TEST(GuesserTest, Match_OneWrong) {
	Guesser guesser("hello");
	ASSERT_FALSE(guesser.match("helloadaed"));
}

TEST(GuesserTest, Match_AllGuessesUsed) {
	Guesser guesser("hello");
	guesser.match("aggag");
	guesser.match("qertqe");
	guesser.match("gqethqhq");
	ASSERT_FALSE(guesser.match("hello"));
}

TEST(GuesserTest, Remaining_AllGuessesUsedRemaining) {
	Guesser guesser("hello");
	guesser.match("aggag");
	guesser.match("qertqe");
	guesser.match("gqethqhq");
	ASSERT_EQ(guesser.remaining(), 0);
}

TEST(GuesserTest, Match_BruteForceDetect) {
	Guesser guesser("hello");
	ASSERT_FALSE(guesser.match("aeifuoskdfjl"));
}

TEST(GuesserTest, Remaining_GuessesDecrement) {
	Guesser guesser("hello");
	guesser.match("aggkowri");
	ASSERT_EQ(2, guesser.remaining());
}

TEST(GuesserTest, Remaining_BruteForceMultiple) {
	Guesser guesser("multiple_brute");
	guesser.match("hellosdaasd");
	guesser.match("rwtipdfklaf");
	ASSERT_EQ(1, guesser.remaining());
}

TEST(GuesserTest, Remaining_Mismatch) {
	Guesser guesser("combo");
	guesser.match("comb");
	ASSERT_EQ(2, guesser.remaining());
}

TEST(GuesserTest, Constructor_InitialRemain) {
	Guesser guesser("initial");
	ASSERT_EQ(3, guesser.remaining());
}

TEST(GuesserTest, Remaining_ResetOnMatch) {
	Guesser guesser("hello");
	guesser.match("holla");
	guesser.match("hello");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, Remaining_MatchFailDecrement) {
	Guesser guesser("test");
	guesser.match("sest");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(2, actual);
}

TEST(GuesserTest, Remaining_MatchRemainReset) {
	Guesser guesser("test");
	guesser.match("sest");
	guesser.match("test");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, Match_BruteForceRemainDecrement) {
	Guesser guesser("hello_hello");
	guesser.match("not_right");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(2, actual);
}

TEST(GuesserTest, Match_CorrectGuessRemainReset) {
	Guesser guesser("correct");
	guesser.match("correct");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, Match_EmptySecretMatch) {
	Guesser guesser("");
	bool actual = guesser.match("");
	ASSERT_TRUE(actual);
}

TEST(GuesserTest, Remaining_DecrementForIncorrectGuess) {
	Guesser guesser("abcdefg");
	guesser.match("different");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(2, actual);
}

TEST(GuesserTest, Match_TruncateSecret) {
	Guesser g("1234567890123456789012345678901234567890");
	ASSERT_TRUE(g.match("12345678901234567890123456789012")); //32
}

TEST(GuesserTest, Match_TruncatedSecretMatches) {
	Guesser guesser("1234567890123456789012345678901234567890");
	bool actual = guesser.match("12345678901234567890123456789012");  //32
	ASSERT_TRUE(actual);
}

TEST(GuesserTest, Match_SpecialCharacters) {
	Guesser guesser("!@#$%^&*");
	bool actual = guesser.match("!@#$%^&*");
	ASSERT_TRUE(actual);
}

TEST(GuesserTest, Match_LongSimilar) {
	Guesser guesser("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");  //32
	bool actual = guesser.match("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"); 
	ASSERT_FALSE(actual);
}

TEST(GuesserTest, Remaining_RightWrongRight) {
	Guesser guesser("right");
	guesser.match("right");
	guesser.match("wrong");
	guesser.match("right");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(3, actual);
}

TEST(GuesserTest, Remaining_WrongRightWrong) {
	Guesser guesser("right");
	guesser.match("wrong");
	guesser.match("right");
	guesser.match("wrong");
	unsigned int actual = guesser.remaining();
	ASSERT_EQ(2, actual);
}
