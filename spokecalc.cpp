#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Output.H>

#include <cmath>
#include <iostream>

const double pi = std::acos(-1);
Fl_Value_Input* OLDInput;
Fl_Value_Input* leftFlangeDistanceInput;
Fl_Value_Input* rightFlangeDistanceInput;
Fl_Value_Input* leftFlangeDiameterInput;
Fl_Value_Input* rightFlangeDiameterInput;
Fl_Value_Input* ERDInput;
Fl_Value_Input* wallThicknessInput;
// pattern data
Fl_Value_Input* crossesInput;
Fl_Value_Input* holesInput;

Fl_Value_Output* leftOutput;
Fl_Value_Output* rightOutput;

void calc( Fl_Widget*, void* )
{
    unsigned int old = OLDInput->value();
    unsigned int lfdis = leftFlangeDistanceInput->value();
    unsigned int rfdis = rightFlangeDistanceInput->value();
    unsigned int lfdia = leftFlangeDiameterInput->value();
    unsigned int rfdia = rightFlangeDiameterInput->value();
    unsigned int erd = ERDInput->value();
    unsigned int thickness = wallThicknessInput->value();

    unsigned int crosses = crossesInput->value();
    unsigned int holes = holesInput->value();

    // the main triangle: A - B (flange to "virtual" hub middle), B - C (virtual hub middle to rim), C - A (rim to flange a.k.a. the spoke's projection)
    // ABC angle is right angle
    // looking for C - A
    // steps:
    // 1; (front view of hub) calculate angle of the spoke towards hub
    // 2; (side view of hub) small triangle: hub middle point (H), spoke starting point (S), half string starting from S and intersecting H to rim
    //

    // LEFT
    double ab = old/2.0 - lfdis;
    double alpha = crosses*2*pi/(holes/2);
    double halfstring = sin(alpha) * lfdia/2;
    double line2 = sqrt((lfdia/2)*(lfdia/2) - (halfstring*halfstring));
    double bc = erd/2 + thickness - line2;
    double ca = sqrt(ab*ab + bc*bc);

    leftOutput->value( ca );

    // RIGHT
    ab = old/2.0 - rfdis;
    halfstring = sin(alpha) * rfdia/2;
    line2 = sqrt((rfdia/2)*(rfdia/2) - halfstring*halfstring);
    bc = erd/2 + thickness - line2;
    ca = sqrt( ab*ab+bc*bc );

    rightOutput->value(ca);
}

int main(int, char**)
{
    Fl_Window mainWindow(640,480);
        // hub data
        OLDInput = new Fl_Value_Input ( 200, 10, 50, 20, "O.L.D. (mm):" );
        leftFlangeDistanceInput = new Fl_Value_Input ( 200, 40, 50, 20, "Left flange distance (mm):" );
        rightFlangeDistanceInput = new Fl_Value_Input ( 200, 70, 50, 20, "Right flange distance (mm):" );
        leftFlangeDiameterInput = new Fl_Value_Input ( 200, 100, 50, 20, "Left flange diameter (mm):" );
        rightFlangeDiameterInput = new Fl_Value_Input ( 200, 130, 50, 20, "Right flange diameter (mm):" );
        // rim data
        ERDInput = new Fl_Value_Input ( 200, 160, 50, 20, "ERD (mm):" );
        wallThicknessInput = new Fl_Value_Input ( 200, 190, 50, 20, "Wall thickness (mm):" );
        // pattern data
        crossesInput = new Fl_Value_Input ( 500, 10, 50, 20, "Number of crossess:" );
        holesInput = new Fl_Value_Input ( 500, 40, 50, 20, "Number of spoke wholes:" );

        Fl_Button calcButton( 500, 70, 100, 30, "Calculate" );

        leftOutput = new Fl_Value_Output ( 500, 100, 50, 20 );
        rightOutput = new Fl_Value_Output ( 500, 130, 50, 20 );
    mainWindow.end();
    mainWindow.show();

    calcButton.callback( calc );

    return Fl::run();
}
