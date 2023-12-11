# Feature: Editor and Library (OpenGL)

## Process:

### Project Setup: Premake

> Simple system cycle using GLFW
> namespaces Core, GL\_Graphics

### Namespace: Core

* Core
    1. Globals
        * Driver specification (potentially other lib e.g vulkan)
        * File path validations (Func)
        * OpenGL error detection / handling
    2. class GL_Core
        1. Manages Lifecycle of libary playground for editor to tap into
        2. Holds pointer to subsystems.
        3. GLFW window api (callbacks triggers)
        4. Input (Key, Mouse)
        5. Shader Files
    3. Input
        * Key, Mouse inputs, (callbacks receivers)
    4. Event (Isingleton)
        * CallBacks Management
```cpp
// Uses
template<typename ... Args>
std::function<void(Args...)>
```


### Namespace GL\_Graphics
#### Buffer
* Buffer Data storage, OpenGL Vertex Array / Buffer Creation APIs.
#### Model 
* Generic Base models [-1.0f,1.0f] e.g Point, Line, Quad, Circle


# Feature: Buffer Layout Element Specialization for Different Types

* Vec2, Vec3, Vec4, Mat3, Mat4, float, int, unsigned short

## Implementation

* Template specialize member function that reassigneds member varaiables instead of constructor

``` cpp
template <typename T>
Buffer<int>::GetSpecs(){}

template <>
Buffer<float>::GetSpecs(){}
```

## Error: Buffer Multiple defnitions
#### Fix:
Somehow "inline" is necessary before very defnition