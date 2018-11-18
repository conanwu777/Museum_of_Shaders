#ifndef INPUT_HPP
#define INPUT_HPP

#include "Camera.hpp"
#include "Window.hpp"
#include "graphics.hpp"
#include "Panel.hpp"

class PostProcess;

class Input{
	public:
		float curTime;
		float startTime;
		float lastTime;

		PostProcess& pp;

		Input(Camera& c, Window& w, Panel& uen, Panel& uex, PostProcess & p);
		Camera& cam;
		Window& win;
		Panel &uiEnter;
		Panel &uiExit;
		void KeyHold(Window& win, vector<RenderObject*> &panels, vector<RenderObject*> &frames);
		void transparentCheck(Position&, vector<RenderObject*> &panels);
		void frameCheck(Position&, Position& movCam, vector<RenderObject*> &panels);
		float   dist(Position& a, Position& b);
		bool insideMode = false;
		bool spaceDown = false;
		bool oneDown = false;
		int obj;
		static Input* singleton;
};

#endif