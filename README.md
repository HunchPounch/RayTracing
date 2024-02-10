# RayTracing
## Description:

There is some sort of viewpoint (camera) in space. Also in the space there is some three-dimensional structure (scene). Between them there is a rectangle divided into square pixels (screen).

<p align="center">
  <img src="screenshots/ray.png" alt="Ray Image">
</p>

The task of ray tracing is to draw a ray from the viewpoint through the center of each pixel of the screen - and see if it intersects any of the objects in the scene. If the ray intersects any of the objects, you need to paint the pixel with the desired color.

An arbitrary number of spheres, tetrahedrons and parallelepipeds are acceptable as objects. Space for an observer has the following representation: the observer looks at the corner of the origin, where the x-axis is to the left and the y-axis is to the right

## Parameter file (parameter.txt):
1) camera coordinates x, y, z (three real numbers);
2) coordinates of the normal vector to the screen (three real numbers);
3) coordinates of the vector perpendicular to the normal to the screen, which defines
direction "up" (three real numbers);
4) distance from the camera to the screen a0 (one real number);
5) distance from the camera to the boundary of visibility a0+ a1 (one real number); 
6) vertical viewing angle α (one real number);
7) width w and height h of the screen in pixels (two integers);
8) coordinates of the light source (three real numbers)

## Oblect file (objects.txt):
1) a sphere is specified by enumerating the coordinates of the sphere center and then the radius
2) tetrahedron is defined by four points in space
3) the box is defined by two opposite corner points in space

Examples of completed files can be found in the repository

## Result:

<p align="center">
  <img src="screenshots/out.png" alt="Ray Image">
</p>
