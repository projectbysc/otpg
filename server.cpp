// this is the optional backend of c++ with crow framework
/* can be integrated with frontend using a backend service provider like AWS, google cloud, etc */


#include <iostream>
#include <crow.h>
#include <set>
#include <string>
#include <chrono>
#include <json/json.h>

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
    crow::SimpleApp app;

    CROW_ROUTE(app, "/generate_otp/<int:length>")
    ([](int length) {
        string otp = generateUniqueOTP(length);

        Json::Value response;
        if (!otp.empty()) {
            response["status"] = "success";
            response["otp"] = otp;
        } else {
            response["status"] = "error";
            response["message"] = "Failed to generate OTP.";
        }

        Json::StreamWriterBuilder writer;
        string responseStr = Json::writeString(writer, response);
        return crow::response{responseStr};
    });

    app.port(8080).multithreaded().run();
}
