# How To Build

## Cmake (minumum version 3.28) needs to be installed.

## Visual Studio 18 2026 needs to be installed (MSVC 18)

### Initialization

```
cmake -B build
```

### Build

```
cmake --build build
```

# Architecture

### ECS

Entity is an ID, namely EntityId

Component is data, component is bound to an Entity Id.

Components are any struct derived from AComponent, which is wrote into concept (C++ 20) as a compile time constraints, so that the semantic can be precise, and Typename is more stable than string literal.

Memory Management of Component is currently inplemented via SparseSet in dsa folder, the reason I choose SOA over AOS is because when doing multithreading, since CPU might fetch entire cache line, it might fetch readonly data with mutable data and cause false sharing. Therefore, using Sparse Set can gain spacial locality against single component type, while decoupling from accessing other component type.

System are functions that do not return, every system is considered a different thread.

(WIP feature) - Multithreading of Systems is done by constraints from DAG, which will be initialized in runtime, but definition of system is certain in compile time. Biggest synchronization problem from multithreading is the problem of multiple writer against single data, which cause data race. However, since my comoponents are independent from each others, I can deduce a DAG from its function signature, which defines a dependency when there is a data been written by a system. And let other systems that depend on this data automatically wait for event to complete. In addition, priority and other relationships can be add to DAG algorithm as well.

Query of Components are constructed in compile time using templates and turn into a fold expansion, and returns an array made of references. Reference are used per tick, which means query is redone per tick, so that lifetime of reference is limited to single run of its belonging system, while system is atomic, avoiding any dangling reference. Component types in query can be made const, in this case, it can be used as an evidence of immutability in compile time, and be used to deduce System DAG in runtime initialization.

(WIP feature) - Currently query might have dangling reference if the storage of components is resized. To solve this, the insertion of components must be placed into a command queue and execute in batch at the end of frame.

### Rendering

Encapsulated Window, designed APIs that accept sfml data, and created adapter between ECS module and Rendering module to avoid coupling.

### Future plan

1. Physics, it should be an independent module just like Rendering, and should be the only writer to Transform
2. Scene/World, currently there is one global ECS manager, scene can make each ECS manager local.
3. ECS Resource, globally unique data, such as player controller, sprite, config files, keybindings and so on.
4. Asset Manager, which is used to manage access and lifetime of game assets, the consumer of assets should only use handle. Which act as an ID but have semantic.
