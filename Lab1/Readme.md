### Transformations and Scene Rendering

This program:
- Renders triangle meshes using OpenGL. 
- Implements custom translation, rotation and scaling functions and leverages them to apply the transformation from world to camera coordinates.
- Impements interactive translation and rotation of the camera using keyboard keys
- Implements perspective and parallel projection
 
<div style="display: flex; justify-content: center; gap: 20px;">
    <figure>
  <img src="assets/par.png" alt="Parallel Projection" width="250">
  <figcaption>Parallel Projection</figcaption>
    </figure>
    <figure>
  <img src="assets/pers.png" alt="Perspective Projection" width="250">
    <figcaption>Perspective Projection</figcaption>
      </figure>
</div>

<div style="display: flex; justify-content: center; gap: 20px;">
  <figure style="text-align: center; position: relative;">
    <img src="assets/par.png" alt="Parallel Projection" width="250">
    <figcaption style="position: absolute; bottom: 0; width: 100%;">Parallel Projection</figcaption>
  </figure>
  <figure style="text-align: center; position: relative;">
    <img src="assets/pers.png" alt="Perspective Projection" width="250">
    <figcaption style="position: absolute; bottom: 0; width: 100%;">Perspective Projection</figcaption>
  </figure>
</div>

- Calculates and stores vertex normals for all triangle meshes and renders them as if they were RGB colours over the surfaces of the meshes.

<div style="display: flex; justify-content: center; gap: 20px;">
    <figure>
  <img src="assets/pers_rgb.png" alt="Parallel Projection" height="200">
  <figcaption>Parallel Projection</figcaption>
    </figure>
    <figure>
  <img src="assets/par_rgb.png" alt="Perspective Projection" height="200">
    <figcaption>Perspective Projection</figcaption>
      </figure>
</div>

- Implements scene composition, i.e., the possibility to render multiple models, with custom parameters for scaling, rotation, and translation

<div style="display: flex; justify-content: center; gap: 20px;">
    <figure>
  <img src="assets/scene.png" alt="Parallel Projection" height="300">
  <figcaption>Scene Composition</figcaption>
    </figure>
</div>
