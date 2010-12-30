/* 
 * File:   SceneXMLParser.h
 * Author: morten
 *
 * Created on December 28, 2010, 9:50 PM
 */

#ifndef SCENEXMLPARSER_H
#define	SCENEXMLPARSER_H

#include "SceneObject.h"

namespace render_e {

// forward declaration
class RenderBase;

class SceneXMLParser {
public:
    SceneXMLParser();
    
    virtual ~SceneXMLParser();
    
    void LoadScene(const char* filename, RenderBase *renderBase);
private:
    SceneXMLParser(const SceneXMLParser& orig); // not allowed (no implementation)
};

}

#endif	/* SCENEXMLPARSER_H */

