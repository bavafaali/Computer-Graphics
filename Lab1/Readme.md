### Transformations and Scene Rendering

This program:
- Renders triangle meshes using OpenGL. 
- Implements custom translation, rotation, and scaling functions and leverages them to apply the transformation from world to camera coordinates.
- Implements interactive translation and rotation of the camera using keyboard keys.
- Implements perspective and parallel projection.

| Parallel Projection | Perspective Projection |
|---------------------|-----------------------|
| <img src="assets/par.png" width="250"> | <img src="assets/pers.png" width="250"> |


- Calculates and stores vertex normals for all triangle meshes and renders them as if they were RGB colors over the surfaces of the meshes.

| Parallel Projection (RGB) | Perspective Projection (RGB) |
|--------------------------|----------------------------|
| <img src="assets/par_rgb.png" alt="Parallel Projection" height="200"> | <img src="assets/pers_rgb.png" alt="Perspective Projection" height="200"> |

- Implements scene composition, i.e., the possibility to render multiple models, with custom parameters for scaling, rotation, and translation.

| Scene Composition |
|----------------------------|
| <img src="assets/scene.png" alt="Scene Composition" height="300"><br>
  <em>Scene Composition</em> |
