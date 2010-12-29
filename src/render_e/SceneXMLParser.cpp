/* 
 * File:   SceneXMLParser.cpp
 * Author: morten
 * 
 * Created on December 28, 2010, 9:50 PM
 */

#include "SceneXMLParser.h"

#include <iostream>
#include <xercesc/util/PlatformUtils.hpp>

using namespace xercesc;

namespace render_e {

SceneXMLParser::SceneXMLParser() {
    using namespace std;
    cout << "XML parser test " << endl;
    try {
        XMLPlatformUtils::Initialize();
    }    catch (const XMLException& toCatch) {
        cout << "XML init exception " << endl;
        // Do your failure processing here
        return;
    }
    cout << "XML init :D " << endl;
    // Do your actual work with Xerces-C++ here.

    XMLPlatformUtils::Terminate();
    cout << "XML Terminated " << endl;
}

SceneXMLParser::SceneXMLParser(const SceneXMLParser& orig) {
}

SceneXMLParser::~SceneXMLParser() {
}

}

