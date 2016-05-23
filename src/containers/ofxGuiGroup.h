#pragma once
#include "../ofxGuiElement.h"

#include "../controls/ofxGuiSlider.h"
#include "../controls/ofxGuiButton.h"
#include "../controls/ofxGuiLabel.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"

template<class VecType>
class ofxGuiVecSlider_;
template<class VecType>
class ofxGuiColorSlider_;

typedef ofxGuiVecSlider_<ofVec3f> ofxGuiVec3Slider;
typedef ofxGuiVecSlider_<ofVec2f> ofxGuiVec2Slider;
typedef ofxGuiVecSlider_<ofVec4f> ofxGuiVec4Slider;
typedef ofxGuiVecSlider_<ofVec3f> ofxGuiPointSlider;

typedef ofxGuiColorSlider_<unsigned char> ofxGuiColorSlider;
typedef ofxGuiColorSlider_<unsigned short> ofxGuiShortColorSlider;
typedef ofxGuiColorSlider_<float> ofxGuiFloatColorSlider;

class ofxGuiPanel;
class ofxGuiTabs;
class ofxGuiFpsPlotter;

class ofxGuiGroupHeader : public ofxGuiElement {
	public:
		ofxGuiGroupHeader(const ofJson &config = ofJson());

		~ofxGuiGroupHeader();

		virtual bool mousePressed(ofMouseEventArgs & args) override;

		virtual float getMinWidth() override;
		virtual float getMinHeight() override;

		static std::string getClassType();

	protected:

		virtual vector<std::string> getClassTypes() override;

		virtual void generateDraw() override;
		virtual void render() override;
#ifndef USE_FONTSTASH
		ofVboMesh textMesh;
#endif
		std::string leftStr, rightStr;
		ofPoint leftStrPos, rightStrPos;

};


class ofxGuiGroup : public ofxGuiElement {
	public:

		ofxGuiGroup();
		ofxGuiGroup(const std::string& collectionName);
		ofxGuiGroup(const std::string& collectionName, const ofJson & config);
		ofxGuiGroup(const ofParameterGroup & parameters, const ofJson &config = ofJson());
		ofxGuiGroup(const ofParameterGroup & parameters, const std::string& _filename, float x = 10, float y = 10);
		ofxGuiGroup(const std::string& collectionName, const std::string& _filename, float x = 10, float y = 10);

		virtual ~ofxGuiGroup();

		void setup();

		using Element::add;

		template<typename T>
		typename std::enable_if<std::is_arithmetic<T>::value, ofxGuiSlider<T>*>::type add(ofParameter<T> & p, const ofJson & config = ofJson());

		ofxGuiButton* add(ofParameter <void> & parameter, const ofJson & config = ofJson());
		ofxGuiToggle* add(ofParameter <bool> & parameter, const ofJson & config = ofJson());
		ofxGuiLabel* add(ofParameter <std::string> & parameter, const ofJson & config = ofJson());
		ofxGuiVec2Slider *add(ofParameter <ofVec2f> & parameter, const ofJson & config = ofJson());
		ofxGuiVecSlider_<ofVec3f> *add(ofParameter <ofVec3f> & parameter, const ofJson & config = ofJson());
		ofxGuiVec4Slider* add(ofParameter <ofVec4f> & parameter, const ofJson & config = ofJson());
		ofxGuiColorSlider* add(ofParameter <ofColor> & parameter, const ofJson & config = ofJson());
		ofxGuiShortColorSlider* add(ofParameter <ofShortColor> & parameter, const ofJson & config = ofJson());
		ofxGuiFloatColorSlider* add(ofParameter <ofFloatColor> & parameter, const ofJson & config = ofJson());

		void add(const ofParameterGroup& parameters);

		ofxGuiLabel* addLabel(const std::string& label, const ofJson& config = ofJson());
		ofxGuiElement* addSpacer(float width, float height);
		ofxGuiElement* addSpacer(const ofJson & config = ofJson());
		ofxGuiFpsPlotter* addFpsPlotter(const ofJson & config = ofJson());

		ofxGuiGroup* addGroup(const std::string& name="", const ofJson& config = ofJson());
		ofxGuiGroup* addGroup(const ofParameterGroup & parameters, const ofJson& config = ofJson());
		ofxGuiPanel* addPanel(const std::string& name="", const ofJson& config = ofJson());
		ofxGuiPanel* addPanel(const ofParameterGroup & parameters, const ofJson& config = ofJson());
		ofxGuiTabs* addTabs(const std::string& name="", const ofJson& config = ofJson());

		virtual void minimize();
		virtual void maximize();
		virtual void minimizeAll();
		virtual void maximizeAll();
		bool getMinimized();
		void toggleMinimize();

		virtual void clear() override;

		/// \brief Get a list of pointers to the child elements.
		///
		/// The parent Element retains ownership.
		///
		/// \returns a list of pointers to child elements.
		std::vector<ofxGuiElement*> getControls();

//		std::vector <std::string> getControlNames() const;
		std::size_t getNumControls();

		ofxGuiIntSlider* getIntSlider(const std::string& name);
		ofxGuiFloatSlider* getFloatSlider(const std::string& name);
		ofxGuiToggle* getToggle(const std::string& name);
		ofxGuiButton* getButton(const std::string& name);
		ofxGuiGroup* getGroup(const std::string& name);

		ofxGuiElement* getControl(const std::string& name);
		ofxGuiElement* getControl(std::size_t num);
		int getControlIndex(const std::string& name);
		int getControlIndex(ofxGuiElement* element);

		template <class ControlType>
		ControlType* getControlType(const std::string& name);

		template <class ControlType>
		ControlType* getControlType(const int& index);

		virtual ofAbstractParameter & getParameter() override;
		virtual std::string getName() override;
		virtual void setName(const std::string& name) override;

		void setShowHeader(bool show);
		ofxGuiElement* getHeader();

		bool getTogglesExclusive() const;
		void setExclusiveToggles(bool exclusive);
		bool setActiveToggle(int index);
		bool setActiveToggle(ofxGuiToggle* toggle);
		ofParameter<int>& getActiveToggleIndex();
		void deactivateAllOtherToggles(ofxGuiToggle* toggle);

		static std::string getClassType();

	protected:

		virtual vector<std::string> getClassTypes() override;

		ofParameterGroup parameters;

		virtual void _setConfig(const ofJson & config) override;

		void addParametersFrom(const ofParameterGroup & parameters);

		ofParameter<int> active_toggle_index;
		bool processToggles();
		void setOneToggleActive();

		ofParameter<std::string> filename;
		ofParameter<bool> exclusiveToggles;
		ofParameter<bool> minimized;

		ofParameter<bool> showHeader;
		ofxGuiElement* header;

		virtual void onChildAdded(DOM::ElementEventArgs&);
		virtual void onParentAdded(DOM::ElementEventArgs&);
		virtual void onHeaderVisibility(bool& showing);
		virtual void onHeaderHeight(float& height);
		virtual void onResize(DOM::ResizeEventArgs&);

	private:
		float widthMaximized, heightMaximized;

};

template <class ControlType>
ControlType* ofxGuiGroup::getControlType(const std::string& name){
	ControlType* control = dynamic_cast <ControlType *>(getControl(name));
	if(control){
		return control;
	}else{
		ofLogWarning() << "getControlType " << name << " not found, creating new";
		control = this->add<ControlType>();
		control->setName(name);
		return control;
	}
}

template <class ControlType>
ControlType* ofxGuiGroup::getControlType(const int& index){

	int counter = -1;
	for(auto &child : children()){
		if(ControlType* e = dynamic_cast<ControlType*>(child)){
			counter++;
			if(counter == index){
				return e;
			}
		}
	}

	return nullptr;

}

template<typename T>
typename std::enable_if<std::is_arithmetic<T>::value, ofxGuiSlider<T>*>::type ofxGuiGroup::add(ofParameter<T> & p, const ofJson & config){
	return add<ofxGuiSlider<T>>(p,config);
}

