#include <gtest/gtest.h>

#include "common/message.h"


namespace N_Test
{
}



//   https://theboostcpplibraries.com/boost.serialization-archive


	/*
Example 64.4. Serializing user-defined types with a member function
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>

using namespace boost::archive;

std::stringstream ss;

class animal
{
public:
  animal() = default;
  animal(int legs) : legs_{legs} {}
  int legs() const { return legs_; }

private:
  friend class boost::serialization::access;

  template <typename Archive>
  void serialize(Archive &ar, const unsigned int version) { ar & legs_; }

  int legs_;
};

void save()
{
  text_oarchive oa{ss};
  animal a{4};
  oa << a;
}

void load()
{
  text_iarchive ia{ss};
  animal a;
  ia >> a;
  std::cout << a.legs() << '\n';
}

int main()
{
  save();
  load();
}
	
	*/



	/*
Example 64.5. Serializing with a free-standing function
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <sstream>

using namespace boost::archive;

std::stringstream ss;

struct animal
{
  int legs_;

  animal() = default;
  animal(int legs) : legs_{legs} {}
  int legs() const { return legs_; }
};

template <typename Archive>
void serialize(Archive &ar, animal &a, const unsigned int version)
{
  ar & a.legs_;
}

void save()
{
  text_oarchive oa{ss};
  animal a{4};
  oa << a;
}

void load()
{
  text_iarchive ia{ss};
  animal a;
  ia >> a;
  std::cout << a.legs() << '\n';
}

int main()
{
  save();
  load();
}
	*/

