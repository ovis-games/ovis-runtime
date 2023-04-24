# Ovis Runtime
**Deprecated:** Replaced by the [Ovis Framework](https://github.com/ovis-games/ovis-framework)

This repository contains the runtime library for a custom ECS focused programming language I developed.
The overarching idea was to create a website where you can easily create interactive graphical applications which would be ideal to for creating small games, trying out additional rendering techniques and general rapid prototyping.

## ECS Concept
This runtime extends on the concept of traditional ECS frameworks.
Traditionally, the state in ECS frameworks consist of a set of entities (usually just some kind of id) and components (arbitrary data types the can be "attached" to entites).
Additionally, there are a set of systems (basically functions) that are able to modify the state.

This runtime introduces a few more concepts that make it possible to use it for whole applications.

* **Scene**: the scene contains the whole state of the ECS.

* **Entity**: same as in traditional ECS terminology.

* **Entity component**: some data type that can be attached to entities.
In traditional ECS implementions usually just called component.

* **Scene component**: some data type that can be added to a scene.
In contrast to entity components, there can be only one scene component of a specific type per scene.
That makes it very useful for global data and avoids the need to create a special entity to hold such data.

* **Event**: events can be emitted or consumed by systems.
For each event type, the scene stores a list of events that got emmitted during the current frame.
After the frame is finished all events are discarded.

* **Viewport**: similar to entities, the scene also stores a list of viewports.

* **Viewport component**: similar to entity components, viewport components can be attached to viewports.
E.g., each viewport has a component `ViewportDimensions` that stores the dimensions of the viewport.


## Language Goals
This section covers the goals I had in mind when designing the language and how I tried to achieve them.

* [Familiar syntax](docs/syntax.md): the language should have a familiar, easily understandible syntax
* [Safety](docs/safety.md): you should not have to worry about data races, or dangling pointer when writing code
* [No boilerplate](docs/boilerplate.md): you should not spent your time writing boilerplate code, but focus on the actual functionality
* [Speed](docs/compilation.md): the code should compile to native machine code / shader code for speed and flexibility
* [SemVer aware dynamic linking](docs/linking.md): reduce compilation time when using plugins
