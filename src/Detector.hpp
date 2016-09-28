//
// Created by jimmy on 21-9-16.
//

#ifndef ROBOTALGORITHM_DETECTOR_HPP
#define ROBOTALGORITHM_DETECTOR_HPP

#include <math.h>
#include <string>
#include <opencv2/imgproc/imgproc.hpp>


class Detector {
public:
    Detector(const std::string shape, const std::string color);
    /**
     *
     * @param img The image where the shapes are to be found.
     * @param shape The shape to find. This must be of sort: "circel”,”halve circel”,”vierkant”,”rechthoek” or ”driehoek”
     * @param color The color of the shape to find. This must be either "rood", "groen", "blauw", "geel", "zwart" or "wit.
     * @return The shapes that were found.
     */
    std::vector<std::vector<cv::Point> > findShapes(cv::Mat& img);

    /**
     * Gets the x and y coordinates of a shape(contour)
     * @param contour The contour/shape to get the x/y coordinate from.
     * @return A pair with two ints aka the x and y coordinates.
     */
    std::pair<double, double> getCenter(std::vector<cv::Point>& contour);

    /**
     * Gets the surface of contour/shape.
     * @param contour The contour/shape to get the surface from.
     * @return The surface.
     */
    double getSurface(std::vector<cv::Point>& contour);

    cv::Mat getFilteredImg(cv::Mat& img);

    ~Detector();

protected:


private:

    void findRect(cv::Mat& img);
    void findCircle(cv::Mat& img);
    void findSquare(cv::Mat& img);
    void findTriangle(cv::Mat& img);
    /**
     * Sets a label at the center of a shape/contour
     * @param im The image to draw/write the label on.
     * @param label What will be written.
     * @param contour The contour/shape to write position the label at.
     */
    void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour);
    /**
     *
     * Helper function to find a cosine of angle between vectors
     * from pt0->pt1 and pt0->pt2
     */
    double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0);
    /**
     * Gets the min and the max range of a color for finding a color.
     * @param color The color to get the range from.
     * @return The min and max range of a color.
     */
    std::pair<cv::Scalar, cv::Scalar> getColorRange(std::string color);
    /**
     * Sets the min and max color of the detector.
     * @param color The color to set the min and max range from.
     */
    void setMinAndMaxColor(const std::string color);
    std::string shape;
    std::string color;
    cv::Scalar minColor;
    cv::Scalar maxColor;

};


#endif //ROBOTALGORITHM_DETECTOR_HPP
