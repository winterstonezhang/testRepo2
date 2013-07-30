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

#ifndef WeatherDataMgr_HPP_
#define WeatherDataMgr_HPP_

#include <QObject>
#include <QtCore/QString>
#include <QtNetwork/QtNetwork>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/ImageView>
#include <bb/cascades/Image>
#include <bb/cascades/Application>




namespace ebf
{
	/*!
	 * @brief This class queries the weather information and manage the replied weather data.
	 */
	class WeatherDataMgr : public QObject
	{
		Q_OBJECT

		//Declare the variables as Q_PROPERTY so that they can be accessed from the qml page.
		Q_PROPERTY(QString weatherDescription READ weatherDescription WRITE setWeatherDescription NOTIFY weatherDescriptionChanged)
		Q_PROPERTY(QString temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
		Q_PROPERTY(QString temperatureFeelLike READ temperatureFeelLike WRITE setTemperatureFeelLike NOTIFY temperatureFeelLikeChanged)
		Q_PROPERTY(QString humidity READ humidity WRITE setHumidity NOTIFY humidityChanged)
		Q_PROPERTY(QString windDirection READ windDirection WRITE setWindDirection NOTIFY windDirectionChanged)
		Q_PROPERTY(QString windSpeed READ windSpeed WRITE setWindSpeed NOTIFY windSpeedChanged)
		Q_PROPERTY(bool active READ active WRITE setActive NOTIFY activeChanged)
		Q_PROPERTY(bool succeeded READ succeeded WRITE setSucceeded  NOTIFY succeededChanged)
		Q_PROPERTY(QString error READ error WRITE setError NOTIFY errorChanged)

	public:
		/**
		 * Constructor of class WeatherDataMgr.
		 * @param pApp:	 the application as the parent object.
		 * @param pRoot: root pane of the qml page.
		 */
		WeatherDataMgr(bb::cascades::Application *pApp, bb::cascades::AbstractPane *pRootPane);

		/**Destructor of this class*/
		virtual ~WeatherDataMgr() { }

		/**
		 * Query the weather live data for a specified city.
		 *
		 * @param strCity: The City whose weather live data will be queried.
		 * @return
		 */
		Q_INVOKABLE void requestWeatherData(const QString& strCity);

		/**
		 * Extract the weather data from the response string in format of XML.
		 * In this method, class bb::data::XmlDataAccess is used to parse the XML string,
		 * and ImageFromWeb is used to load the image from web to the imageView on qml page.
		 *
		 * @param strResponse: The XML response string from which the weather data are extracted.
		 * @return
		 * @see  ImageFromWeb  bb::data::XmlDataAccess
		 */
		void extractWeatherData(const QString& strResponse);

		/**
		 * Reset the values of member variables for weather data and flags.
		 */
		void reset();

		/**
		 * Return the weather description.
		 * @return The weather description as QString
		 */
		QString weatherDescription() const;

		/**
		 * Return the temperature.
		 * @return The temperature as QString
		 */
		QString temperature() const;

		/**
		 * Return the feel-like temperature.
		 * @return The feel-like temperature as QString.
		 */
		QString temperatureFeelLike() const;

		/**
		 * Return the value of humidity.
		 * @return The value of humidity as QString.
		 */
		QString humidity() const;

		/**
		 * Return the wind direction.
		 * @return The wind direction as QString.
		 */
		QString windDirection() const;

		/**
		 * Return the value of the wind speed.
		 * @return The wind speed as QString.
		 */
		QString windSpeed() const;

		/**
		 * Return whether the weather query is running now.
		 * @return True if the weather query is running, false otherwise.
		 */
		bool active() const;

		/**
		 * Return if the last weather query is done successfully.
		 * @return True if the last weather query is done successfully, false otherwise.
		 */
		bool succeeded() const;

		/**
		 * Return the error message for the last weather query.
		 * @return Error message as QString.
		 */
		QString error() const;

		/**
		 * Set weather description and emit signal weatherDescriptionChanged().
		 * @param strWeatherDescription: Value of weather description to be assigned.
		 */
		void setWeatherDescription(const QString& strWeatherDescription);


		/**
		 * Set temperature and emit signal temperatureChanged().
		 * @param strTemperature: Value of temperature to be assigned.
		 */
		void setTemperature(const QString& strTemperature);



		/**
		 * Set the feel-like temperature and emit signal temperatureFeelLikeChanged().
		 * @param strTemperatureFeelLike: Value of feel-like temperature to be assigned.
		 */
		void setTemperatureFeelLike(const QString& strTemperatureFeelLike);

		/**
		 * Set humidity and emit signal humidityChanged().
		 * @param strHumidity: Value of humidity to be assigned.
		 */
		void setHumidity(const QString& strHumidity);

		/**
		 * Set wind direction and emit signal windDirectionChanged().
		 * @param strWindDirection: Value of wind direction to be assigned.
		 */
		void setWindDirection(const QString& strWindDirection);

		/**
		 * Set wind speed and emit signal windSpeedChanged().
		 * @param strWindSpeed: Value of wind speed to be assigned.
		 */
		void setWindSpeed(const QString& strWindSpeed);

		/**
		 * Set flag variable "active" and emit signal activeChanged().
		 * @param bActive: Boolean value indicating if the weather query is running.
		 */
		void setActive(const bool bActive);

		/**
		 * Set flag variable "succeeded" and emit signal succeededChanged().
		 * @param bActive: Boolean value indicating if the last weather query succeeded.
		 */
		void setSucceeded(const bool bSucceeded);


		/**
		 * Set the error message and emit signal errorChanged().
		 * @param strError: Error message string to be assigned.
		 */
		void setError(const QString& strError);


	public Q_SLOTS:
		//public QT slots go here


	Q_SIGNALS:
		/**signal indicating the temperature value is changed.*/
		void temperatureChanged();
		/**signal indicating the weather description value is changed.*/
		void weatherDescriptionChanged();
		/**signal indicating the feel-like temperature value is changed.*/
		void temperatureFeelLikeChanged();
		/**signal indicating the humidity value is changed.*/
		void humidityChanged();
		/**signal indicating the wind direction value is changed.*/
		void windDirectionChanged();
		/**signal indicating the wind speed value is changed.*/
		void windSpeedChanged();
		/**signal indicating the active flag is changed.*/
		void activeChanged();
		/**signal indicating the succeeded flag is changed.*/
		void succeededChanged();
		/**signal indicating the error message is changed.*/
		void errorChanged();



	private slots:
		/**
		 * SLOT method to process the HTTP response for the weather query .
		 */
		void onNetworkReply();


	private:
		/**This http url string is used to query the weather information, provided by website wunderground.*/
		const QString m_strWeatherQueryUrl;
		/**The root pane of the qml page.*/
		bb::cascades::AbstractPane *m_pRootPane;
		/**To perform the http request.*/
		QNetworkAccessManager* m_pNetworkAccessManager;
		/**Store the live weather description.*/
		QString m_strWeatherDescription;
		/**Store the live temperature.*/
		QString m_strTemperature;
		/**Store the live feel-like temperature.*/
		QString m_strTemperatureFeelLike;
		/**Store the live humidity.*/
		QString m_strHumidity;
		/**Store the live wind direction.*/
		QString m_strWindDirection;
		/**Store the live wind speed.*/
		QString m_strWindSpeed;
		/**Flag indicating if the http request and response are still running.*/
		bool m_bActive;
		/**Flag indicating if last http request is successfully finished.*/
		bool m_bSucceeded;
		/**Store the potential error message of the last http request.*/
		QString m_strError;


	};//end of class WeatherDataMgr
};//end of namespace ebf

#endif /* WeatherDataMgr_HPP_ */
