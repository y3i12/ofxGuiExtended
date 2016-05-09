#pragma once

#include "ofxGuiGraphics.h"
#include "ofFbo.h"

class ofxGuiZoomableGraphics : public ofxGuiGraphics {
	public:

		ofxGuiZoomableGraphics(string canvasName="", const ofJson& config = ofJson());
		ofxGuiZoomableGraphics(string canvasName, ofBaseDraws * graphics, const ofJson& config = ofJson());
		ofxGuiZoomableGraphics(string canvasName, ofBaseDraws * graphics, float w, float h = 0);

		virtual ~ofxGuiZoomableGraphics();

		void setup();

		virtual bool mousePressed(ofMouseEventArgs & args) override;
		virtual bool mouseDragged(ofMouseEventArgs & args) override;
		virtual bool mouseReleased(ofMouseEventArgs & args) override;
		virtual bool mouseScrolled(ofMouseEventArgs & args) override;

		void onResize(DOM::ResizeEventArgs&);

	protected:

		virtual void render() override;
		virtual void generateDraw() override;

		void setZoomFactor(int factor);
		ofPoint addZoom(ofPoint p);
		float addZoom(float p);
		ofPoint removeZoom(ofPoint p);

		int zoom_factor;
		float zoom_speed;
		ofPoint zoom_point, zoom_point_scaled, zoom_point_offset;
		ofPoint zoom_translation;

		bool dragging_dst;
		ofPoint last_mouse;

		ofFbo contentFbo;

};
