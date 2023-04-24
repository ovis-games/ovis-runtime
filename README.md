# Ovis Runtime
**Deprecated:** Replaced by the [Ovis Framework](https://github.com/ovis-games/ovis-framework)

This repository contains the runtime library for a custom ECS focused programming language I developed.
The overarching idea was to create a website where you can easily create interactive graphical applications which would be ideal to for creating small games, trying out additional rendering techniques and general rapid prototyping.

## Language Goals
This section covers the goals I had in mind when designing the language and how I tried to achieve them.

### Easy
One very important aspect to me was that the language can be easily understood when you have at least a little bit of programming experience.
Thus, I looked at existing languages (Swift, Rust, C++, TypeScript, WGSL, ...) and used a familiar syntax.
E.g., a function that caluclates the area of a circle would look like this:
```
function areaOfCircle(radius: Float) -> Float {
    return 2.0 * Float.pi * radius
}
```
and a struct can be defined as follows:
```
struct Player {
    name: String
    score: Int
    position: Vec2F
}
```

<!--
Another part that often makes a programming language complex is object lifetimes which becomes mostly important when an object is created on the heap.
There are multiple solutions to this with the two most commonly used solutions beeing reference counting and garbage collection with both have their own pros and cons.
The ovis programming language takes a different approach here by taking a step back and looking at why we need data on the heap in the first place.
Generally, the heap is needed when we want to store data for a longer 
-->

# No Boilerplate
When dealing with ECS frameworks you often need to write a lot of boilerplate code to register components or systems, set up dependencies an so on.
I wanted to have this boilerplate code abstracted away, so the user can focus on the actual functionality.
E.g., 
