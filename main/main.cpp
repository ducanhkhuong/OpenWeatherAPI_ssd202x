#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include <fstream>
#include <mutex>

using namespace std;
using json = nlohmann::json;

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    size_t totalSize = size * nmemb;
    buffer->append((char*)contents, totalSize);
    return totalSize;
}

mutex dataMutex;
json weatherData;

void fetchWeatherData(const string& apiUrl) {
    CURL* curl;
    CURLcode res;
    string readBuffer;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "Error : " << curl_easy_strerror(res) << endl;
        } else {
            json weatherData = json::parse(readBuffer);
            string weatherInfo = "Infor WeatherData\n";
            weatherInfo += "Status:"     + to_string(weatherData["cod"].get<int>()) +"\n";
            weatherInfo += "longitude:"   + to_string(weatherData["coord"]["lon"].get<float>()) +"\n";
            weatherInfo += "latitude:"    + to_string(weatherData["coord"]["lat"].get<float>()) +"\n";

            weatherInfo += "Location: " + weatherData["name"].get<string>() + "\n";
            weatherInfo += "Timezone: " + to_string(weatherData["timezone"].get<int>()) + "\n";
            weatherInfo += "Id:"        + to_string(weatherData["id"].get<int>()) + "\n"; 
            weatherInfo += "Country:  " + weatherData["sys"]["country"].get<string>() + "\n";
            weatherInfo += "Weather: " +  weatherData["weather"][0]["description"].get<string>() + "\n";

            weatherInfo += "Temperature: "+ to_string(weatherData["main"]["temp"].get<float>() - 273.14) + "\n";
            weatherInfo += "Humidity: "   + to_string(weatherData["main"]["humidity"].get<int>())        + "\n";
            weatherInfo += "Wind Speed: " + to_string(weatherData["wind"]["speed"].get<float>())         + "\n";
            weatherInfo += "Visibility: " + to_string(weatherData["visibility"].get<int>())              + "\n";
            weatherInfo += "Pressure: "   + to_string(weatherData["main"]["pressure"].get<int>())        + "\n";
            cout << weatherInfo << endl;
        }
        curl_easy_cleanup(curl);
    }
    this_thread::sleep_for(chrono::seconds(5));
}



int main() {
    string apiKey    = "4455d3b14a1f08c648288279e73693ac";
    string longitude = "105.83";
    string latitude  = "21.02";
    string apiUrl    = "https://api.openweathermap.org/data/2.5/weather?lat=" + latitude +"&lon="+ longitude +"&appid=" + apiKey;

	while (true)
	{
		thread fetchThread(fetchWeatherData, apiUrl);
		fetchThread.join();
	}
}
