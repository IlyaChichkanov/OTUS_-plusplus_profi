#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Bulk
{
public:

  Bulk(int n) : block_size_(n) { data_.resize(n); }

  void push(std::string_view cmd)
  {
    if(cmd == "{")
    {
      if(!is_block_started_)
      {
        is_block_started_ = true;
        display();
      }
      return;
    }
    
    if(cmd == "}")
    {
      if(is_block_started_)
      {
        is_block_started_ = false;
        display();
      }
      return;
    }

    if(cnt_ >= block_size_) data_.push_back(cmd.data());
    else data_[cnt_] = cmd.data();
    cnt_++;
    
    if(!is_block_started_)
    {
      if(cnt_ == block_size_)
        display();
    }
  }

  void display()
  {
    if(cnt_ == 0) return;
    std::cout << "Bulk: ";
    for(int i = 0; i < cnt_; ++i)
    {
      std::cout << data_[i];
      if(i != cnt_-1) std::cout << ", ";                      
    }
    std::cout << "\n";
    cnt_ = 0;
  }

private:
  int                      block_size_{1};
  int                      cnt_{0};
  bool                     is_block_started_{false};
  std::vector<std::string> data_;
};
