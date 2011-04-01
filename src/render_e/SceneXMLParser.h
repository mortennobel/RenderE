/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
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

