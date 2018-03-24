# Computer-Games-Studio-Assignment-1
First semester assignment for Computer Games Studio in second year of my degree

A 3D scene made using DirectX12, I used a template given to me by my lecturer in this module to start off. 
This template allowed models to be placed and rendered.
With this template, I added a lot more models and used textures and normal maps alongside the bumpmap shader
that we had access to to make my models, planets of the solar system in this case, more reactive to the "light" in the scene.
Basic camera control is also in this scene and allows the controller to move the camera with the mouse an move through the
scene with the keyboard.

Basic "animations" were also coded in by me, to give the planets a rotation and orbit around the sun model. I did this
with trigonometric functions and matrix multiplication. With this I made sure that each model was scaled appropriately and moved
at a speed relative to their distance from the sun.

Towards the end of the assignment I also added a skybox to the scene. The skybox isn't actually a separate "skybox" class either,
but is actually just another planet model with a space texture and then scaled negatively so that the texure appears on the inside.
