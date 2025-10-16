                                                      
#include <iostream> 
#include <string>   
#include <algorithm>
#include <cctype>
#include <curl/curl.h>
#include <chrono>
#include <thread>

void loadingScreen() {
char spinner[] = {'|', '/', '-', '\\'};
    for (int i = 0; i < 40; ++i) {
        std::cout << "\rTimE tO phiSh " << spinner[i % 4] << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\rLoading complete!   " << std::endl;

}

void sendEmail(std::string email_address) {
//send the email code

CURL *curl;
CURLcode res;

//config
    std::string apiKey = "re_fK8jSVbG_6rJqzcquNfFwh3oJ9gWtGcmA"; 
    std::string from = "friendsnotfood@resend.dev";          
    std::string to = email_address;

    // json payload
std::string jsonData = "{"
        "\"from\": \"Friends Not Food <friendsnotfood@resend.dev>\","
        "\"to\": [\"" + to + "\"],"
        "\"subject\": \"Seafood Recipes\","
        "\"html\": \"<h2>Healthy Recipe of the Week</h2><p>Are you trying to <i>lower your blood pressure</i>? Or maybe you'd like to <b>improve cognitve funtion</b> through food?</p><p><br></br>Look no further! Chef Nemo releases weekly meal plans for you to follow along with. Includes a weekly grocery list, allergy substitutions, and a step by step cook book.</p><p>Click to follow the <a href=https://www.youtube.com/watch?v=_yntbXDAhNk><b>Weekly Newsletter</b></a>!</p><p><br></br>Sincerly,<br></br>Chef Nemo</p>\""
        "}";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        std::string authHeader = "Authorization: Bearer " + std::string(apiKey);
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.resend.com/emails");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
        else
            std::cout << "Email sent successfully to " << to << "!\n";

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    curl_global_cleanup();
}

int main() {

    std::string first;
    std::string last;
    std::string number;
    std::string buzz;

    std::cout << "Please enter their first name: ";
    std::cin >> first;

    std::cout << "Please enter their last name: ";
    std::cin >> last;

    std::cout << "Please enter their favorite number: ";
    std::cin >> number;

    std::cout << "Please enter any other buzz words you think may help: ";
    std::cin >> buzz;

    std::cout<<std::endl;
    
    //Names to lowercase
    std::transform(first.begin(), first.end(), first.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    std::transform(last.begin(), last.end(), last.begin(),
                   [](unsigned char d){ return std::tolower(d); });

    std::transform(number.begin(), number.end(), number.begin(),
                   [](unsigned char n){ return std::tolower(n); });

    std::transform(buzz.begin(), buzz.end(), buzz.begin(),
                   [](unsigned char b){ return std::tolower(b); });

//come up with diff emails

    std::string firstLetterLast = first.substr(0, 1) + last;
    std::string firstLetterLast_Dot = first.substr(0, 1) + "." + last;
    std::string firstLetterLast_Dash = first.substr(0, 1) + "-" + last;
    std::string initials = first.substr(0, 1) + last.substr(0, 1);
    std::string firstOnly = first;
    std::string lastOnly = last;

    std::string layer_one[] = {firstLetterLast, firstLetterLast_Dot, firstLetterLast_Dash, initials, firstOnly, lastOnly };
    int size_of_one = sizeof(layer_one) / sizeof(layer_one[0]);

     std::string layer_two[] = {"@gmail.com", "@yahoo.com", "@outlook.com", "@comcast.net"};
     int size_of_two = sizeof(layer_two) / sizeof(layer_two[0]); 

     loadingScreen();

     std::string temp;

     for (int i=0; i<size_of_one; ++i) {
	for(int j=0; j<size_of_two; ++j) {
	temp = layer_one[i] + layer_two[j];
	std::cout<< temp <<std::endl;	
//	sendEmail(temp);

	temp = layer_one[i] + number + layer_two[j];
	std::cout<< temp <<std::endl;
//      sendEmail(temp);

	temp = layer_one[i] + buzz + layer_two[j];
	std::cout<< temp <<std::endl;
//      sendEmail(temp);


	} 
 }


    std::string mine = "jstolimaria@gmail.com";

    sendEmail(mine);

    return 0;
}


