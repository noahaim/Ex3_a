#include <string>
#include <map>
namespace ariel{
class NumberWithUnits{
    double number;
    std::string  unit;
    static std::map<std::string ,std::map<std::string,double>> AllUnits;

    public:
        NumberWithUnits(double num, std::string s){
            if(AllUnits.find(s)!=AllUnits.end()){
            number=num;
            unit=s;
        }
        else throw std::invalid_argument("no legal unit");
        }
        static void read_units(std::ifstream& f);

        friend const NumberWithUnits operator+(const NumberWithUnits& n1,const NumberWithUnits& n2);
        NumberWithUnits& operator+=(const NumberWithUnits& other);
        const NumberWithUnits operator+() const;

        friend const NumberWithUnits operator-(const NumberWithUnits& n1,const NumberWithUnits& n2);
        NumberWithUnits& operator-=(const NumberWithUnits& other);
        const NumberWithUnits operator-() const;

    friend bool operator<(const NumberWithUnits& n1, const NumberWithUnits& n2);
    friend bool operator<=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    friend bool operator>(const NumberWithUnits& n1, const NumberWithUnits& n2);
    friend bool operator>=(const NumberWithUnits& n1, const NumberWithUnits& n2);
    friend bool operator==(const NumberWithUnits& n1, const NumberWithUnits& n2);
    friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);

    NumberWithUnits& operator++();
    const NumberWithUnits operator++(int dummy_flag_for_postfix_increment);
    NumberWithUnits& operator--();
    const NumberWithUnits operator--(int dummy_flag_for_postfix_increment);

    friend const NumberWithUnits operator*(const NumberWithUnits& n,double d);
    friend const NumberWithUnits operator*(double d,const NumberWithUnits& n);

    friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n);
    friend std::istream& operator>> (std::istream& is, NumberWithUnits& n);

};
}