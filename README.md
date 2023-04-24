# Ovis Runtime
**Deprecated:** Replaced by the [Ovis Framework](https://github.com/ovis-games/ovis-framework)

This repository contains the runtime library for a custom ECS focused programming language I developed.
The overarching idea was to create a website where you can easily create interactive graphical applications which would be ideal to for creating small games, trying out additional rendering techniques and general rapid prototyping.

## ECS Concept (WIP)
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

## Example
The following example showcases how the language can be used to write a simple program that changes the color of the viewport based on the mouse position:
```
#Update
function updateClearColor(dims: ViewportDimensions, mouseMove: MouseMoveEvent) -> ClearColor {
  let clr = ClearColor()

  clr.r = mouseMove.position.x / dims.x
  clr.g = mouseMove.position.y / dims.y
  clr.a = 1.0

  return clr
}
```
This program defines a single function `updateClearColor`.
The `#Update` attribute in line 1 indicates that the function represents and update job and should be executed whenever one of the function inputs change.
The first input to the function is `ViewportDimensions` which is a viewport component resource and is a type alias for a two-dimensional vector that represents the size of the current viewport.
The second input is of the type `MouseMoveEvent` and as the name suggests is an event resource.
Thus, the function gets called automatically whenever a move move event is fired and the viewport has the `ViewportDimensions` attached which is done automatically when the main viewport is created.
The `MouseMoveEvent` is a built-in event and gets emitted automatically whenever the cursor moves over one of the viewports.
The output of the function is of the type `ClearColor` which is also a viewport component and is a type alias for the `Color` type.
There is a built-in job job `clearViewport` that reads this component and clears the framebuffer accordingly.
