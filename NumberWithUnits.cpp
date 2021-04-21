#include "NumberWithUnits.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>  
#include <map>
#include <string>
using namespace ariel;
using namespace std;
std::map<std::string ,std::map<std::string,double>> NumberWithUnits::AllUnits;
namespace ariel{
    
    void NumberWithUnits::read_units(std::ifstream& f)
    {
        std::string unit1;
        std::string unit2;
        std::string s;
        double num1; 
        double num2;
        while(f>>num1>>unit1>>s>>num2>>unit2) 
        {
            NumberWithUnits::AllUnits[unit1][unit2]=num2;
            NumberWithUnits::AllUnits[unit2][unit1]=1/num2;

            std::map<std::string,double>::iterator it;
            for(it=AllUnits[unit1].begin();it!=AllUnits[unit1].end();it++)
            {
                if(it->first!=unit2){
                    AllUnits[it->first][unit2]=AllUnits[it->first][unit1]*num2;
                    AllUnits[unit2][it->first]=1/AllUnits[it->first][unit2];
                }
            }
        }
            f.close();
        }

         const NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2){
            if(n1.unit==n2.unit)
            {
                return NumberWithUnits(n1.number+n2.number,n1.unit);
            }
            else if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0.0)
            {
                return NumberWithUnits(n1.number+n2.number*NumberWithUnits::AllUnits[n2.unit][n1.unit],n1.unit);
            }
            else {
             throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
             }
        }
        const NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2){
            return n1+(-n2);
        }
        NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& other){
            if(this->unit==other.unit)
            {
                this->number+=other.number;
                return *this;
            }
            else if(NumberWithUnits::AllUnits[this->unit][other.unit]!=0)
            {
                this->number+=other.number*NumberWithUnits::AllUnits[other.unit][this->unit];
                return *this;
            }
            else throw invalid_argument("Units do not match - ["+this->unit+"] cannot be converted to ["+other.unit+"]");
           
        }
        NumberWithUnits& NumberWithUnits::operator-=(const NumberWithUnits& other){
            // if(this->unit==other.unit)
            // {
            //     this->number-=other.number;
            //     return *this;
            // }
            // else if(NumberWithUnits::AllUnits[other.unit][this->unit]!=0)
            // {
            //     cout<<AllUnits[this->unit][other.unit];
            //     this->number-=other.number*NumberWithUnits::AllUnits[other.unit][this->unit];
            //     return *this;
            // }
            // else throw invalid_argument ("Units do not match - ["+this->unit+"] cannot be converted to ["+other.unit+"]");
            return *this+=(-other);
       }
        const NumberWithUnits NumberWithUnits::operator+()const{
            return NumberWithUnits(this->number,this->unit);
        }
        const NumberWithUnits NumberWithUnits::operator-()const{
            return NumberWithUnits(-(this->number),this->unit);
        }
        bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            if(n1.unit==n2.unit)
            {
                return (n1.number<n2.number);
            }
            else if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0)
            {
                return (NumberWithUnits::AllUnits[n2.unit][n1.unit]*n2.number>n1.number);
            }
            else throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
        }
        bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n1<n2||n1==n2);
        }
        bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n2<n1);
        }
        bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return (n1==n2||n1>n2);
        }
        bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            if(n1.unit==n2.unit)
            {
                return(n1.number==n2.number);
            }
            else if(NumberWithUnits::AllUnits[n2.unit][n1.unit]!=0)
            {
                return(NumberWithUnits::AllUnits[n2.unit][n1.unit]*n2.number==n1.number);
            }
            else throw invalid_argument("Units do not match - ["+n1.unit+"] cannot be converted to ["+n2.unit+"]");
        }
        bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2)
        {
            return !(n1==n2);
        }
        NumberWithUnits& NumberWithUnits::operator++()
        {
            this->number++;
            return *this;
        }
        const NumberWithUnits NumberWithUnits::operator++(int dummy_flag_for_postfix_increment)
        {   
            NumberWithUnits copy=*this;
            this->number++;
            return copy;
        }  
        NumberWithUnits& NumberWithUnits::operator--()
        {
            this->number--;
            return *this;
        }
        const NumberWithUnits NumberWithUnits::operator--(int dummy_flag_for_postfix_increment)
        {
            NumberWithUnits copy=*this;
            this->number--;
            return copy;
        }
        const NumberWithUnits operator* (const NumberWithUnits& n,double d)
        {
            return NumberWithUnits(n.number*d,n.unit);
        }
        const NumberWithUnits operator* (double d,const NumberWithUnits& n)
        {
            return NumberWithUnits(n.number*d,n.unit);
        }
        std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n)
        {
            return os<<n.number<<"["<<n.unit<<"]";
        }
        std::istream& operator>> (std::istream& is, NumberWithUnits& n)
        {
            char s;
            return is>>n.number>>s>>n.unit;
        }
}