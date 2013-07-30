/**
 * @file ImageFromWeb.hpp
 * @author Xiaodong Zhang
 * @version 1.0
 *
 * After the query of weather data, we get the URL of the weather image from the http response.
 * This image from this URL should be displayed on qml page. Unfortunately, qml page of BB10
 * cascades framework does not support the image with a http URL source. Therefore, I write this
 * class as a workaround.
 * This class make the http request for this image, read the response as a stream of bytes, create
 * an image with these bytes and assign this image to the imageView control of the qml page.
 *
 */

#ifndef IMAGEFROMWEB_HPP_
#define IMAGEFROMWEB_HPP_

#include <QObject>
#include <QtCore/QString>
#include <QtNetwork/QtNetwork>
#include <bb/cascades/ImageView>
#include <bb/cascades/Image>

namespace ebf
{
	/*!
	 * @brief This class operate on the image with a http URL .
	 */
	class ImageFromWeb : public QObject
	{
		Q_OBJECT
	public:
		/**
		 * Constructor of this class.
		 * @param pParent: parent of this object.
		 */
		ImageFromWeb(QObject *pParent);

		/**
		 * Destructor of this class.
		 */
		virtual ~ImageFromWeb();

		/**
		 * Request the image via http URL, and the response will be processed in method onNetworkReply().
		 *
		 * @param pImageView: The imageView control on the qml page.
		 * @param strImageUrl: URL of the image to be requested.
		 * @param pNetworkAccessManager: NetworkAccessManager to do the http request.
		 * @return true if there is no error, false otherwise.
		 * @see ImageFromWeb::onNetworkReply()
		 */
		bool loadImageToImageView(bb::cascades::ImageView* pImageView, const QString& strImageUrl,
				QNetworkAccessManager* pNetworkAccessManager);

	public Q_SLOTS:
		/**
		 * SLOT method to process the HTTP response for the weather image request.
		 *
		 * @see ImageFromWeb::loadImageToImageView()
		 */
		void onNetworkReply();


	private:
		/**Store the pointer of the imageView control from qml page.*/
		bb::cascades::ImageView* m_pImageView;

	};//end of class ImageFromWeb
};//end of namespace ebf

#endif /* IMAGEFROMWEB_HPP_ */




