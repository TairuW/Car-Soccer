#ifndef BALL_H_
#define BALL_H_

#include <mingfx.h>

/// Small data structure for a ball
class Ball {
public:

    /// The constructor sets the radius and calls Reset() to start the ball at
    /// the center of the field
    Ball() : radius_(2.6) {
        velocity_ = Vector3((std::rand() % 40 - 10),
                            (std::rand() % 40 - 20),
                            (std::rand() % 40 - 10));
        Reset();
    }

    /// Nothing special needed in the constructor
    virtual ~Ball() {}


    void Reset() {
        position_ = Point3(0, radius_, 0);
    }

    float radius() { return radius_; }

    Point3 position() { return position_; }
    Vector3 velocity() { return velocity_; }

    void set_position(const Point3 &p) { position_ = p; }
    void set_velocity(const Vector3 &p) { velocity_ = p; }

    void launch_ball() {
        position_ = Point3(0, radius_, 0);
        velocity_ = Vector3((std::rand() % 40 - 10),
                            (std::rand() % 40 - 20),
                            (std::rand() % 40 -10));
    }

private:
    // You will probably need to store some additional data here, e.g., velocity
    Vector3 velocity_;
    Point3 position_;
    float radius_;
};

#endif
