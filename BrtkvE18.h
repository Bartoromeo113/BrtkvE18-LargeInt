#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <algorithm>

typedef unsigned long long e18;

class BrtkvE18 {
public:
    e18* liczba;
    int rozmiar;
    int znak;

public://==========================================
    // Konstruktor
    BrtkvE18(const std::string& l) {
        // Remove leading zeros
        std::string trimmed = l;
        size_t firstNonZero = trimmed.find_first_not_of('0');
        
        // If the string is all zeros, keep one zero
        if (firstNonZero == std::string::npos) {
            trimmed = "0";
        } else {
            trimmed = trimmed.substr(firstNonZero);
        }
        
        // Calculate the size based on the trimmed string
        rozmiar = trimmed.length() / 18 + (trimmed.length() % 18 == 0 ? 0 : 1);
        liczba = new e18[rozmiar]();
        
        // Przechodzimy po stringu od końca do początku
        int segmentIndex = 0;
        for (int i = trimmed.length(); i > 0; i -= 18) {
            int start = std::max(0, i - 18);
            std::string segment = trimmed.substr(start, i - start);
            
            liczba[segmentIndex] = std::stoull(segment);
            segmentIndex++;
        }
    }

      BrtkvE18(int roz) {
          rozmiar = roz;
          liczba = new e18[rozmiar]();

      }

      BrtkvE18() {
        rozmiar = 0;
        liczba = nullptr;
    }
    


    BrtkvE18(const BrtkvE18& inny) {
        rozmiar = inny.rozmiar;
        liczba = new e18[rozmiar]();

        // Przechodzimy po stringu od końca do początku
        
        for (int i = 0; i < rozmiar; i++) {
            liczba[i] = inny.liczba[i];
        }
    }
    void wstawWartosc(const std::string& l) {
        // Remove leading zeros
        std::string trimmed = l;
        size_t firstNonZero = trimmed.find_first_not_of('0');
        
        // If the string is all zeros, keep one zero
        if (firstNonZero == std::string::npos) {
            trimmed = "0";
        } else {
            trimmed = trimmed.substr(firstNonZero);
        }

        // Calculate the size based on the trimmed string
        rozmiar = trimmed.length() / 18 + (trimmed.length() % 18 == 0 ? 0 : 1);
        liczba = new e18[rozmiar]();
        
        // Przechodzimy po stringu od końca do początku
        int segmentIndex = 0;
        for (int i = trimmed.length(); i > 0; i -= 18) {
            int start = std::max(0, i - 18);
            std::string segment = trimmed.substr(start, i - start);
            
            liczba[segmentIndex] = std::stoull(segment);
            segmentIndex++;
        }
    }

    e18 zwrocULL(){
        if(rozmiar!=1){
            std::cout<<"nie mozna przekonwertowac";
            return 0;
        }else{
            return liczba[0];
        }
    }

    ~BrtkvE18() {
        delete[] liczba;
    }

    friend std::ostream& operator<<(std::ostream& os, const BrtkvE18& obj) {
        if(obj.rozmiar == 0){
            os << "0";
            return os;
        }
        for (int i = obj.rozmiar - 1; i >= 0; i--) {
            if (i < obj.rozmiar - 1) {
                os << std::setfill('0') << std::setw(18);
            }
            os << obj.liczba[i] ;
            os << "|";
        }
        return os;
    }

    BrtkvE18& operator=(const BrtkvE18& other) {
        if (this == &other) return *this;
        delete[] liczba;
        rozmiar = other.rozmiar;
        liczba = new e18[rozmiar];
        for (int i = 0; i < rozmiar; i++) liczba[i] = other.liczba[i];
        return *this;
    }
    BrtkvE18& operator=(e18 other) {      
        delete[] liczba;
        rozmiar = 1;
        liczba = new e18[1];
        liczba[0] = other; 
        return *this;
    }
    BrtkvE18& operator+=(const BrtkvE18& other) {
        int roz_max = std::max(rozmiar, other.rozmiar); 
        int roz_min = std::min(rozmiar, other.rozmiar);
           
      
        for (int i = 0; i < roz_max-1; i++) {
            if(roz_max == roz_min){
                liczba[i] += other.liczba[i];
                liczba[i+1] += liczba[i] / 1000000000000000000;
                liczba[i] = liczba[i] % 1000000000000000000;
            }else{
                if(i<roz_min){
                    liczba[i] += other.liczba[i];
                }else{
                    if(roz_min == other.rozmiar){
                       
                    }else{
                        liczba[i] += other.liczba[i];
                    }
                }
                liczba[i+1] += liczba[i] / 1000000000000000000;
                liczba[i] %= 1000000000000000000;
            }

        }
        if(roz_min == other.rozmiar){
              //  Result.liczba[roz_max-1] += liczba[roz_max-1];
        }
        if(roz_min == rozmiar){
                liczba[roz_max-1] += other.liczba[roz_max-1];

        }
        

        if (liczba[roz_max-1] > 999999999999999999) {
            rozmiar++;
            roz_max++;
            e18* newLiczba = new e18[roz_max];

            for (int i = 0; i < roz_max-1; i++) {
                newLiczba[i] = liczba[i];
            }
            newLiczba[roz_max-2] %= 1000000000000000000;
            newLiczba[roz_max-1] = 1;

            delete[] liczba;
            liczba = newLiczba;

        } 
        return *this;
    }
    
    BrtkvE18 operator+(const BrtkvE18& other) const {
        int roz_max = std::max(rozmiar, other.rozmiar); 
        int roz_min = std::min(rozmiar, other.rozmiar);
        BrtkvE18 Result(roz_max);
        if(roz_min == 0){
            if(roz_min == other.rozmiar){
                for (int i = 0; i < roz_max; i++) {
                    Result.liczba[i] = liczba[i];
                }
            }else{
                for (int i = 0; i < roz_max; i++) {
                    Result.liczba[i] = other.liczba[i];
                }
            }
            return Result;
        }
           
      
        for (int i = 0; i < roz_max-1; i++) {
            if(roz_max == roz_min){
                Result.liczba[i] += liczba[i] + other.liczba[i];
                Result.liczba[i+1] += Result.liczba[i] / 1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }else{
                if(i<roz_min){
                    Result.liczba[i] += liczba[i] + other.liczba[i];
                }else{
                    if(roz_min == other.rozmiar){
                        Result.liczba[i] += liczba[i];
                    }else{
                        Result.liczba[i] += other.liczba[i];
                    }
                }
                Result.liczba[i+1] += Result.liczba[i] / 1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }

        }
        if(roz_min == other.rozmiar){
                Result.liczba[roz_max-1] += liczba[roz_max-1];
        }
        if(roz_min == rozmiar){
                Result.liczba[roz_max-1] += other.liczba[roz_max-1];

        }
        

        if (Result.liczba[roz_max-1] > 999999999999999999) {
            Result.rozmiar++;
            roz_max++;
            e18* newLiczba = new e18[roz_max];

            for (int i = 0; i < roz_max-1; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            newLiczba[roz_max-2] %= 1000000000000000000;
            newLiczba[roz_max-1] = 1;

            delete[] Result.liczba;
            Result.liczba = newLiczba;

        } 
        return Result;
    }
    
    BrtkvE18 operator+(e18 other) const {
        BrtkvE18 Result(*this);
        Result.liczba[0]+=other;
        for(int i = 0; i < rozmiar-1; i++){
            if(Result.liczba[i]<999999999999999999){
                return Result;
            }else{
                Result.liczba[i+1]+=1;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }
        }

        if(Result.liczba[rozmiar-1]>999999999999999999){
            e18* newLiczba = new e18[rozmiar+1];
            for (int i = 0; i < rozmiar; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar++;
            delete[] Result.liczba;
            Result.liczba = new e18[rozmiar+1];       
            for (int i = 0; i < rozmiar; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            Result.liczba[rozmiar] = 1;
            delete[] newLiczba;
        }
        return Result;
    }
    friend BrtkvE18 operator+(e18 left, const BrtkvE18& right) {
        return right + left;
    }

    BrtkvE18& operator-=(const BrtkvE18& other)  {
        if(*this <= other){
            wstawWartosc("0");
            return *this;
        }
        if(rozmiar == 1){
            wstawWartosc(std::to_string(liczba[0] - other.liczba[0]));
            return *this;
        }
        int roz_max = std::max(rozmiar, other.rozmiar); 
        int roz_min = std::min(rozmiar, other.rozmiar);
        int ink = -1;
        if(roz_max==roz_min){
            for(int i = roz_max-1; i > -1; i--){
                if(liczba[i] != other.liczba[i]){
                    ink = i;
                    break;
                }
            }
            for(int i = roz_max-1; i > ink; i--){
                liczba[i] = 0;
            }
            liczba[ink] -= other.liczba[ink];
    
            for(int i = ink-1; i > -1; i--){
            liczba[i+1]--;
            liczba[i] += 1000000000000000000 - other.liczba[i];
            }
            for(int i = 0; i< roz_max -1;i++){
                liczba[i+1]+=liczba[i]/1000000000000000000;
                liczba[i] %= 1000000000000000000;
            }
        }else{//różne rozmiary
           
          
            for(int i = roz_max-2; i > -1; i--){
            liczba[i+1]--;
            liczba[i] += 1000000000000000000;
            }

            for(int i = 0; i < roz_min; i++){
               liczba[i] -= other.liczba[i];
            }
            for(int i = 0; i< roz_max -1;i++){
                liczba[i+1]+=liczba[i]/1000000000000000000;
                liczba[i] %= 1000000000000000000;
            }

        }
      
        for(int i = roz_max-1; i >-1; i --){
            if(liczba[i] != 0){
              ink = i;
              break;
            }
        }
        if(ink + 1 == roz_max){
            return *this;
        }
       
        e18* newLiczba = new e18[ink+1];
        for (int i = 0; i < ink+1; i++) {
            newLiczba[i] = liczba[i];
        } 
        rozmiar = ink+1;
        delete[] liczba;
        liczba = new e18[ink+1];
        for (int i = 0; i < ink+1; i++) {
            liczba[i] = newLiczba[i];
        } 
        delete[] newLiczba;
        return *this;
    }

    BrtkvE18 operator-(const BrtkvE18& other) const {
        if(*this <= other){
            return BrtkvE18("0");
        }

        if(rozmiar == 1){
            return BrtkvE18(std::to_string(liczba[0] - other.liczba[0]));
        }
        int roz_max = std::max(rozmiar, other.rozmiar); 
        int roz_min = std::min(rozmiar, other.rozmiar);
        int ink = -1;
        BrtkvE18 Result(roz_max); 
        if(roz_max==roz_min){
            for(int i = roz_max-1; i > -1; i--){
                if(liczba[i] != other.liczba[i]){
                    ink = i;
                    break;
                }
            }
            Result.liczba[ink] = liczba[ink] - other.liczba[ink];
    
            for(int i = ink-1; i > -1; i--){
            Result.liczba[i+1]--;
            Result.liczba[i] = 1000000000000000000+liczba[i] - other.liczba[i];
            }
            for(int i = 0; i< roz_max -1;i++){
                Result.liczba[i+1]+=Result.liczba[i]/1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }
        }else{//różne rozmiary
           
            Result.liczba[roz_max-1] = liczba[roz_max-1];
            for(int i = roz_max-2; i > -1; i--){
            Result.liczba[i+1]--;
            Result.liczba[i] = 1000000000000000000+liczba[i];
            }

            for(int i = 0; i < roz_min; i++){
                Result.liczba[i] -= other.liczba[i];
            }
            for(int i = 0; i< roz_max -1;i++){
                Result.liczba[i+1]+=Result.liczba[i]/1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }

        }
       
        for(int i = roz_max-1; i >-1; i --){
            if(Result.liczba[i] != 0){
              ink = i;
              break;
            }
        }
        if(ink + 1 == roz_max){
            return Result;
        }
        e18* newLiczba = new e18[ink+1];
        for (int i = 0; i < ink+1; i++) {
            newLiczba[i] = Result.liczba[i];
        } 
        Result.rozmiar = ink+1;
        delete[] Result.liczba;
        Result.liczba = new e18[ink+1];
        for (int i = 0; i < ink+1; i++) {
            Result.liczba[i] = newLiczba[i];
        } 
        delete[] newLiczba;
        return Result;
    }
    BrtkvE18 operator-(e18 other) const {
        if(*this<=other) return BrtkvE18("0");
        if(rozmiar == 1){
            return BrtkvE18(std::to_string(liczba[0] - other));
        }
        BrtkvE18 Result(*this);
        int ink=0;
        if(liczba[0]>other){
            Result.liczba[0]-=other;
            return Result;
        }else{
            for(int i = 1; i < rozmiar; i++){
                if(Result.liczba[i]>0){
                    ink=i;
                    break;
                }
            }
        }
        for(int i = ink; i >0; i--){
            Result.liczba[i]--;
            Result.liczba[i-1]+=1000000000000000000;
        }
        Result.liczba[0]-=other;
        if(Result.liczba[rozmiar-1]==0){
            e18* newLiczba = new e18[rozmiar-1];
            for (int i = 0; i < rozmiar-1; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar--;
            delete[] Result.liczba;
            Result.liczba = new e18[rozmiar+1];       
            for (int i = 0; i < rozmiar-1; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            Result.liczba[rozmiar] = 1;
            delete[] newLiczba;
        }
        return Result;
    }
    friend BrtkvE18 operator-(e18 left, const BrtkvE18& right) {
        if(right>=left) return BrtkvE18("0");
        return BrtkvE18(std::to_string(left - right.liczba[0]).c_str());
    }
    BrtkvE18& operator--(int notUsed) {
        *this -= BrtkvE18("1");
        return *this;
    }
    BrtkvE18& operator++(int notUsed) {
        *this += BrtkvE18("1");
        return *this;
    }
    BrtkvE18& operator*=(const BrtkvE18& other) {
        int roz_max = rozmiar + other.rozmiar;
        BrtkvE18 Result(roz_max); 
        for (int i = 0; i < other.rozmiar*2; i++) {
            for (int j = 0; j < rozmiar*2; j++) {
                e18 temp = ((j%2==0)?liczba[j/2]%1000000000:liczba[j/2]/1000000000) * ((i%2==0)?other.liczba[i/2]%1000000000:other.liczba[i/2]/1000000000);
                if((i+j)%2==0){
                    Result.liczba[(i+j)/2] += temp;
            }else{
                Result.liczba[(i+j)/2] += (temp%1000000000)*1000000000;
                Result.liczba[(i+j)/2+1] += temp/1000000000;

            }
             
            }
           
            for(int i = 0; i< roz_max -1 ;i++){
                Result.liczba[i+1]+=Result.liczba[i]/1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }
        }
        if(Result.liczba[roz_max-1]==0){
            roz_max--;
            if (roz_max==0)
            {
                *this = Result;
                return *this;
            }
            e18* newLiczba = new e18[roz_max];
            for (int i = 0; i < roz_max; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar = roz_max;
            delete[] Result.liczba;
            Result.liczba = new e18[roz_max];       
            for (int i = 0; i < roz_max; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            delete[] newLiczba;
        }
        *this = Result;
        return *this;
    }
    BrtkvE18 operator*(const BrtkvE18& other) const {
        int roz_max = rozmiar + other.rozmiar;
        BrtkvE18 Result(roz_max); 
        for (int i = 0; i < other.rozmiar*2; i++) {
            for (int j = 0; j < rozmiar*2; j++) {
                e18 temp = ((j%2==0)?liczba[j/2]%1000000000:liczba[j/2]/1000000000) * ((i%2==0)?other.liczba[i/2]%1000000000:other.liczba[i/2]/1000000000);
                if((i+j)%2==0){
                    Result.liczba[(i+j)/2] += temp;
            }else{
                Result.liczba[(i+j)/2] += (temp%1000000000)*1000000000;
                Result.liczba[(i+j)/2+1] += temp/1000000000;

            }
             
            }
           
            for(int i = 0; i< roz_max -1 ;i++){
                Result.liczba[i+1]+=Result.liczba[i]/1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }
        }
        if(Result.liczba[roz_max-1]==0){
            roz_max--;
            if (roz_max==0)
            {
                return BrtkvE18("0");
            }
            e18* newLiczba = new e18[roz_max];
            for (int i = 0; i < roz_max; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar = roz_max;
            delete[] Result.liczba;
            Result.liczba = new e18[roz_max];       
            for (int i = 0; i < roz_max; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            delete[] newLiczba;
        }
        return Result;
    }
    BrtkvE18 operator*(e18 other) const {
        if(other == 0 && *this == 0) return BrtkvE18("0");
        int roz_max = rozmiar + 1;
        BrtkvE18 Result(roz_max);
         
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < rozmiar*2; j++) {
                e18 temp = ((j%2==0)?liczba[j/2]%1000000000:liczba[j/2]/1000000000) * ((i%2==0)?other%1000000000:other/1000000000);
                if((i+j)%2==0){
                    Result.liczba[(i+j)/2] += temp;
            }else{
                Result.liczba[(i+j)/2] += (temp%1000000000)*1000000000;
                Result.liczba[(i+j)/2+1] += temp/1000000000;

            }
             
            }
           
            for(int i = 0; i< roz_max -1 ;i++){
                Result.liczba[i+1]+=Result.liczba[i]/1000000000000000000;
                Result.liczba[i] = Result.liczba[i] % 1000000000000000000;
            }
        }
        if(Result.liczba[roz_max-1]==0){
            roz_max--;
            if (roz_max==0)
            {
                return BrtkvE18("0");
            }
            e18* newLiczba = new e18[roz_max];
            for (int i = 0; i < roz_max; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar = roz_max;
            delete[] Result.liczba;
            Result.liczba = new e18[roz_max];       
            for (int i = 0; i < roz_max; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            delete[] newLiczba;
        }
        return Result;
    }
    friend BrtkvE18 operator*(e18 left, const BrtkvE18& right) {
        return right*left;
    }
    
    BrtkvE18& operator/=(int dzielnik)  {
        if (*this == BrtkvE18("0"))
        {
            wstawWartosc("0");
            return *this;

        }
        if (dzielnik == 0)
        {
            return *this;
        }

        
        int roz_max = rozmiar;
        e18 resztov = 0;
        e18 wynikov = 0;
        e18 st_cal = 1000000000000000000/dzielnik;
        e18 st_rsz = 1000000000000000000%dzielnik;
       

        for (int j = roz_max-1; j >-1; j--) {
            wynikov = resztov*st_cal;
            liczba[j] +=resztov*st_rsz;
            resztov=liczba[j] % dzielnik;
            liczba[j]=(liczba[j]/dzielnik)+wynikov;
           }

        if(liczba[roz_max-1]==0){

            roz_max--;


            if (roz_max==0)
            {   
                wstawWartosc("0");
                return *this;
    
            }
            
            e18* newLiczba = new e18[roz_max];
            for (int i = 0; i < roz_max; i++) {
                newLiczba[i] = liczba[i];
            }
            rozmiar = roz_max;
            delete[] liczba;
            liczba = new e18[roz_max];       
            for (int i = 0; i < roz_max; i++) {
                liczba[i] = newLiczba[i];
            }
            delete[] newLiczba;
        }
        return *this;
    }
    BrtkvE18 operator/(int dzielnik) const {
        if (*this == BrtkvE18("0"))
        {
            return BrtkvE18("0");
        }
        if (dzielnik == 0)
        {
            return *this;
        }

        
        int roz_max = rozmiar;
        e18 resztov = 0;
        e18 wynikov = 0;
        e18 st_cal = 1000000000000000000/dzielnik;
        e18 st_rsz = 1000000000000000000%dzielnik;
        BrtkvE18 Result(roz_max);
        for (int i = 0; i < roz_max; i++) {
            Result.liczba[i] = liczba[i];
        }
        for (int j = roz_max-1; j >-1; j--) {
            wynikov = resztov*st_cal;
            Result.liczba[j] +=resztov*st_rsz;
            resztov=Result.liczba[j] % dzielnik;
            Result.liczba[j]=(Result.liczba[j]/dzielnik)+wynikov;
           }

        if(Result.liczba[roz_max-1]==0){

            roz_max--;


            if (roz_max==0)
            {   
                return BrtkvE18("0");
                
                
            }
            
            e18* newLiczba = new e18[roz_max];
            for (int i = 0; i < roz_max; i++) {
                newLiczba[i] = Result.liczba[i];
            }
            Result.rozmiar = roz_max;
            delete[] Result.liczba;
            Result.liczba = new e18[roz_max];       
            for (int i = 0; i < roz_max; i++) {
                Result.liczba[i] = newLiczba[i];
            }
            delete[] newLiczba;
        }
        return Result;
    }
    friend BrtkvE18 operator/(e18 left, const BrtkvE18& right) {
        if(right>left) return BrtkvE18("0");
        if(right==left) return BrtkvE18("1");
        return BrtkvE18(std::to_string(left / right.liczba[0]).c_str());
    }
    BrtkvE18& operator%=(int mod)  {
        if (mod == 0)
        {
            return *this;
        }

        e18 resztov = 0;
        e18 st_rsz = 1000000000000000000%mod;

        for (int j = rozmiar-1; j >-1; j--) {
            resztov =resztov*st_rsz;
            resztov += liczba[j]%mod;
            resztov %= mod;
           }
           wstawWartosc(std::to_string(resztov).c_str());
        return *this;
    }
    BrtkvE18 operator%(int mod) const {
        if (mod == 0)
        {
            return *this;
        }

        e18 resztov = 0;
        e18 st_rsz = 1000000000000000000%mod;

        for (int j = rozmiar-1; j >-1; j--) {
            resztov =resztov*st_rsz;
            resztov += liczba[j]%mod;
            resztov %= mod;
           }
           BrtkvE18 Result(std::to_string(resztov).c_str());
        return Result;
    }
    static BrtkvE18 pow(const BrtkvE18 left, const BrtkvE18 right){
        if(right == 0) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        BrtkvE18 Result("1");
        BrtkvE18 right2(right);
        BrtkvE18 Potegov(left);

        while(right2!=0){
          

            if(right2%2==1){

                Result=Result*Potegov;
            }
            Potegov=Potegov*Potegov;
            right2 = right2/2;
        }
        return Result;
    }
    static BrtkvE18 pow(const BrtkvE18 left, e18 right){
        if(right == 0) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        BrtkvE18 Result("1");
        
        BrtkvE18 Potegov(left);

        while(right!=0){
          

            if(right%2==1){

                Result=Result*Potegov;
            }
            Potegov=Potegov*Potegov;
            right = right/2;
        }
        return Result;
    }
    static BrtkvE18 pow(e18 left, e18 right){
        if(right == 0) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        BrtkvE18 Result("1");
        
        BrtkvE18 Potegov(std::to_string(left));

        while(right!=0){
          

            if(right%2==1){

                Result=Result*Potegov;
            }
            Potegov=Potegov*Potegov;
            right = right/2;
        }
        return Result;
    }
    static BrtkvE18 tetration(const BrtkvE18 left, const BrtkvE18 right){
        if(right == 0 || left == 1) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        if(right == 1) return left;

        BrtkvE18 Result(left);
        BrtkvE18 right2(right);
        BrtkvE18 Potegov(left);

        for(int i = 0; i< right-1; i++){
            Result = BrtkvE18::pow(left, Result);
        }
        return Result;
    }
    
    static BrtkvE18 pentation(const BrtkvE18 left, const BrtkvE18 right){
        if(right == 0 || left == 1) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        if(right == 1) return left;

        BrtkvE18 Result(left);
        BrtkvE18 right2(right);
        BrtkvE18 Potegov(left);

        for(int i = 0; i< right-1; i++){
            Result = BrtkvE18::tetration(left, Result);
        }
        return Result;
    }

    static BrtkvE18 hexation(const BrtkvE18 left, const BrtkvE18 right){
        if(right == 0 || left == 1) return BrtkvE18("1");
        if(left == 0) return BrtkvE18("0");
        if(right == 1) return left;

        BrtkvE18 Result(left);
        BrtkvE18 right2(right);
        BrtkvE18 Potegov(left);

        for(int i = 0; i< right-1; i++){
            Result = BrtkvE18::pentation(left, Result);
        }
        return Result;
    }
////// dzielenie, pierwiastkowanie, iteracja, 
    bool operator<(const BrtkvE18& other)const {
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
                if(liczba[i] < other.liczba[i]){
                    return true;
                }
            }
        }else if(rozmiar < other.rozmiar){
            return true;
        }

            return false;
        
    }
    bool operator<(e18 other)const {
        if(rozmiar!=1) return false;

        if(liczba[0]<other) return true;
            return false;
        
    }
    friend bool operator<(long long left, const BrtkvE18& right) {
        return right>left;
    }

    bool operator>(const BrtkvE18& other)const {
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
                if(liczba[i] > other.liczba[i]){
                    return true;
                }
            }
        }else if(rozmiar > other.rozmiar){
            return true;
        }

            return false;
        
    }
    bool operator>(e18 other)const {
        if(rozmiar!=1) return true;

        if(liczba[0]>other) return true;
            return false;
        
    }
    friend bool operator>(long long left, const BrtkvE18& right) {
        return right<left;
    }
    bool operator<=(const BrtkvE18& other)const {
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
                if(liczba[i] < other.liczba[i]){
                    return true;
                }
                if(liczba[i] > other.liczba[i]){
                    return false;
                }
            }
            return true;
        }else if(rozmiar < other.rozmiar){
            return true;
        }

            return false;
        
    }
    bool operator<=(e18 other)const {
        if(rozmiar!=1) return false;
        if(liczba[0]<=other) return true;
            return false;
    }
    friend bool operator<=(long long left, const BrtkvE18& right) {
        return right>=left;
    }
    bool operator>=(const BrtkvE18& other)const {
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
           
                if(liczba[i] > other.liczba[i]){

                    return true;
                }
                if(liczba[i] < other.liczba[i]){
                    return false;
                }
            }
            return true;
        }else if(rozmiar > other.rozmiar){
            return true;
        }

            return false;
        
    }
    bool operator>=(e18 other)const {
        if(rozmiar!=1) return true;

        if(liczba[0]>=other) return true;
            return false;
        
    }
    friend bool operator>=(long long left, const BrtkvE18& right) {
        return right<=left;
    }
    bool operator==(const BrtkvE18& other)const {
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
                if(liczba[i] != other.liczba[i]){
                    return false;
                }
            }
            return true;
        }

            return false;
        
    }
    bool operator==(e18 other)const {
        if(rozmiar!=1) return false;

        if(liczba[0]==other) return true;
            return false;
        
    }
    friend bool operator==(long long left, const BrtkvE18& right) {
        return right==left;
    }
    bool operator!=(const BrtkvE18& other) const{
        if(rozmiar == other.rozmiar){
            for(int i = rozmiar -1; i > -1; i--){
                if(liczba[i] != other.liczba[i]){
                    return true;
                }
            }
            return false;
        }

            return true;
        
    }
    bool operator!=(e18 other)const {
        if(rozmiar!=1) return true;

        if(liczba[0]!=other) return true;
            return false;
        
    }
    friend bool operator!=(long long left, const BrtkvE18& right) {
        return right!=left;
    }
};
