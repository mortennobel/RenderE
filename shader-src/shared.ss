#version 120
// Provides shared shader functions that can be used in both vertex shaders and fragment shaders

void testCall(inout vec4 color){
    color = vec4(0,1,1,1);
}
