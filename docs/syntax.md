# Syntax

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
