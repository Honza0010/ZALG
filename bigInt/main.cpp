#include <iostream>
#include <vector>
#include <string>

const size_t N = 30;

class BigInt {
private:
    enum SIGN : bool {
        POSITIVE, NEGATIVE
    };
    std::vector<int> digits;
    bool sign;
    unsigned int size;
public:
    BigInt() {
        digits = std::vector<int>(N, 0);
        sign = POSITIVE;
        size = 0;
    }

    explicit BigInt(const std::string& number) : BigInt() {
        size_t length = number.length();
        int sub = 0;
        if (number[0] == '-') {
            length--;
            sign = NEGATIVE;
            sub = 1;
        }

        size = length;

        unsigned int index = N - length;
        for (char digit : number.substr(sub)) {
            digits[index] = digit - '0';
            index++;
        }
    }

    void print() {
        if (sign == NEGATIVE) {
            std::cout << "-";
        }

        for (unsigned int i = N - size; i < N; i++) {
            std::cout << digits[i];
        }

        std::cout << std::endl;
    }

    bool is_greater(const BigInt& bigInt)
    {
        /*if (this->sign == NEGATIVE && bigInt.sign == POSITIVE)
        {
            return false;
        }
        if (this->sign == POSITIVE && bigInt.sign == NEGATIVE)
        {
            return true;
        }
        if (this->sign == NEGATIVE && bigInt.sign == NEGATIVE)
        {
            if (this->size > bigInt.size)
            {
                return false;
            }
            else if (bigInt.size > this->size)
            {
                return true;
            }
            else
            {
                for (int i = N - 1 - this->size; i < N; i++)
                {
                    if (this->digits[i] != bigInt.digits[i])
                    {
                        if (this->digits[i] > bigInt.digits[i])
                            return false;
                        else
                            return true;
                    }
                }
                return false;
            }
        }*/
        
     
        if (this->size > bigInt.size)
        {
            return true;
        }
        else if (bigInt.size > this->size)
        {
            return false;
        }
        else
        {
            for (int i = N - 1 - this->size; i < N; i++)
            {
                if (this->digits[i] != bigInt.digits[i])
                {
                    if (this->digits[i] > bigInt.digits[i])
                        return true;
                    else
                        return false;
                }
            }
            return true;
        }
        
        
    }

    void operator+=(BigInt& bigInt) 
    {
        if (bigInt.sign != sign) 
        {
            if (bigInt.sign == NEGATIVE) 
            { // a + (-b) == a - (+b)
                bigInt.sign = POSITIVE;
                operator-=(bigInt);
                bigInt.sign = NEGATIVE;
            }
            else 
            {                      // -a + b == -(a - b)
                this->sign = POSITIVE;
                operator-=(bigInt);
                this->sign = NEGATIVE;
            }
        }
        else 
        {
            unsigned int k = std::max(size, bigInt.size);
            this->size = k;
            bool danger_of_overflow = (k == N);

            // modifikovany algorithus ZALG 7.2.2
            int p = 0; // prenesena hodnota z minuleho scitani cislic
            int i = N - 1;
            for (; i > N - 1 - k; i--) 
            {
                if (danger_of_overflow && i == -1 && p == 1) 
                {
                    // Preteceni!!!
                }

                int b = digits[i] + bigInt.digits[i] + p;
                digits[i] = b % 10; // least significant digit of b
                p = b / 10;         // update carry value
            }
            if (p) 
            {
                digits[i] = p;
                size++;
            }
        }
    }

    void operator-=(BigInt& bigInt) 
    {
        if (bigInt.sign != sign)
        {
            if (bigInt.sign == NEGATIVE)
            { // a - (-b) == a + b
                bigInt.sign = POSITIVE;
                operator+=(bigInt);
                bigInt.sign = NEGATIVE;
            }
            else
            {                      // -a - b == -(a + b)
                this->sign = POSITIVE;
                operator+=(bigInt);
                this->sign = NEGATIVE;
            }
        }
   
        else 
        {
            bool this_size_bigger = (size >= bigInt.size);
            unsigned int k = std::max(size, bigInt.size);
            this->size = k;
            bool danger_of_overflow = (k == N);


            if (is_greater(bigInt))
            {
                int p = 0; // prenesena hodnota z minuleho scitani cislic
                int i = N - 1;
                for (; i > N - 1 - k; i--)
                {
                    if (danger_of_overflow && i == -1 && p == 1)
                    {
                        // Preteceni!!!
                    }
 
                    int b = digits[i] - bigInt.digits[i] - p;
                    digits[i] = b % 10 >= 0 ? b % 10 : (10 + b); // least significant digit of b
                    p = b < 0 ? 1 : 0;         // update carry value
                }

            }
            else
            {
                int p = 0; // prenesena hodnota z minuleho scitani cislic
                int i = N - 1;
                for (; i > N - 1 - k; i--)
                {
                    if (danger_of_overflow && i == -1 && p == 1)
                    {
                        // Preteceni!!!
                    }

                    int b = bigInt.digits[i] - digits[i] - p;
                    digits[i] = b % 10 >= 0 ? b % 10 : (10+b); // least significant digit of b
                    p = b < 0 ? 1 : 0;         // update carry value
                }

                this->sign = bigInt.sign == NEGATIVE ? POSITIVE : NEGATIVE;
            }

            this->size = digits[N - 1 - size] == 0 ? size - 1 : size;
           
        }
    }

    friend class BigDec;
};

const size_t K = 20;
const size_t M = 10;

class BigDec {
    BigInt number;
    int dec_digits;

public:
    explicit BigDec(const std::string& num) {
        int comma = num.find(',');
        if (comma == std::string::npos) {
            number = BigInt(num);
            dec_digits = 0;
        }
        else {
            std::string dec_part = num.substr(comma + 1);
            std::string int_part = num.substr(0, comma);
            dec_digits = dec_part.size();
            number = BigInt(int_part + dec_part);
        }
        unsigned int shift = M - dec_digits;
        for (unsigned int i = N - number.size; i < N; i++) {
            number.digits[i - shift] = number.digits[i];
            number.digits[i] = 0;
        }
        number.size += (M - dec_digits);
    }

    void print() {
        if (number.sign == number.NEGATIVE) {
            std::cout << "-";
        }


        for (unsigned int i = N - number.size; i < K; i++) {
            std::cout << number.digits[i];
        }

        if (dec_digits) {
            std::cout << ",";
        }

        for (unsigned int i = K; i < K + dec_digits; i++) {
            std::cout << number.digits[i];
        }

        std::cout << std::endl;
    }

    void operator+=(BigDec& big_dec) {
        number += big_dec.number; // neefektivni
    }

    void operator-=(BigDec& big_dec) {
        number -= big_dec.number; // neefektivni
    }
};

int main() {
    BigInt num("123456789");
    BigInt num2("65649798466");


    //BigInt num("10");
    //BigInt num2("12");

   /* BigDec num3("656497,98466");
    BigDec num4("656497,98466");
    num3.print();
    num3 += num4;
    num3.print();*/
    num -= num2;
    num.print();
    return 0;
}