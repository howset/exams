#include <iostream>
#include <sstream>
#include <string>
#include "set.hpp"
#include "searchable_array_bag.hpp"
#include "searchable_tree_bag.hpp"

static bool expect_true(const char* what, bool cond){ if(!cond){ std::cerr<<what<<" expected true\n"; return false;} return true; }
static bool expect_false(const char* what, bool cond){ if(cond){ std::cerr<<what<<" expected false\n"; return false;} return true; }

static std::string capture_print(set &s){ std::ostringstream oss; auto* old=std::cout.rdbuf(oss.rdbuf()); s.print(); std::cout.rdbuf(old); return oss.str(); }

static bool test_array_set_basic(){ searchable_array_bag bag; set s(bag); s.insert(5); s.insert(10); s.insert(5); return expect_true("has5", s.has(5)) && expect_true("has10", s.has(10)); }
static bool test_tree_set_basic(){ searchable_tree_bag bag; set s(bag); s.insert(3); s.insert(7); s.insert(3); return expect_true("has3", s.has(3)) && expect_true("has7", s.has(7)); }
static bool test_clear(){ searchable_array_bag bag; set s(bag); s.insert(1); s.insert(2); s.clear(); return expect_false("has1 after clear", s.has(1)) && expect_false("has2 after clear", s.has(2)); }
static bool test_bulk_insert(){ searchable_array_bag bag; set s(bag); int arr[]={1,2,3,4}; s.insert(arr,4); for(int i=1;i<=4;i++){ if(!s.has(i)) return false; } return true; }
static bool test_print_unique(){ searchable_tree_bag bag; set s(bag); s.insert(9); s.insert(9); std::string out=capture_print(s); int count=0; for(size_t pos=0;(pos=out.find("9",pos))!=std::string::npos;++pos) ++count; return count>=1; }

int main(int argc,char** argv){ if(argc<2){ std::cerr<<"usage: "<<argv[0]<<" <test>\n"; return 2; } std::string t=argv[1]; bool ok=false; if(t=="array_basic") ok=test_array_set_basic(); else if(t=="tree_basic") ok=test_tree_set_basic(); else if(t=="clear") ok=test_clear(); else if(t=="bulk") ok=test_bulk_insert(); else if(t=="print_unique") ok=test_print_unique(); else { std::cerr<<"unknown test\n"; return 2; } return ok?0:1; }
