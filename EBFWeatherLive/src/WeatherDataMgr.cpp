/**
 * @file WeatherDataMgr.cpp
 * @author Xiaodong Zhang
 * @version 1.0
 *
 * This class makes the http request of the weather live data provided by website "www.wunderground.com",
 * and get the http response in XML format. Afterwards, this class will parse the xml string,
 * extract the desired fields and store these data into the corresponding member variables.
 * Only the live weather data are stored, but the forecast weather data are not stored in this class.
 *
 * For example, a http request over the following link is made to query the current weather information
 * for the city "Bochum in Germany". You can try this on your browser to see the XML response.
 *
 * http://api.wunderground.com/api/9c36417de74aa4ee/geolookup/conditions/forecast/q/Germany/Bochum.xml
 *
 */


#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/LocaleHandler>
#include <bb/data/XmlDataAccess>

#include "WeatherDataMgr.hpp"
#include "ImageFromWeb.hpp"

using namespace bb::cascades;
using namespace ebf;


/**
 * Constructor of class WeatherDataMgr.
 * @param pApp:	 the application as the parent object.
 * @param pRoot: root pane of the qml page.
 */
WeatherDataMgr::WeatherDataMgr(Application *pApp, AbstractPane *pRoot)
	: QObject(pApp)
	, m_pNetworkAccessManager(new QNetworkAccessManager(this))
	, m_pRootPane(pRoot)
	, m_strWeatherQueryUrl("http://api.wunderground.com/api/9c36417de74aa4ee/geolookup/conditions/forecast/q/Germany/")
{
	//initialize the member variables
	reset();
}


/**
 * Query the weather live data for a specified city.
 *
 * @param strCity: The City whose weather live data will be queried.
 * @return
 */
void WeatherDataMgr::requestWeatherData(const QString& strCity)
{
    //check if the city is empty
    if(strCity.trimmed().isEmpty()) {
    	setError("Please select a city.");
    	setActive(false);
    	setSucceeded(false);
    	return;
    }else{

	reset();
	//the query is starting now.
	setActive(true);
	//construct the URL string with the given city name
    QString strUrl = m_strWeatherQueryUrl + strCity + ".xml";

    const QUrl url(strUrl);
    QNetworkRequest networkRequest(url);

    //make the asynchronous request now
    QNetworkReply* networkReply = m_pNetworkAccessManager->get(networkRequest);

    //SLOT method onNetworkReply will process the reply
    connect(networkReply, SIGNAL(finished()), this, SLOT(onNetworkReply()));
    }
}


/**
 * SLOT method to process the HTTP response for the weather query .
 */
void WeatherDataMgr::onNetworkReply()
{
	//Initially, set the m_succeeded to be true, which will be set to false later when the reply has error.
	setSucceeded(true);

	//Find out the object of QNetworkReply which send the SIGNAL
    QNetworkReply* networkReply = qobject_cast<QNetworkReply*>(sender());

    QString strResponse;
    if (networkReply) {
        if (networkReply->error() == QNetworkReply::NoError) {//if the reply is correct
            const int iAvailable = networkReply->bytesAvailable();
            if (iAvailable > 0) {
            	//read the reply as bytes, convert it to QString and assign to the response QString
                const QByteArray buffer(networkReply->readAll());
                strResponse = buffer;
                //extract the weather data from the XML response XML.
                extractWeatherData(strResponse);
            }
        } else {//if the reply has error
            // Get http status code if there is error with the http reply
            const int httpStatus = networkReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            //set the error string to enable the display in the qml
            setError(QString("Http Error: %1").arg(httpStatus));
            //set the succeeded flag
            setSucceeded(false);
        }

        //The object will be deleted when control returns to the event loop.
        networkReply->deleteLater();
    }

    //if the response string is empty, it is also an error
    if (strResponse.trimmed().isEmpty()) {
    	 setError("Unable to retrieve the http response");
    	 setSucceeded(false);
    }
}




/**
 * Extract the weather data from the response string in format of XML.
 * In this method, class bb::data::XmlDataAccess is used to parse the XML string,
 * and ImageFromWeb is used to load the image from web to the imageView on qml page.
 *
 * @param strResponse: The XML response string from which the weather data are extracted.
 * @return
 * @see  ImageFromWeb  bb::data::XmlDataAccess
 */
void WeatherDataMgr::extractWeatherData(const QString& strResponse) {
	//print this response to the console for debug purpose
    fprintf(stdout, "%s\n", qPrintable(QString("response="+strResponse)));
    fflush(stdout);

    bb::data::XmlDataAccess xda;
    //weather live data are located from node "/response/current_observation" of the XML response.
	QVariant currentObservationQVariant = xda.loadFromBuffer (strResponse, "/response/current_observation");
	//the loaded data is stored in a QVariantMap
	QVariantMap currentObservationMap = currentObservationQVariant.value<QVariantMap>();

	//extract the weather data and assign them to the matching member varaibles
	setWeatherDescription(currentObservationMap["weather"].value<QString>());
	setTemperature(currentObservationMap["temp_c"].value<QString>());
	setTemperatureFeelLike(currentObservationMap["feelslike_c"].value<QString>());
	setHumidity(currentObservationMap["relative_humidity"].value<QString>());
	setWindDirection(currentObservationMap["wind_dir"].value<QString>());
	setWindSpeed(currentObservationMap["wind_kph"].value<QString>());

	/******************load the weather icon image from web************************/
	// Retrieves the root container from the page
	ImageView *pImageView = m_pRootPane->findChild<ImageView*>("weatherIconImageView");
	ebf::ImageFromWeb* pImageFromWeb = new ebf::ImageFromWeb(this);
	QString strIconUrl = currentObservationMap["icon_url"].value<QString>();
	//load the image from web and assign it to the imageView of qml page
	pImageFromWeb->loadImageToImageView(pImageView,strIconUrl, m_pNetworkAccessManager);

	//the request and response of the weather data is finished now.
    setActive(false);
}


/**
 * Reset the values of member variables for weather data and flags.
 */
void WeatherDataMgr::reset()
{
	setWeatherDescription("");
	setTemperature("");
	setTemperatureFeelLike("");
	setHumidity("");
	setWindDirection("");
	setWindSpeed("");
	setActive(false);
	setSucceeded(false);
	setError("");
}

/**
 * Return the weather description.
 * @return The weather description as QString
 */
QString WeatherDataMgr::weatherDescription() const {
	return m_strWeatherDescription;
}

/**
 * Return the temperature.
 * @return The temperature as QString
 */
QString WeatherDataMgr::temperature() const {
	return m_strTemperature;
}

/**
 * Return the feel-like temperature.
 * @return The feel-like temperature as QString.
 */
QString WeatherDataMgr::temperatureFeelLike() const
{
	return m_strTemperatureFeelLike;
}

/**
 * Return the value of humidity.
 * @return The value of humidity as QString.
 */
QString WeatherDataMgr::humidity() const
{
	return m_strHumidity;
}

/**
 * Return the wind direction.
 * @return The wind direction as QString.
 */
QString WeatherDataMgr::windDirection() const
{
	return m_strWindDirection;
}

/**
 * Return the value of the wind speed.
 * @return The wind speed as QString.
 */
QString WeatherDataMgr::windSpeed() const
{
	return m_strWindSpeed;
}

/**
 * Return whether the weather query is running now.
 * @return True if the weather query is running, false otherwise.
 */
bool WeatherDataMgr::active() const {
	return m_bActive;
}

/**
 * Return if the last weather query is done successfully.
 * @return True if the last weather query is done successfully, false otherwise.
 */
bool WeatherDataMgr::succeeded() const {
	return m_bSucceeded;
}

/**
 * Return the error message for the last weather query.
 * @return Error message as QString.
 */
QString WeatherDataMgr::error() const {
	return m_strError;
}



/**
 * Set weather description and emit signal weatherDescriptionChanged().
 *
 * @param strWeatherDescription: Value of weather description to be assigned.
 * @return
 */
void WeatherDataMgr::setWeatherDescription(const QString& strWeatherDescription)
{
	m_strWeatherDescription = strWeatherDescription;
	emit weatherDescriptionChanged();
}

/**
 * Set temperature and emit signal temperatureChanged().
 *
 * @param strTemperature: Value of temperature to be assigned.
 */
void WeatherDataMgr::setTemperature(const QString& strTemperature)
{
	m_strTemperature = strTemperature;
	emit temperatureChanged();
}
/**
 * Set the feel-like temperature and emit signal temperatureFeelLikeChanged().
 *
 * @param strTemperatureFeelLike: Value of feel-like temperature to be assigned.
 */
void WeatherDataMgr::setTemperatureFeelLike(const QString& strTemperatureFeelLike)
{
	m_strTemperatureFeelLike = strTemperatureFeelLike;
	emit temperatureFeelLikeChanged();
}

/**
 * Set humidity and emit signal humidityChanged().
 *
 * @param strHumidity: Value of humidity to be assigned.
 */
void WeatherDataMgr::setHumidity(const QString& strHumidity)
{
	m_strHumidity = strHumidity;
	emit humidityChanged();
}

/**
 * Set wind direction and emit signal windDirectionChanged().
 *
 * @param strWindDirection: Value of wind direction to be assigned.
 */
void WeatherDataMgr::setWindDirection(const QString& strWindDirection)
{
	m_strWindDirection = strWindDirection;
	emit windDirectionChanged();
}

/**
 * Set wind speed and emit signal windSpeedChanged().
 *
 * @param strWindSpeed: Value of wind speed to be assigned.
 */
void WeatherDataMgr::setWindSpeed(const QString& strWindSpeed)
{
	m_strWindSpeed = strWindSpeed;
	emit windSpeedChanged();
}




/**
 * Set flag variable "active" and emit signal activeChanged().
 *
 * @param bActive: Boolean value indicating if the weather query is running.
 */
void WeatherDataMgr::setActive(const bool bActive)
{
	m_bActive = bActive;
	emit activeChanged();
}

/**
 * Set flag variable "succeeded" and emit signal succeededChanged().
 *
 * @param bActive: Boolean value indicating if the last weather query succeeded.
 */
void WeatherDataMgr::setSucceeded(const bool succeeded)
{
	m_bSucceeded = succeeded;
	emit succeededChanged();
}

/**
 * Set the error message and emit signal errorChanged().
 *
 * @param strError: Error message string to be assigned.
 */
void WeatherDataMgr::setError(const QString& strError)
{
	m_strError = strError;
	emit errorChanged();
}



