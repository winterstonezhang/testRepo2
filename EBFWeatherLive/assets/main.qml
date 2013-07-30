/**
 * @file main.qml
 * @author Xiaodong Zhang
 * @version 1.0
 *
 * This qml file renders a page where the user can select a city 
 * and query the current weather information. 
 * In this qml page, the values of the most controls are bound
 * to the fields of weatherDataMgr object which is instantiated
 * in main.cpp.
 *
 */

import bb.cascades 1.0

Page {

	//container for the whole page
	Container {
	    //use this image as the background of this qml page
	    ImageView {
	        horizontalAlignment: HorizontalAlignment.Center
	        verticalAlignment: VerticalAlignment.Center      
            imageSource: "asset:///images/blue_sky_4EBF.jpg"
	    }
	    layout: DockLayout {	    
	    }
	
		//----------Container containning the weather querying controls and the result of the query.
	    Container {
	        leftPadding: 10
	        rightPadding: 10
	
	        Label {
	            id: titleLabel
	            text: "EBF Weather Live"
	            textStyle {
	                color: Color.Black
	                fontSizeValue: 15
	            }
	            horizontalAlignment: HorizontalAlignment.Center
	        }
	        
	        //---------------Container with the dropdown and "refrsh" button
	        Container { 
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }

				//Add some of the cities of Germany in this DropDown control.
				//You can later add more city names to it.
				DropDown {
	                id: cityDropDown
	                enabled: ! weatherDataMgr.active
	                title: "Germany City:"
	
				    Option {
				        text: "Berlin"
				        value: "Berlin"
				    }
					Option {
					    text: "Bochum"
					    value: "Bochum"
					}
					
	                Option {
	                    text: "Duesseldorf"
	                    value: "Duesseldorf"
	                }
                    
                    Option {
                        text: "Dresden"
                        value: "Dresden"
                    }
	                
                    Option {
                        text: "Frankfurt"
                        value: "Frankfurt"
                    }
                    Option {
                        text: "Hamburg"
                        value: "Hamburg"	                   
                    }
	                Option {
	                    text: "Koeln"
	                    value: "Cologne "	                   
	                }
                    Option {
                        text: "Muenchen"
                        value: "Munich"	                   
                    }

					//If user changes the selection of the city, weatherDataMgr object will 
					//be called to query the weather for the selected city.
	                onSelectedIndexChanged: {
	                    weatherDataMgr.requestWeatherData(cityDropDown.selectedValue);
                        dateTimeLabel.setCurrentDateTime();
	                }

	            }

	            //Press this button to retrieve the current weather data if the city selection
	            //is not changed. 
	            Button {
	                id: refreshButton
	                horizontalAlignment: HorizontalAlignment.Center
    				text: "Refresh"
	                enabled: !weatherDataMgr.active
	
	                onClicked: {
	                    //weatherService.requestWeatherInformation(cityDropDown.selectedValue);
	                    weatherDataMgr.requestWeatherData(cityDropDown.selectedValue);
                        dateTimeLabel.setCurrentDateTime();
	                }
                }//end of button "refreshButton"
	        } //end of container
	               
	
			
	        //--------------------Container to show the activity indicator when the 
	        //weatherDataMgr is just working to query the weather data.
	        Container {
	            id: activityIndicatorContainer
	            horizontalAlignment: HorizontalAlignment.Center
	            property alias active: activityIndicator.running
				//This container is shown when the acitvity indicator is running
	            visible: weatherDataMgr.active
	
	            layout: DockLayout {
	            }
	
	            ActivityIndicator {
	                id: activityIndicator
	                //This indicator will be running only when the weatherDataMgr is doing the weather query.
	                running: weatherDataMgr.active
	                horizontalAlignment: HorizontalAlignment.Center
	                verticalAlignment: VerticalAlignment.Center
	                preferredHeight: 300
	                preferredWidth: 500
	            }
	        }

	        //----------------Container to show the live weather data and the weather icon
	        Container {
	            id: weatherDataAndIconContainer
	            layout: StackLayout {
	                orientation: LayoutOrientation.LeftToRight
	            }
	            visible: !weatherDataMgr.active &&  weatherDataMgr.succeeded
	            topMargin: 10.0
	            topPadding: 20.0
	            
	            Container {
	                id: weatherDataContainer
	                horizontalAlignment: HorizontalAlignment.Left
	                topMargin: 100
	                topPadding: 20
	                leftPadding: 20
	                rightPadding: 20
	                //This container is visible only when weatherDataMgr is not working
	                //and the last request succeeded.
	                visible: !weatherDataMgr.active && weatherDataMgr.succeeded
	
	                layoutProperties: StackLayoutProperties {
	                    spaceQuota: 4.0
	
	                }
	                //label to show the local date and time of the smartphone.
                    Label {
                        id: dateTimeLabel
                        text: Qt.formatDateTime(new Date(), "hh:mm  MMM. dd  yyyy")
                        textStyle.fontWeight: FontWeight.Default
                        textStyle.fontSizeValue: 2.5
                        textFormat: TextFormat.Auto
                        textStyle.color: Color.DarkGreen
                        
                        //Javascript function to set the this label to the current local date and time.
                        function setCurrentDateTime() {
                            text = Qt.formatDateTime(new Date(), "hh:mm MMM. dd  yyyy");
                        }
                    }
                    
                    //Label to show the weather description
	                Label {
	                    id: weatherDescriptionLabel
	                    text: weatherDataMgr.weatherDescription
	                    textStyle.fontWeight: FontWeight.Bold
	                    textStyle.fontSizeValue: 2.5
	                }
	                
                    //Label to show the temperature
	                Label {
	                    id: temperatureLabel
	                    text: weatherDataMgr.temperature+"°C"
	                    textStyle.fontWeight: FontWeight.Bold
	                }
	                
                    //Label to show the feel-like temperature
	                Label {
	                    id: temperatureFeelLikeLabel
                        text: "Feel Like: "+ weatherDataMgr.temperatureFeelLike+"°C"
	                }
	                
                    //Label to show the humidity
	                Label {
	                    id: humidityLabel
	                    text: "Humidity: "+ weatherDataMgr.humidity
	                }
	                
                    //Label to show the wind direction
	                Label {
	                    id: windDirectionLabel
	                    text: "Wind Dire.: "+ weatherDataMgr.windDirection
	                }
	                
                    //Label to show the wind speed
	                Label {
	                    id: windSpeedLabel
	                    text: "Wind Speed: "+ weatherDataMgr.windSpeed+"kmh"
	                }
	                
	             }
	            
	            //Container to show the weather icon
	            Container {
	                id : weatherIconContainer
	                layoutProperties: StackLayoutProperties {
	                    spaceQuota: 2.0
	
	                }
	                topMargin: 20.0
	                
	                //Show the image downloaded from the web. The image is set in Qt C++ class ImageFromWeb.
	                ImageView {
	                    id: weatherIconImageView
	                    objectName: "weatherIconImageView"
	                    loadEffect: ImageViewLoadEffect.DefaultDeferred
	                    topMargin: 10.0
	                    minWidth: 150.0
	                    minHeight: 150.0
	                    //verticalAlignment: VerticalAlignment.Top
	                    horizontalAlignment: HorizontalAlignment.Left
	                    leftMargin: 10.0
	                }
                }//end of container "weatherIconContainer"
	           
            }//end of container "weatherDataAndIconContainer"
	

	        //-----------------Container to show error message.
	        Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
	            id: errorMsgContainer
	            horizontalAlignment: HorizontalAlignment.Center
	            topMargin: 100
	            //This container is visible only when weatherDataMgr is not requesting the live weather data,
	            //and the last request did not succeed.
				visible: true //!weatherDataMgr.active && ! weatherDataMgr.succeeded

				//Show the error message in this text area
	            TextArea {
	                id: errorMsgTextArea
	                editable: false
	                //backgroundVisible: false
	                text: weatherDataMgr.error 
	                textStyle {
	                    base: SystemDefaults.TextStyles.BigText
	                    color: Color.Red
	                    textAlign: TextAlign.Center
	                }
                }//end of errorMsgTextArea
            }//end of errorMsgContainer
	    }

	    attachedObjects: [
	    	//No attatched object neccesary for this qml. 
	    	//Objected weatherDataMgr is exposed to this qml in main.cpp.
	    ]
	    
//		//TODO 
//	    //At the beginning, there is no error, so we make the errorMsgContainer unvisible.
//	    onCreationCompleted: {
//	       errorMsgContainer.visible = false;
//	    }
	
	}

}
