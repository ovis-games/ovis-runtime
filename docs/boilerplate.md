# Boilerplate

When dealing with ECS frameworks you often need to write a lot of boilerplate code to register components or systems, set up dependencies an so on.
I wanted to have this boilerplate code abstracted away, so the user can focus on the actual functionality.
E.g., definiting a job is as simple as writing a normal function and giving it the `#Update` or `#Setup` attribute.

## Jobs

### Update Jobs
Update jobs correspond to a System in proper ECS terms and they are executed whenver one of its input resources change.
If one of the inputs is, e.g., an entity component, the job will automatically executed for every entity (that has the specified component).

```
#Update
function foo(i1: InputResource1, i2: InputResource2) -> (OutputResource1, OutputResource2) {

}
```

### Setup Jobs
Setup jobs are executed once after the scene is created instead of every frame.
Otherwise, they behave exactly like update jobs.
```
#Setup
function foo(i1: InputResource1, i2: InputResource2) -> (OutputResource1, OutputResource2) {

}
```

## Resources
Currently, the user can implement four kinds of resources: `SceneComponents`, `EntityComponents`, `ViewportComponents`, and `Events`.
To create a resource just add the corresponding tag (e.g., `#SceneComponent`) to a struct or type alias declaration, e.g.:
```
#Event
struct MouseMoveEvent {
  position: Vec2F
  relativePosition: Vec2F
}

#EntityComponent
type Position = Vec3F
```
The framework will ensure that the corresponding resource type will be registered so that the approprate CPU and GPU buffers will be created.
