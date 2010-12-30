/* 
 * File:   SceneXMLParser.cpp
 * Author: morten
 * 
 * Created on December 28, 2010, 9:50 PM
 */

#include "SceneXMLParser.h"

#include <iostream>
#include <stack>
#include <map>

// Mandatory for using any feature of Xerces.
#include <xercesc/util/PlatformUtils.hpp>

// DOM (if you want SAX, then that's a different include)
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/sax/HandlerBase.hpp>

#include "math/Vector3.h"
#include "math/Mathf.h"
#include "shaders/ShaderFileDataSource.h"
#include "textures/Texture2D.h"
#include "textures/CubeTexture.h"
#include "Material.h"
#include "Camera.h"
#include "FBXLoader.h"
#include "MeshFactory.h"
#include "Light.h"
#include "RenderBase.h"

// define xerces namespace
XERCES_CPP_NAMESPACE_USE
        using namespace std;


namespace render_e {

// Helper functions

bool stringEqual(const char *s1, const char *s2) {
    return strcmp(s1, s2) == 0;
}

float stringToFloat(const char *s1) {
    return (float) atof(s1);
}

Vector3 stringToVector3(char *s1) {
    Vector3 f;
    char * pch;
    int index = 0;
    pch = strtok(s1, ",");
    while (pch != NULL && index < 3) {
        f[index] = (float) atof(pch);
        index++;
        pch = strtok(NULL, ",");
    }

    return f;
}

Vector4 stringToVector4(char *s1) {
    Vector4 f;
    char * pch;
    int index = 0;
    pch = strtok(s1, ",");
    while (pch != NULL && index < 4) {
        f[index] = (float) atof(pch);
        index++;
        pch = strtok(NULL, ",");
    }

    return f;
}

Vector2 stringToVector2(char *s1) {
    Vector2 f;
    char * pch;
    int index = 0;
    pch = strtok(s1, ",");
    while (pch != NULL && index < 2) {
        f[index] = (float) atof(pch);
        index++;
        pch = strtok(NULL, ",");
    }
 
    return f;
}

enum MyParserState {
    SCENE,
    SHADERS,
    TEXTURES,
    MATERIALS,
    SCENEOBJECTS,
    SCENEOBJECT,
    COMPONENT
};

// internal helper classes

class MySAXHandler : public HandlerBase {
public:

    MySAXHandler(RenderBase *renderBase) : renderBase(renderBase), sceneObject(NULL) {
    }
    
    void error(char *tagName){
        cout<<"Unknown tag "<<tagName<<" state "<<state.top()<<endl;
    }

    void parseScene(const XMLCh * const name, AttributeList& attributes, char* message) {
        if (stringEqual("shaders", message)) {
            state.push(SHADERS);
        } else if (stringEqual("materials", message)) {
            state.push(MATERIALS);
        } else if (stringEqual("textures", message)) {
            state.push(TEXTURES);
        } else if (stringEqual("scenegraph", message)) {
            state.push(SCENEOBJECTS);
        } else {
            error(message);
        }
        
    }

    void parseShaders(const XMLCh * const name, AttributeList& attributes, char* message) {
        if (stringEqual("shader", message)) {
            string shaderName;
            string file;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    shaderName.append(attValue);
                } else if (stringEqual("file", attName)) {
                    file.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            ShaderLoadStatus status;
            Shader *shader = shaderLoader.LoadLinkShader(file.c_str(), status);
            if (status==SHADER_OK){
                shader->SetName(shaderName);
                shaders[shaderName] = shader;
                cout << "Loaded shader "<<shaderName<<endl;
            } else {
                cout << "Cannot load shader "<<file<<endl;
            }
        } else {
            error(message);
        }
    }

    void parseTextures(const XMLCh * const name, AttributeList& attributes, char* message) {
        if (stringEqual("texture2d", message)) {
            string textureName;
            string file;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    textureName.append(attValue);
                } else if (stringEqual("file", attName)) {
                    file.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            Texture2D *texture = new Texture2D(file.c_str());
            texture->SetName(textureName);
            textures[textureName] = texture;
        } else if (stringEqual("cubetexture", message)) {
            string textureName;
            string left, right, top, bottom, back, front;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    textureName.append(attValue);
                } else if (stringEqual("left", attName)) {
                    left.append(attValue);
                } else if (stringEqual("right", attName)) {
                    right.append(attValue);
                } else if (stringEqual("top", attName)) {
                    top.append(attValue);
                } else if (stringEqual("bottom", attName)) {
                    bottom.append(attValue);
                } else if (stringEqual("back", attName)) {
                    back.append(attValue);
                } else if (stringEqual("front", attName)) {
                    front.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            CubeTexture *texture = new CubeTexture(
                    left.c_str(), right.c_str(),
                    top.c_str(), bottom.c_str(),
                    back.c_str(), front.c_str());
            texture->SetName(textureName);
            textures[textureName] = texture;
        } else {
            error(message);
        }
    }

    void parseMaterials(const XMLCh * const name, AttributeList& attributes, char* message) {
        static Material *material = NULL;
        if (stringEqual("material", message)) {
            string matName;
            string shader;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    matName.append(attValue);
                } else if (stringEqual("shader", attName)) {
                    shader.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            Shader *shaderObj = shaders[shader];
            if (shaderObj == NULL) {
                cerr << "Shader " << shader << " not found" << endl;
            }
            material = new Material(shaderObj);
            
            materials[matName] = material;
        } else if (stringEqual("parameter", message)) {
            assert(material != NULL);
            string parameterName;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    parameterName.append(attValue);
                } else if (stringEqual("vector2", attName)) {
                    material->SetVector2(parameterName, stringToVector2(attValue));
                } else if (stringEqual("vector3", attName)) {
                    material->SetVector3(parameterName, stringToVector3(attValue));
                } else if (stringEqual("vector4", attName)) {
                    material->SetVector4(parameterName, stringToVector4(attValue));
                } else if (stringEqual("texture", attName)) {
                    map<string, TextureBase*>::iterator iter = textures.find(attValue);
                    if (iter == textures.end()) {
                        cout << "Cannot find texture " << attValue << endl;
                    } else {
                        material->SetTexture(parameterName, iter->second);
                    }
                } else if (stringEqual("float", attName)) {
                    float f = stringToFloat(attValue);
                    material->SetFloat(parameterName, f);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
        } else {
            error(message);
        }
    }

    void parseSceneObjects(const XMLCh * const name, AttributeList& attributes, char* message) {
        if (stringEqual("object", message)) {
            string objectName;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
            string parent;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    objectName.append(attValue);
                } else if (stringEqual("position", attName)) {
                    position = stringToVector3(attValue);
                } else if (stringEqual("rotation", attName)) {
                    rotation = stringToVector3(attValue);
                } else if (stringEqual("scale", attName)) {
                    scale = stringToVector3(attValue);
                } else if (stringEqual("parent", attName)) {
                    parent.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            sceneObject = new SceneObject();
            sceneObject->GetTransform().SetPosition(position);
            sceneObject->GetTransform().SetRotation(rotation);
            sceneObject->GetTransform().SetScale(scale);
            if (objectName.length() > 0 && parent.length() > 0){
                parentMap[objectName] = parent;
            }
        } else {
            error(message);
        }
    }
    
    void parseComponents(const XMLCh * const name, AttributeList& attributes, char* message) {
        if (stringEqual("camera", message)) {
            Camera *cam = new Camera();
            cout << "Todo setup camera"<<endl;
            sceneObject->AddCompnent(cam);
        /*} else if (stringEqual("mesh", message)) {
            string meshName;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
            string material;
            string fbxfile;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    meshName.append(attValue);
                } else if (stringEqual("position", attName)) {
                    position = stringToVector3(attValue);
                } else if (stringEqual("rotation", attName)) {
                    rotation = stringToVector3(attValue);
                } else if (stringEqual("scale", attName)) {
                    scale = stringToVector3(attValue);
                } else if (stringEqual("material", attName)) {
                    material.append(attValue);
                } else if (stringEqual("fbxfile", attName)) {
                    fbxfile.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            SceneObject *sceneObject = fbxLoader.Load(fbxfile.c_str());
            if (sceneObject ==NULL){
                cout <<"Cannot load "<<fbxfile<<endl;
                return;
            }
            
            position = position+sceneObject->GetTransform().GetPosition();
            sceneObject->GetTransform().SetPosition(position);
            
            if (scale != Vector3::Zero()){
                scale = scale*sceneObject->GetTransform().GetScale();
                sceneObject->GetTransform().SetScale(scale);
            }
            
            if (rotation != Vector3::Zero()){
                Quaternion rotation = Quaternion::MakeFromEuler(rotation.x*Mathf::DEGREE_TO_RADIAN, rotation.y*Mathf::DEGREE_TO_RADIAN, rotation.z*Mathf::DEGREE_TO_RADIAN);
                rotation = rotation * sceneObject->GetTransform().GetRotation();
                sceneObject->GetTransform().SetRotation(rotation);
            }
            
            renderBase->AddSceneObject(sceneObject);
            
        } else if (stringEqual("cube", message)) {
            string meshName;
            Vector3 position;
            Vector3 rotation;
            Vector3 scale;
            string material;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    meshName.append(attValue);
                } else if (stringEqual("position", attName)) {
                    position = stringToVector3(attValue);
                } else if (stringEqual("rotation", attName)) {
                    rotation = stringToVector3(attValue);
                } else if (stringEqual("scale", attName)) {
                    scale = stringToVector3(attValue);
                } else if (stringEqual("material", attName)) {
                    material.append(attValue);
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            Mesh *mesh = MeshFactory::CreateCube();
            SceneObject *cubeObject = new SceneObject();
            MeshComponent *meshComponent = new MeshComponent();
            meshComponent->SetMesh(mesh);
            cubeObject->AddCompnent(meshComponent);
            
            position = position+cubeObject->GetTransform().GetPosition();
            cubeObject->GetTransform().SetPosition(position);
            
            if (scale != Vector3::Zero()){
                scale = scale*cubeObject->GetTransform().GetScale();
                cubeObject->GetTransform().SetScale(scale);
            }
            
            if (rotation != Vector3::Zero()){
                Quaternion rotation = Quaternion::MakeFromEuler(rotation.x*Mathf::DEGREE_TO_RADIAN, rotation.y*Mathf::DEGREE_TO_RADIAN, rotation.z*Mathf::DEGREE_TO_RADIAN);
                rotation = rotation * cubeObject->GetTransform().GetRotation();
                cubeObject->GetTransform().SetRotation(rotation);
            }
            
            renderBase->AddSceneObject(cubeObject);
            */
        } else if (stringEqual("light", message)){
            string lightName;
            Light *light = new Light();
            
            string lightType;
            
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    lightName.append(attValue);
                } else if (stringEqual("type", attName)) {
                    lightType.append(attValue);
                } else if (stringEqual("ambient", attName)) {
                    light->SetAmbient(stringToVector3(attValue));
                } else if (stringEqual("diffuse", attName)) {
                    light->SetDiffuse(stringToVector3(attValue));
                } else if (stringEqual("specular", attName)) {
                    light->SetSpecular(stringToVector3(attValue));
                } else if (stringEqual("type", attName)) {
                    if (stringEqual("point", attValue)){
                        light->SetLightType(PointLight);
                    } else {
                        cout << "Unknown lighttype "<<attValue << endl;
                    }
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            
            sceneObject->AddCompnent(light);
        } else {
            error(message);
        }
    }

    void endElement(const XMLCh * const name) {
        assert(!state.empty());
        MyParserState prevState = state.top();
        state.pop();
        if (prevState == SCENEOBJECT){
            renderBase->AddSceneObject(sceneObject);
        }
    }

    void startElement(const XMLCh * const name, AttributeList& attributes) {
        
        char* message = XMLString::transcode(name);
        
        if (state.empty()) {
            state.push(SCENE);
        } else {
            cout<<state.top()<<endl;
            switch (state.top()) {
                case SCENE:
                    parseScene(name, attributes, message);
                    break;
                case SHADERS:
                    parseShaders(name, attributes, message);
                    state.push(SHADERS); // push same value to stack
                    break;
                case TEXTURES:
                    parseTextures(name, attributes, message);
                    state.push(TEXTURES); // push same value to stack
                    break;
                case MATERIALS:
                    parseMaterials(name, attributes, message);
                    state.push(MATERIALS); // push same value to stack
                    break;
                case SCENEOBJECTS:
                    parseSceneObjects(name, attributes, message);
                    state.push(SCENEOBJECT); // push same value to stack
                    break;
                case SCENEOBJECT:
                    parseComponents(name, attributes, message);
                    state.push(COMPONENT); // push same value to stack
                    break;
            }
        }

        XMLString::release(&message);
    }

    void fatalError(const SAXParseException& exception) {
        char* message = XMLString::transcode(exception.getMessage());
        cout << "Fatal Error: " << message
                << " at line: " << exception.getLineNumber()
                << endl;
        XMLString::release(&message);
    }

    SceneObject *sceneObject;
    RenderBase *renderBase;
    stack<MyParserState> state;

    FBXLoader fbxLoader;
    ShaderFileDataSource shaderLoader;
    map<string, Shader*> shaders;
    map<string, TextureBase*> textures;
    map<string, Material*> materials;
    map<string, string> parentMap;
};

SceneXMLParser::SceneXMLParser() {
    try {
        XMLPlatformUtils::Initialize();
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Error during initialization! :\n"
                << message << "\n";
        XMLString::release(&message);
        // Do your failure processing here
        return;
    }
}

SceneXMLParser::~SceneXMLParser() {
    XMLPlatformUtils::Terminate();
}

void SceneXMLParser::LoadScene(const char* filename, RenderBase *renderBase) {
    SAXParser* parser = new SAXParser();
    parser->setDoNamespaces(true); // optional

    MySAXHandler* docHandler = new MySAXHandler(renderBase);
    ErrorHandler* errHandler = (ErrorHandler*) docHandler;
    parser->setDocumentHandler(docHandler);
    parser->setErrorHandler(errHandler);

    try {
        parser->parse(filename);
    } catch (const XMLException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return;
    } catch (const SAXParseException& toCatch) {
        char* message = XMLString::transcode(toCatch.getMessage());
        cout << "Exception message is: \n"
                << message << "\n";
        XMLString::release(&message);
        return;
    } catch (...) {
        cout << "Unexpected Exception \n";
        return;
    }
    delete parser;
    delete docHandler;
}
}

