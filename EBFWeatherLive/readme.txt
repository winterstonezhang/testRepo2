This weather application is developed for blackberry 10 platform. With this application, the user can query 
the live weather inforamation. This application query the weather live data provided by website "www.wunderground.com",
and get returned the http response in XML format. Afterwards, this application will parse the XML response,
extract the desired fields and displays the weather data to the user. The weather icon is downloaded from web via
the icon URL specified in the returned XML response.
Only the live weather data are displayed, and the forecast weather data are not displayed.
 
For example, a http request with the following link is made to query the current weather information
for the city "Bochum" in Germany. You can try this on your browser to see the XML response.

http://api.wunderground.com/api/9c36417de74aa4ee/geolookup/conditions/forecast/q/Germany/Bochum.xml
 
 
The application logic is written in the Qt classes WeatherDataMgr and ImageFromWeb.
The user GUI is written in the main.qml page.  
 
 
 
The following major techniks are used:
- BB10 cascades framework
- QML, Qt C++, signal, slot
- QNetworkRequest, QNetworkReply to perform the http request and process the http response
- bb::data::XmlDataAccess to parse the XML data 
 


To edit the source codes of this application, please use "QNX® Momentics® IDE for BlackBerry® 10 Native SDK".
To run this application, please use the simulator "Blackberry 10 Simulator".