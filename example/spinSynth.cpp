/*	Graphics Library of Views (GLV) - GUI Building Toolkit
	See COPYRIGHT file for authors and license information */

#include "example.h"

struct Scene : View3D{

	Scene(const Rect& r): View3D(r){}

	virtual void onDraw3D(){
		using namespace glv::draw;

		if((rx+=incx) >= 360) rx-=360;
		if((ry+=incy) >= 360) ry-=360;
		if((rz+=incz) >= 360) rz-=360;

		Point3 p[] = {
			Point3(-0.5,-0.5,0), Point3(+0.5,-0.5,0), Point3(0,+1,0)
		};
		
		Color c[] = { HSV(0.1), HSV(0.2), Color(0) };
		
		translateZ(-3);
		rotate(rx, ry, rz);
		paint(Triangles, p,c,3);
	}
	
	float incx, incy, incz;
	float rx, ry, rz;
};

Slider slider1(Rect(200, 40)), slider2(slider1), slider3(slider1);
View toolBar(Rect(0,60));
View statusBar(Rect(0,-20,0,20));
Label statusString("", 10, 4);
Scene scene(Rect(0,toolBar.h, 0,-(toolBar.h+statusBar.h)));

void ntStatusString(const Notification& n){
	View * s = (View *)n.sender();
	statusString.value(s->className() + std::string(" ") + s->name() + ": " + s->valueToString());
}

int main (int argc, char ** argv){

	slider1.name("inc x");
	slider2.name("inc y");
	slider3.name("inc z");

	slider1.interval(30,-30);
	slider2.interval(30,-30);
	slider3.interval(30,-30);

	slider1.attachVariable(scene.incx);
	slider2.attachVariable(scene.incy);
	slider3.attachVariable(scene.incz);
	
	slider1.attach(ntStatusString, Update::Value);
	slider2.attach(ntStatusString, Update::Value);
	slider3.attach(ntStatusString, Update::Value);

	GLV top(0,0,0);
	top.colors().set(Color(HSV(0.1,0.5,0.8), 1), 0.7);
	
	scene.stretch(1,1).anchor(0,0);
	toolBar.stretch(1,0).anchor(0,0);
	statusBar.stretch(1,0).anchor(0,1);
	
	top << scene << toolBar << (statusBar << statusString);

	Placer p(toolBar, Direction::E, Place::TL, 10, 10, 10);

	p << slider1 << slider2 << slider3;

	Window win(800, 600, "", &top);
	Application::run();
}
