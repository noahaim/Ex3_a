#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;

TEST_CASE("check operator +")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(2, "km");  
  NumberWithUnits n2(2, "km");
  NumberWithUnits d=n1+n2;
  CHECK(NumberWithUnits(4,"km")==d);
  NumberWithUnits n3(1000, "m");
  d=n1+n3;
  CHECK(NumberWithUnits(3,"km")==d);
  d=n3+n1;
  CHECK(NumberWithUnits(3000,"m")==d);
  NumberWithUnits n4(3, "min");
  CHECK_THROWS(n1+n4);
}
TEST_CASE("check operator -")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "km");  
  NumberWithUnits n2(2, "km");
  NumberWithUnits d=n1-n2;
  CHECK(NumberWithUnits(3,"km")==d);
  NumberWithUnits n3(1000, "m");
  d=n1-n3;
  CHECK(NumberWithUnits(4,"km")==d);
  d=n3-n1;
  CHECK(NumberWithUnits(-4000,"m")==d);
  NumberWithUnits n4(3, "min");
  CHECK_THROWS(n1-n4);
}
TEST_CASE("check operator +=")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "km");  
  NumberWithUnits n2(2, "km");
  n1+=n2;
  CHECK(NumberWithUnits(7,"km")==n1);
  NumberWithUnits n3(1000, "m");
  n2+=n3;
  CHECK(NumberWithUnits(3,"km")==n2);
  n3+=n2;
  CHECK(NumberWithUnits(4000,"m")==n3);
  NumberWithUnits n4(3, "hour");
  CHECK_THROWS(n3+=n4);
}
TEST_CASE("check operator -=")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "km");  
  NumberWithUnits n2(2, "km");
  n1-=n2;
  CHECK(NumberWithUnits(3,"km")==n1);
   NumberWithUnits n3(1000, "m");
  n2-=n3;
  CHECK(NumberWithUnits(1,"km")==n2);
  n3-=n2;
  CHECK(NumberWithUnits(0,"m")==n3);
   NumberWithUnits n4(3, "min");
  CHECK_THROWS(n3-=n4);
}
TEST_CASE("check operator - oneri")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "min");  
  n1=-n1;
  CHECK(NumberWithUnits(-5,"min")==n1);
}
TEST_CASE("check operator + oneri")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "min");  
  n1=+n1;
  CHECK(NumberWithUnits(5,"min")==n1);
}
TEST_CASE("check operator <")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(4,"kg")<n1);
  CHECK(NumberWithUnits(2000,"g")<n1);
  CHECK_FALSE(NumberWithUnits(5000,"g")<n1);
  CHECK_FALSE(NumberWithUnits(6,"kg")<n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5,"USD")<n1));
}
TEST_CASE("check operator >")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(7,"kg")>n1);
  CHECK(NumberWithUnits(7000,"g")>n1);
  CHECK_FALSE(NumberWithUnits(2000,"g")>n1);
  CHECK_FALSE(NumberWithUnits(2,"kg")>n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5,"USD")>n1));
}
TEST_CASE("check operator <=")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(4,"kg")<=n1);
  CHECK(NumberWithUnits(5000,"g")<=n1);
  CHECK(NumberWithUnits(2000,"g")<=n1);
  CHECK_FALSE(NumberWithUnits(5001,"g")<=n1);
  CHECK_FALSE(NumberWithUnits(9,"kg")<=n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5, "min")<n1));
}
TEST_CASE("check operator >=")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(5,"kg")>=n1);
  CHECK(NumberWithUnits(5000,"g")>=n1);
  CHECK(NumberWithUnits(7,"kg")>=n1);
  CHECK(NumberWithUnits(7000,"g")>=n1);
  CHECK_FALSE(NumberWithUnits(2000,"g")>=n1);
  CHECK_FALSE(NumberWithUnits(2,"kg")>=n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5,"USD")>n1));
}
TEST_CASE("check operator ==")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(5000,"g")==n1);
  CHECK(NumberWithUnits(5,"kg")==n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5,"USD")==n1));
}
TEST_CASE("check operator !=")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "kg");
  CHECK(NumberWithUnits(2000,"g")!=n1);
  CHECK(NumberWithUnits(21,"kg")!=n1);
  CHECK_THROWS(bool temp=(NumberWithUnits(5,"USD")!=n1));
}
TEST_CASE("check operator ++ after")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "USD");
  CHECK(NumberWithUnits(5,"USD")==n1++);
}
TEST_CASE("check operator ++ before")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "USD");
  CHECK(NumberWithUnits(6,"USD")==++n1);
}
TEST_CASE("check operator -- after")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "USD");
  CHECK(NumberWithUnits(5,"USD")==n1--);
  CHECK(NumberWithUnits(4,"USD")==n1);
}
TEST_CASE("check operator -- before")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "USD");
  CHECK(NumberWithUnits(4,"USD")==--n1);
}
TEST_CASE("check operator * double")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits n1(5, "hour");
  CHECK(NumberWithUnits(10,"hour")==n1*2);
  CHECK(NumberWithUnits(10,"hour")!=2.5*n1);
}
TEST_CASE("not legal units")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  CHECK_THROWS(NumberWithUnits n1(5, "day"));
  CHECK_THROWS(NumberWithUnits n1(11, "euro"));
}
TEST_CASE("check operator << and >>")
{
  ifstream units_file{"units.txt"};
  NumberWithUnits::read_units(units_file);
  NumberWithUnits f1(0,"hour");
  istringstream iss("5[hour]");
  ostringstream oss;
  iss>>f1;
  oss<<f1;
  CHECK(oss.str() == "5[hour]");
}