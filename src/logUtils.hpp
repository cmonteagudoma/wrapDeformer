#ifndef WRAPDEFORMER_LOGUTILS_HPP
#define WRAPDEFORMER_LOGUTILS_HPP

#include <maya/MGlobal.h>

#include "alias.hpp"


namespace LogUtils
{

    /** Log the given integer value using Maya displayInfo
     *
     * @param label     custom initial message
     * @param value     value to log
     */
    static void logInt(const str &label, const int &value) {
        char buffer[256];
        sprintf(buffer, "%s %i", label.c_str(), value);
        MGlobal::displayInfo(buffer);
    }

    /** Log the given label using Maya displayInfo
     *
     * @param label     label to log
     */
    static void logStr(const str &label) {
        char buffer[256];
        sprintf(buffer, "%s", label.c_str());
        MGlobal::displayInfo(buffer);
    }


    /** Log the given boolean value using Maya displayInfo
     *
     * @param label     custom initial message
     * @param value     value to log
     */
    static void logBool(const str &label, const bool &value) {
        str boolean = value ? "true" : "false";
        logStr(label + boolean);
    }


    /** Log the given float value using Maya displayInfo
     *
     * @param label     custom initial message
     * @param value     value to log
     */
    static void logFloat(const str &label, const float &value) {
        char buffer[256];
        sprintf(buffer, "%s %f", label.c_str(), value);
        MGlobal::displayInfo(buffer);
    }


    /** Log the given matrix using Maya displayInfo
     *
     * @param label     custom initial message
     * @param m         matrix to log
     */
    static void logMatrix(const str &label, const Matrix &m) {
        logStr(label);
        logStr(std::to_string(m(0,0)) + ", " +
               std::to_string(m(0,1)) + ", " +
               std::to_string(m(0,2)));
        logStr(std::to_string(m(1,0)) + ", " +
               std::to_string(m(1,1)) + ", " +
               std::to_string(m(1,2)));
        logStr(std::to_string(m(2,0)) + ", " +
               std::to_string(m(2,1)) + ", " +
               std::to_string(m(2,2)));
    }
}

#endif //WRAPDEFORMER_LOGUTILS_HPP