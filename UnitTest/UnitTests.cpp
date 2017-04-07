#include "../TopartUnitTest/Topart.h"
#include "gtest\gtest.h"

#if READ_DATA_FROM_FILE
TEST(Result, CompCounter1)
{
	string path = "g:\\Kerti\\Projects\\ItechChallenge\\TopartUnitTest\\UnitTest\\test1.txt";

	Graph g;
	g.StartProgram(path);
	ASSERT_EQ(2, g.compCounter);
}

TEST(Result, CompCounter2)
{
	string path = "g:\\Kerti\\Projects\\ItechChallenge\\TopartUnitTest\\UnitTest\\test2.txt";
	Graph g;
	g.StartProgram(path);

	ASSERT_EQ(0, g.compCounter);
}

TEST(creatingHighVertex, highVertex)
{
	Graph g;
	g.V = 10000;
	g.Init();
	ASSERT_TRUE(true);
}
#endif
int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
