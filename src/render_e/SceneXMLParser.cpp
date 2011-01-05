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

int stringToInt(const char *s1) {
    return atoi(s1);
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
                } else {
                    cout << "Unknown shader attribute name "<<attName<<endl;
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
            int width;
            int height;
            string type;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    textureName.append(attValue);
                } else if (stringEqual("file", attName)) {
                    file.append(attValue);
                } else if (stringEqual("type", attName)) {
                    type.append(attValue);
                } else if (stringEqual("width", attName)) {
                    width = stringToInt(attValue);
                } else if (stringEqual("height", attName)) {
                    height = stringToInt(attValue);
                } else {
                    cout << "Unknown texture2d attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            if (file.length()>0){
                cout << "Loading texture "<<(file.c_str())<<endl;
                Texture2D *texture = new Texture2D(file.c_str());
                texture->SetName(textureName);
                TextureLoadStatus status = texture->Load();
                if (status == OK){
                    textures[textureName] = texture;
                } else {
                    cout<<"Error loading texture "<<textureName<<" filename "<<file<<endl;
                }
            } else {
                Texture2D *texture = new Texture2D();
                texture->SetName(textureName);
                TextureFormat textureFormat;
                if (type.compare("DEPTH")){
                    textureFormat = DEPTH;
                } else if (type.compare("RGB")){
                    textureFormat = RGB;
                } else {
                    textureFormat = RGBA;
                }
                texture->Create(width, height, textureFormat);
                textures[textureName] = texture;
            }
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
                } else {
                    cout << "Unknown cubetexture attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            CubeTexture *texture = new CubeTexture(
                    left.c_str(), right.c_str(),
                    top.c_str(), bottom.c_str(),
                    back.c_str(), front.c_str());
            texture->SetName(textureName);
            TextureLoadStatus status = texture->Load();
            if (status == OK){
                textures[textureName] = texture;
            } else {
                cout<<"Error loading cube texture "<<textureName<<" filename "<<left<<endl;
            }
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
                } else {
                    cout << "Unknown attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            
            map<string, Shader*>::iterator iter = shaders.find(shader);
            if (iter == shaders.end()) {
                cout << "Cannot find shader " << shader << endl;
            } else {
                material = new Material(iter->second);
                material->SetName(matName);
                materials[matName] = material;
            }
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
                        cout<<"Set texture parameter "<<iter->second->GetName()<<" value "<<iter->second->GetTextureId()<<endl;
                    }
                } else if (stringEqual("float", attName)) {
                    float f = stringToFloat(attValue);
                    material->SetFloat(parameterName, f);
                } else if (stringEqual("int", attName)) {
                    int i = stringToFloat(attValue);
                    material->SetInt(parameterName, i);
                } else {
                    cout << "Unknown parameter attribute name "<<attName<<endl;
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
            Vector3 scale(1,1,1);
            string parent;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("name", attName)) {
                    objectName.append(attValue);
                } else if (stringEqual("position", attName)) {
                    position = stringToVector3(attValue);
                } else if (stringEqual("rotation", attName)) {
                    rotation = stringToVector3(attValue)*Mathf::DEGREE_TO_RADIAN;
                } else if (stringEqual("scale", attName)) {
                    scale = stringToVector3(attValue);
                } else if (stringEqual("parent", attName)) {
                    parent.append(attValue);
                } else {
                    cout << "Unknown object attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            sceneObject = new SceneObject();
            sceneObject->GetTransform()->SetPosition(position);
            sceneObject->GetTransform()->SetRotation(rotation);
            sceneObject->GetTransform()->SetScale(scale);
            sceneObject->SetName(objectName);
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
            bool projection = true;
            float fieldOfView = 40.0f;
            float aspect = 1.0f;
            float nearPlane = 0.1f;
            float farPlane = 1000.0f;
            float left = -1;
            float right = 1;
            float bottom = -1;
            float top = 1;
            Vector4 clearColor(0,0,0,1);
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));

                if (stringEqual("type", attName)){
                    if (stringEqual("orthographic",attValue)){
                        projection = false;
                    }
                } else if (stringEqual("fieldOfView",attName)){
                    fieldOfView = stringToFloat(attValue);
                } else if (stringEqual("aspect",attName)){
                    aspect = stringToFloat(attValue);
                } else if (stringEqual("nearPlane",attName)){
                    nearPlane = stringToFloat(attValue);
                } else if (stringEqual("farPlane",attName)){
                    farPlane = stringToFloat(attValue);
                } else if (stringEqual("left",attName)){
                    left = stringToFloat(attValue);
                } else if (stringEqual("right",attName)){
                    right = stringToFloat(attValue);
                } else if (stringEqual("bottom",attName)){
                    bottom = stringToFloat(attValue);
                } else if (stringEqual("top",attName)){
                    top = stringToFloat(attValue);
                } else if (stringEqual("nearPlane",attName)){
                    nearPlane = stringToFloat(attValue);
                } else if (stringEqual("farPlane",attName)){
                    farPlane = stringToFloat(attValue);
                } else if (stringEqual("clearColor",attName)){
                    clearColor = stringToVector4(attValue);
                } else {
                    cout << "Unknown camera attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            if (projection){
                cam->SetProjection(fieldOfView, aspect, nearPlane,farPlane);
            } else {
                cam->SetOrthographic(left, right, bottom, top, nearPlane,farPlane);
            }
            cam->SetClearColor(clearColor);
            sceneObject->AddCompnent(cam);
        } else if (stringEqual("material", message)) {
            string ref;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("ref", attName)) {
                    ref.append(attValue);
                } else {
                    cout << "Unknown material attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            if (ref.length()>0){
                map<string, Material*>::iterator iter = materials.find(ref);
                if (iter == materials.end()) {
                    cout << "Cannot find material " << ref << endl;
                } else {
                    sceneObject->AddCompnent(iter->second);
                }
            } else {
                cout << "Warn material ref not set"<<endl;
            }
        } else if (stringEqual("mesh", message)) {
            string meshName;
            string primitive;
            string fbxfile;
            for (int i = 0; i < attributes.getLength(); i++) {
                char *attName = XMLString::transcode(attributes.getName(i));
                char *attValue = XMLString::transcode(attributes.getValue(i));
                if (stringEqual("primitive", attName)) {
                    primitive.append(attValue);
                } else if (stringEqual("fbxfile", attName)) {
                    fbxfile.append(attValue);
                } else {
                    cout << "Unknown attribute name "<<attName<<endl;
                }
                XMLString::release(&attValue);
                XMLString::release(&attName);
            }
            Mesh *mesh = NULL;
            if (primitive.length() > 0){
                if (stringEqual("cube", primitive.c_str())){
                    mesh = MeshFactory::CreateCube();
                } else if (stringEqual("sphere", primitive.c_str())){
                    mesh = MeshFactory::CreateICOSphere();
                } else if (stringEqual("tetrahedron", primitive.c_str())){
                    mesh = MeshFactory::CreateTetrahedron();
                } else if (stringEqual("plane", primitive.c_str())){
                    mesh = MeshFactory::CreatePlane();
                } else {
                    cout << "Unknown mesh.primitive name "<<primitive.c_str()<<endl;
                }
            } else if (fbxfile.length() > 0){
                cout << "Todo : implement fbx import"<<endl;
            }
            if (mesh != NULL){
                MeshComponent *meshComponent = new MeshComponent();
                meshComponent->SetMesh(mesh);
                sceneObject->AddCompnent(meshComponent);
            }
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
                    light->SetAmbient(stringToVector4(attValue));
                } else if (stringEqual("diffuse", attName)) {
                    light->SetDiffuse(stringToVector4(attValue));
                } else if (stringEqual("specular", attName)) {
                    light->SetSpecular(stringToVector4(attValue));
                } else if (stringEqual("type", attName)) {
                    if (stringEqual("point", attValue)){
                        light->SetLightType(PointLight);
                    } else {
                        cout << "Unknown lighttype "<<attValue << endl;
                    }
                } else if (stringEqual("constantAttenuation", attName)) {
                    light->SetConstantAttenuation(stringToFloat(attValue));
                } else if (stringEqual("linearAttenuation", attName)) {
                    light->SetLinearAttenuation(stringToFloat(attValue));
                } else if (stringEqual("quadraticAttenuation", attName)) {
                    light->SetQuadraticAttenuation(stringToFloat(attValue));
                } else {
                    cout << "Unknown light attribute name "<<attName<<endl;
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
    cout<<"Loading scene "<<filename<<endl;
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

