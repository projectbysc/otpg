
// this code is the backend which can be used in a compiler


#include <iostream>
#include <set>
#include <string>
#include <chrono>

using namespace std;

string generateUniqueOTP(int length) {
    if (length > 10) {
        cerr << "Max unique digits in OTP is 10." << endl;
        return "";
    }

    auto now = chrono::high_resolution_clock::now();
    auto timeSeed = chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();

    set<int> uniqueDigits;

    int seed = static_cast<int>(timeSeed) % 1000000007;
    int multiplier = 31;

    while (uniqueDigits.size() < length) {
        seed = (seed * multiplier + 1) % 1000000007;
        int digit = (seed % 10 + 10) % 10;
        uniqueDigits.insert(digit);
    }

    string otp = "";
    for (int digit : uniqueDigits) {
        otp += to_string(digit);
    }

    return otp;
}

int main() {
    int otpLength = 6;
    string otp = generateUniqueOTP(otpLength);
    cout << "Generated OTP: " << otp << endl;
    return 0;
}
