# SearchSwarm

## Requirements

1. Will be able to segment a large area into smaller sections based on number of agents.
2. Each segmented area will have an optimal sweep calculated. This should be the least amount of time to travel, accounting for acceleration and deacceleration, as well as any altitude changes
3. Each agent will have object avoidance capability.
4. Each agent will be equipped with a lightweight object detection model to identify articles of interest.
5. An agent's travel path and acceleration will allow for clear images.

## Functional Design
### Segmenting Large Area
When a search area is defined, the first step should be to segment the area into more basic polygons, as well as smaller areas for each agent to cover:

![image](https://github.com/user-attachments/assets/6c1c729c-5464-4ea5-9940-e52dbb2161cd)

Which should be segmented to something like:

![image](https://github.com/user-attachments/assets/55559bd5-5dfb-4d04-bec4-5903a3a64f2e)

The segmentation will be performed on a "home" machine independent of each agent, to decrease overhead on each agent as well as improve performance using a higher spec device.

### Segmented Area Sweep
Each segmented area should have an optimal sweep calculated, again done on the "home" machine. An example of some sweeps calculated can be seen here:

![image](https://github.com/user-attachments/assets/3c5382ea-f7a0-4e10-b2f6-52f0387fd5c7)

It should be noted that the prority of the sweep is to complete a sweep as quickly as possible, without emphasis on the return deistnace. A cost function can be assumed to be the distance to travel from the starting point, then the total distance of the sweep. Addtionnally, this should mean that sharp angles may not be the best course, due to acceleration/decceleration time, so look into other types of distances, ex. Dubins

### Object Avoidance
360 degree LiDAR sensor at the minimum to look for any obstacles ahead of the agent, potential for a 3D LiDAR scanner to get a better perspective on overall height. Realistically, any objects the LiDAR sees in front of the agent will be maneuvared around laterally, which can reduce the need for 3D imaging and the added computation.

### Object Detection Model
Models like BiSeNet v2 or ResNet18 are viable options. Will only need to actualy train on a few classes it can be more lightweight, and only instance detection or object recognition is needed as opposed to full semantic segmentation.

### Travel Path
Depending on the camera and it's frame rate, the path will be adjusted to ensure proper coverage while traveling at the highest possible velocity, with minimal acceleration change.
