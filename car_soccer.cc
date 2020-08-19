/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    if (IsKeyDown(GLFW_KEY_LEFT))
        dir[0]--;
    if (IsKeyDown(GLFW_KEY_RIGHT))
        dir[0]++;
    if (IsKeyDown(GLFW_KEY_UP))
        dir[1]++;
    if (IsKeyDown(GLFW_KEY_DOWN))
        dir[1]--;
    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        ball_.Reset();
        ball_.launch_ball();
    }
}

void CarSoccer::boundaryDetction() {
        //Ball Boundary Detection
        if (ball_.position().y() <= ball_.radius()) {
          ball_.set_position(Point3(ball_.position().x(),
                                    ball_.radius(),
                                    ball_.position().z()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(0,1,0))) * Vector3(0,1,0)));
        }
        if (ball_.position().y() >= 35 - ball_.radius()) {
          ball_.set_position(Point3(ball_.position().x(),
                                    35 - ball_.radius(),
                                    ball_.position().z()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(0,-1,0))) * Vector3(0,-1,0)));
        }
        if (ball_.position().x() >= 40-ball_.radius()) {
          ball_.set_position(Point3(40-ball_.radius(),
                                    ball_.position().y(),
                                    ball_.position().z()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(-1,0,0))) * Vector3(-1,0,0)));
        }

        if (ball_.position().x() <= -40+ball_.radius()) {
          ball_.set_position(Point3(-40 + ball_.radius(),
                                    ball_.position().y(),
                                    ball_.position().z()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(1,0,0))) * Vector3(1,0,0)));
        }

        if (ball_.position().z() >= 50 - ball_.radius()) {
          ball_.set_position(Point3(ball_.position().x(),
                                    ball_.position().y(),
                                    50 - ball_.radius()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(0,0,1))) * Vector3(0,0,1)));
        }

        if (ball_.position().z() <= -50 + ball_.radius()) {
          ball_.set_position(Point3(ball_.position().x(),
                                    ball_.position().y(), -50 + ball_.radius()));
          ball_.set_velocity(0.8*(ball_.velocity()- 2*(ball_.velocity().Dot(Vector3(0,0,-1))) * Vector3(0,0,-1)));
        }

        //Car boundary detection
        if (car_.position().z() <= -50 + car_.collision_radius()) {
          car_.set_position(Point3(car_.position().x(),
                                   car_.position().y(),
                                   car_.collision_radius() - 50));
        }
        if (car_.position().z() >=  50 - car_.collision_radius()) {
          car_.set_position(Point3(car_.position().x(),
                                   car_.position().y(),
                                   50 - car_.collision_radius()));

        }
        if (car_.position().x() <=  -40 + car_.collision_radius()) {
          car_.set_position(Point3(car_.collision_radius() - 40,
                                   car_.position().y(),
                                   car_.position().z()));

        }
        if (car_.position().x() >=  40 - car_.collision_radius()) {
          car_.set_position(Point3(40 - car_.collision_radius(),
                                   car_.position().y(),
                                   car_.position().z()));

        }

}

void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.
    boundaryDetction();

    //angle = turnRate * speed * dt:
    //turnRate:
    //Decide the turnRate and the angle cased on the turnRate
    float turnRate = joystick_direction().x();
    car_.set_angle ( car_.angle() - timeStep * turnRate * 200);
    Vector3 updateVelocity = 150 * Vector3((joystick_direction().y()* sin(car_.angle() * M_PI/180)),0,  joystick_direction().y() * cos(car_.angle() * M_PI/180)) - 3 * car_.velocity();
    car_.set_velocity(car_.velocity() + timeStep *(updateVelocity)) ;
    car_.set_position(car_.position() - timeStep * car_.velocity());


    //Gravity as acceleration
    ball_.set_position(ball_.position() + (timeStep)*ball_.velocity());
    ball_.set_velocity(ball_.velocity() + (timeStep)*Vector3(0, -9.8, 0));


    //Ball movement after collision
    Vector3 dis = ball_.position() - car_.position();
    if (dis.Length() < (ball_.radius() + car_.collision_radius())) {

       Vector3 revelant = ball_.velocity() - car_.velocity();
       ball_.set_velocity((-1)*car_.velocity() - (revelant - 2 * (revelant.Dot((revelant.ToUnit()))*(dis.ToUnit()))));
    }

    //Goal check
    if(ball_.position().z() <= (-50 + ball_.radius()) && ball_.position().x()>= (-10 + ball_.radius()) && ball_.position().x()<=(10 - ball_.radius()) &&ball_.position().y()<= (10 - ball_.radius()))
    {
       ball_.Reset();
       car_.Reset();
    }

    if(ball_.position().z() >= (50 - ball_.radius()) && ball_.position().x()>= (-10 + ball_.radius()) && ball_.position().x()<=(10 - ball_.radius()) &&ball_.position().y()<= (10 - ball_.radius()))
    {
       ball_.Reset();
       car_.Reset();
    }
}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    viewMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));

    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);

    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);

    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);

    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::RotationY(car_.angle()) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);


    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);


    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);


    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()

    Matrix4 initialPosition;
    // The boundary of the pitch
    std::vector<Point3> loop;
     loop.push_back(Point3( 40,0,50));
     loop.push_back(Point3( 40,0,-50));
     loop.push_back(Point3( -40,0,-50));
     loop.push_back(Point3( -40,0,50));
     loop.push_back(Point3( 40,0,50));
     loop.push_back(Point3( -40,0,50));
     loop.push_back(Point3( -40,35,50));
     loop.push_back(Point3( -40,35,-50));
     loop.push_back(Point3( -40,0,-50));
     loop.push_back(Point3( 40,0,-50));
     loop.push_back(Point3( 40,35,-50));
     loop.push_back(Point3( -40,35,-50));
     loop.push_back(Point3( 40,35,-50));
     loop.push_back(Point3( 40,35,50));
     loop.push_back(Point3( -40,35,50));
     loop.push_back(Point3( 40,35,50));

    quickShapes_.DrawLines(modelMatrix_ * initialPosition, viewMatrix_, projMatrix_, Color(255,255,255), loop, QuickShapes::LinesType::LINE_LOOP, 0.1);

   //Goal set up
    std::vector<Point3> goal1;
    for(int i=0;i<=10; i++)
    {
        goal1.push_back(Point3( 10,i,50));
        goal1.push_back(Point3( -10,i,50));
         quickShapes_.DrawLines(modelMatrix_ * initialPosition, viewMatrix_, projMatrix_, Color(255,255,0), goal1, QuickShapes::LinesType::LINES, 0.05);
    }
    for(int i=-10;i<=10; i++)
    {
        goal1.push_back(Point3( i,0,50));
        goal1.push_back(Point3( i,10,50));
        quickShapes_.DrawLines(modelMatrix_ * initialPosition, viewMatrix_, projMatrix_, Color(255,255,0), goal1, QuickShapes::LinesType::LINES, 0.05);
    }

    std::vector<Point3> goal2;
    for(int i=0;i<=10; i++)
    {
        goal2.push_back(Point3( 10,i,-50));
        goal2.push_back(Point3( -10,i,-50));
        quickShapes_.DrawLines(modelMatrix_ * initialPosition, viewMatrix_, projMatrix_, Color(0,128,255), goal2, QuickShapes::LinesType::LINES, 0.1);
    }
    for(int i=-10;i<=10; i++)
    {
        goal2.push_back(Point3( i,0,-50));
        goal2.push_back(Point3( i,10,-50));
        quickShapes_.DrawLines(modelMatrix_ * initialPosition, viewMatrix_, projMatrix_, Color(0,128,255), goal2, QuickShapes::LinesType::LINES, 0.1);
    }

}
