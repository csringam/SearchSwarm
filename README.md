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
TBD

### Object Detection Model
BiSeNet v2?
Will only need to actualy train on a few classes so maybe can be more lightweight
