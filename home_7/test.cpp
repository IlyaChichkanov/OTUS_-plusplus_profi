#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <streambuf>

#include "bulk.hpp"

TEST(BulkTest, Brackets)
{
  Bulk Bulk(3);
  
  std::streambuf* coutBuf = std::cout.rdbuf();
  std::ostringstream strCout;
  std::cout.rdbuf(strCout.rdbuf());
  
  Bulk.push("{");
  Bulk.push("command1");
  Bulk.push("command2");
  Bulk.push("{");
  Bulk.push("command3");
  Bulk.push("command4");
  Bulk.push("}");
  Bulk.push("}");
  Bulk.push("command5");
  Bulk.push("command6");
  Bulk.push("command7");
  Bulk.push("command8");
  Bulk.display();
  
  std::cout.rdbuf(coutBuf);
  
  ASSERT_STREQ("Bulk: command1, command2, command3, command4\nBulk: command5, command6, command7\nBulk: command8\n", strCout.str().c_str());
}

int main(int argc, char** argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();        
}
