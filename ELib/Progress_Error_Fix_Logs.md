# Feature: Editor and Library (OpenGL)

## Process:

### Project Setup: Premake

> Simple system cycle using GLFW
> Editor and OpenGL Library Project.
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

# Progress Log:
* (11/12/23) [Buffer Creation](#buffer-creation) : Dynamic Vertex Array buffer creation
* (18/12/23) [Render](#render)      : Able to render basic shapes;
* (24/12/23) [Key Mapping](#key-mapping) : Implemented KeyBinding, potential remapping of keys to actions

<a id="buffer-creation"></a>
## Buffer Creation
In: Buffer.h, Buffer.cpp, Buffer.inl
* Able to Create buffer, with custom vertex array layout dynamically.
* Using template specialization of a member function to specify data specs of each vertex array attribute
* Allows for custom container types, like glm::vec2, glm::vec3 or custom math containers.
* Dynamically Resize of OpenGL buffer creation calls.
```cpp
// Creating a buffer e.g
BufferData BD;
BD.ConstructBufferElement<glm::vec3>("pos", pos_vtx);
BD.ConstructBufferElement<glm::vec3>("clr", clr_vtx);
BD.ConstructBufferElement<glm::vec2>("tex", tex_vtx);
BD.ConstructIndexBuffer(idx_vtx);
```


<a id="render"></a>
## Render 
In: Model.h, Model.cpp
Implements model coordinates from [-1, 1] dimensions. Creates BufferData class objects
Implemented Models: Point, Line, Hollow Quad, Filled Quad, Hollow Circle, Filled Circle

<a id="key-mapping"></a>
## Key Mapping
In: Defines.h, Input.h, Input.cpp (e.g in CameraController.cpp)
Implements using enum flags as actions tied to a key / mouse input.
Flags can be combined for specific configurations / implementation.
### ENUM_Key_Actions (Defines.h)
* Base actions, flags can be combined for unique instructions
### class KeyMap: 
* wraps std::bitset<MAX_FLAG> to contain enum operations
KeyMap.CheckFlag: Takes in a sequence of enum flags, and check if object has specified flags
KeyMap.SetFlag: Takes in a sequence of enum flags, and set flags onto the bitset member value
```cpp
KeyMap TestKeyMap;
// Single Actions
TestKeyMap.SetFlag(GLFW_KEY_A, {ENUM_Key_Actions::FORWARD});
// Combination of Actions
TestKeyMap.SetFlag(GLFW_KEY_Z, {ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD});
```

### class KeyBinding:
Executes instructions, bound to key
```cpp
// Code Snippet Definition:
void KeyBinding::Update(const std::map<int, KeyInfo*>& KeySequence, std::function<void(Base_KeyMap)> func_ptr) {
    for (auto [key, _] : KeySequence) {
        if (m_BaseKeyActionMap.find(key) != m_BaseKeyActionMap.end()) {
            func_ptr(m_BaseKeyActionMap[key]);
        }
    }
}

// Code Snippet e.g
Core::KeyBinding m_KeyBindings;
m_KeyBindings.Update(p_inputsystem->GetCurrentSequence(), [](Base_KeyMap instructions) {
    if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::FORWARD)) {
        E_LOG_INFO("Zoom in");
    }
    if (instructions.CheckFlags(ENUM_Key_Actions::ZOOM, ENUM_Key_Actions::BACKWARD)) {
        E_LOG_INFO("Zoom out");
    }
    });
```



# Difficulties
### Feature: Buffer Layout Element Specialization for Different Types

* Vec2, Vec3, Vec4, Mat3, Mat4, float, int, unsigned short

#### Implementation

* Template specialize member function that reassigns member varaiables instead of constructor

``` cpp
template <typename T>
Buffer<int>::GetSpecs(){}

template <>
Buffer<float>::GetSpecs(){}
```

### Error: Buffer Multiple defnitions
#### Fix: (12/12/2023)
Somehow "inline" is necessary before very defnition

### Error: No Definition Overload (13/12/2023)
##### Potential fix:
Check if <T> is the same type as std::vector<T>
