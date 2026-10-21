# Ray Tracing in One Weekend (C implementation)

A C port of Peter Shirley's *Ray Tracing in One Weekend*. This project follows the book's progression from basic rays to a full scene, and serves as a foundation for experimenting with CPU multithreading and measuring its impact on render time. Raylib is only used to display the rendered scene in a window, generally its not at all necessary to use this library. The Threading is implemented along [OSTEPs Threads section](https://ostep.org/).


![Final render](images/final_render.jpg?raw=true "Final render")

High-resolution render of the implemented renderer, based on the cover of *Ray Tracing in One Weekend*.[^final_render]

[^final_render]: Rendered with the C implementation of the ray tracer.

# Progression:
![fade](/images/fade.jpg?raw=true "fade")

![sky](/images/sky.jpg?raw=true "sky")

![first_sphere](images/first_sphere.jpg?raw=true "first_sphere")

![surface_normals](images/surface_normals.jpg?raw=true "surface_normals")

![normal_ground](images/normal_ground.jpg?raw=true "normal_ground")

![diffuse](images/diffuse.jpg?raw=true "diffuse")

![gamma_corrected](images/gamma_corrected.jpg?raw=true "gamma_corrected")

![fuzz](images/fuzz.jpg?raw=true "fuzz")

