#include "plane_seg/ImageProcessor.hpp"
#include <opencv2/highgui.hpp>

namespace planeseg {

ImageProcessor::ImageProcessor(){
}

ImageProcessor::~ImageProcessor(){}

void ImageProcessor::process(){
    displayImage(original_img_, "original");
    std::cout << "Press 's' to save, 'e' to erode, anything else to close" << std::endl;
    int l = cv::waitKey(0);
    if (l == 's'){
        saveImage(original_img_);
    }
    else if (l == 'e'){
        erodeImage(original_img_);
        displayImage(erode_img_, "erode");
        std::cout << "Press 's' to save both images, original then eroded" << std::endl;
        int k = cv::waitKey(0);
        if (k == 's'){
            saveImage(original_img_);
            saveImage(erode_img_);
        }
    }
}


void ImageProcessor::displayImage(cv_bridge::CvImage image, std::string process){
    cv::namedWindow(process, cv::WINDOW_AUTOSIZE);
    cv::imshow(process, image.image);
}

void ImageProcessor::saveImage(cv_bridge::CvImage image_){
    std::string imagename;
    std::cout << "Enter filename to save image (don't forget .png!): " << std::endl;
    std::cin >> imagename;
    cv::imwrite("/home/christos/rosbags/" + imagename, image_.image);
}

void ImageProcessor::erodeImage(cv_bridge::CvImage originalImage){

    int erode_size = 10;
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                                cv::Size(2*erode_size + 1, 2*erode_size + 1),
                                                cv::Point(erode_size, erode_size)
                                                );
    cv::erode(originalImage.image, erode_img_.image, element);
}

} //namespace planeseg
