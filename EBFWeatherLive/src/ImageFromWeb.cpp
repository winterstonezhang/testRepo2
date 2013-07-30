/**
 * @file ImageFromWeb.cpp
 * @author Xiaodong Zhang
 * @version 1.0
 *
 * After the query of weather data, we get the URL of the weather image from the http response.
 * This image from this URL should be displayed on qml page. Unfortunately, qml page of BB10
 * cascades framework does not support the image with a http URL source. Therefore, I write this
 * class as a workaround.
 * This class make the http request for this image, read the response as a stream of bytes, create
 * an image with these bytes and assign this image to the imageView control of the qml page.
 */

#include "ImageFromWeb.hpp"

using namespace bb::cascades;
using namespace ebf;


/**
 * Constructor of this class.
 *
 * @param pParent: parent of this object.
 */
ImageFromWeb::ImageFromWeb(QObject *pParent): QObject(pParent), m_pImageView(NULL)
{
}

/**
 * Destructor of this class.
 */
ImageFromWeb::~ImageFromWeb()
{
}


/**
 * Request the image via http URL, and the response will be processed in method onNetworkReply().
 *
 * @param pImageView: The imageView control on the qml page.
 * @param strImageUrl: URL of the image to be requested.
 * @param pNetworkAccessManager: NetworkAccessManager to do the http request.
 * @return true if there is no error, false otherwise.
 * @see ImageFromWeb::onNetworkReply()
 */
bool ImageFromWeb::loadImageToImageView(ImageView* pImageView, const QString& strImageUrl, QNetworkAccessManager* pNetworkAccessManager)
{

	if (pNetworkAccessManager) {
	    QUrl url(strImageUrl);
	    //validate the URL
		if (!url.isValid()) {
			return false;
		}
		//construct a request object using this url
	    QNetworkRequest networkRequest(url);
	    //perform the http request of the weather image
	    QNetworkReply* networkReply = pNetworkAccessManager->get(networkRequest);
	    //method onNetworkReply() will process the http response.
	    connect(networkReply, SIGNAL(finished()), this, SLOT(onNetworkReply()));
	    //store the pointer of the imageView control, so that it can be set with the created image in method onNetworkReply().
	    m_pImageView = pImageView;
	}

	return true;

}


/**
 * SLOT method to process the HTTP response for the weather image request.
 *
 * @see ImageFromWeb::loadImageToImageView()
 */
void ImageFromWeb::onNetworkReply()
{
	//Find out the object of QNetworkReply which send the SIGNAL
    QNetworkReply* pNetworkReply = qobject_cast<QNetworkReply*>(sender());
    if (pNetworkReply) {
        if (pNetworkReply->error() == QNetworkReply::NoError) {//if the reply is correct
            const int iAvailable = pNetworkReply->bytesAvailable();
            if (iAvailable > 0) {
            	//read the reply as bytes
                const QByteArray buffer(pNetworkReply->readAll());
                //create a image object from these bytes.
                Image image(buffer);
                //set the image to the imageView control, so that it is displayed on qml page.
                if(m_pImageView)
                	m_pImageView->setImage(image);
            }
        } else {
            //TODO set the m_pImageView to a picture indicating an error.
        }

        //The object will be deleted when control returns to the event loop.
        pNetworkReply->deleteLater();
    }

}


