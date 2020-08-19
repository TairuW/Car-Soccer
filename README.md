# Car Soccer
/* Tairu Wang */
# Development
## Overview
This car soccer-game using some ideal physical models to simulat the car or ball's motions including movement, collision, friction and reflection.

## class Ball()
The class ball takes some basic attributes inlcuding the ball's velocity, position and radius.
### Constructor
Give three random velocity to the ball everytime the ball is launched.
### Reset()
Reset() function is designed to re-locate the ball's position to (0,radius,0) everytime when it is called.
### set_velocity() and velocity()
In order to set and get the velocity of the ball.
### set_position() and position()
In order to set and get the velovity of the ball.

## class Car()
Th class ball will have a turn angle to decide the velocity of the car.
### Reset()
Re locate th car, set every field to 0.
### set_angle() and angle()
In order to set and get the angle of the car.
### set_position() and position()
In order to set and get the position of the car.
### set_velocity() and velocity()
In order to set and get the velocity of the car.

## car_soccer.cc
### OnSpecialKeyDown()
Reset the ball's location and velocity everytime when the spacebar is pressed.
### BoundaryDetection()
This void functions takes no arguments, basically it is divided into two parts, first part is to detect if the ball has reached the boundary, using the formula provided in the assignment to detect, just check each boundary (six surfaces), once it reaches the boundary, using the norm and dot operation to reflect the ball’s velocity. As for the car, since we don’t need to change the car’s velocity, and it only moves on x and y axis, just set a new position when reaches the boundary.
### UpdateSimulation(double timeStep)
#### Decide car's movement
This is the function that updates the car and ball’s movement. First, I call the boundaryDetection() function to ensure the objects won’t go out of boundary. Then, starts to decide the car’s turning. First, read the turn rate from the keyboard, and using the turn rate to decide the angle that the car will turn. Based on this angle, we can update the car’s velocity.  I set 200 as the car’s turning speed. Then, based on the thrust/drag theory provided in the requirement file, I update the velocity, actually is like a force, where the updatedVelocity equals to (thrust - drag)dt, then set up the new velocity, and using p = p’ + dt to decide the new postion. Since the direction,I use “-” instead of “+”. Using this implementation will make the car more like a realistic model, it won't move sideways.
#### Give a intial velocity to the ball and acceleration based on gravity
The ball’s position is based on its velocity, simply using p = p + v*t. Then, update its acceleration based on the gravity based on the timeframe.
#### Collision
According to the background provided in the requirement, there are four steps to update the velocity after collision. 1. detect if there is a collision based on the relationship between the distance of the objects and the sum of their radius. 2. If the distance less or equal than the sum, compute a relative velocity. 3.Next, I used .dot operator and ToUnit build in function to decide the correct norm to reflect the velocity based on its relative velocity, using the reflection formula provided in the slide, and set the new velocity.
#### Goal detectiom
Then detect if the ball hits the goal. This is like a simpler version of checking boundary, just to decide if the ball hits the goal area. If so, reset the location of ball and car.
### Draw Boundary
First, I set up a new matrix named initialPosition, and based on this matrix, starts to draw the playground. I use two techniques. First, connect the points of the pitch one by one to draw the boundary. Secondly, use loops to draw the goal like a grid, which is easier to implemente.  
